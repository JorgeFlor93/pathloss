/*
 *  ws_cobra_metrics_to_redis.cpp
 *  Author: Benjamin Sergeant
 *  Copyright (c) 2019 Machine Zone, Inc. All rights reserved.
 */

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <ixcobra/IXCobraConnection.h>
#include <ixsnake/IXRedisClient.h>
#include <mutex>
#include <queue>
#include <spdlog/spdlog.h>
#include <sstream>
#include <thread>

namespace ix
{
    int ws_cobra_metrics_to_redis(const std::string& appkey,
                                  const std::string& endpoint,
                                  const std::string& rolename,
                                  const std::string& rolesecret,
                                  const std::string& channel,
                                  const std::string& filter,
                                  const std::string& host,
                                  int port,
                                  const ix::SocketTLSOptions& tlsOptions)
    {
        ix::CobraConnection conn;
        conn.configure(appkey,
                       endpoint,
                       rolename,
                       rolesecret,
                       ix::WebSocketPerMessageDeflateOptions(true),
                       tlsOptions);
        conn.connect();

        // Display incoming messages
        std::atomic<int> msgPerSeconds(0);
        std::atomic<int> msgCount(0);

        auto timer = [&msgPerSeconds, &msgCount] {
            while (true)
            {
                spdlog::info("#messages {} msg/s {}", msgCount, msgPerSeconds);

                msgPerSeconds = 0;
                auto duration = std::chrono::seconds(1);
                std::this_thread::sleep_for(duration);
            }
        };

        ix::RedisClient redisClient;
        if (!redisClient.connect(host, port))
        {
            spdlog::error("Cannot connect to redis host {}:{}", host, port);
            return 0;
        }

        std::mutex conditionVariableMutex;
        std::condition_variable condition;
        std::queue<Json::Value> queue;

        auto redisSender = [&condition, &queue, &conditionVariableMutex, &redisClient] {
            Json::FastWriter jsonWriter;

            int batchSize = 1000;
            int i = 0;

            std::stringstream pipe;

            while (true)
            {
                Json::Value msg;

                {
                    std::unique_lock<std::mutex> lock(conditionVariableMutex);
                    condition.wait(lock, [&queue] { return !queue.empty(); });

                    msg = queue.front();
                    queue.pop();
                }

                // compute channel
                std::stringstream ss;
                ss << "session=" << msg["session"].asString() << ";msgid=" << msg["id"].asString();

                std::string channel = ss.str();

                std::string errMsg;
                pipe << redisClient.prepareXaddCommand(channel, jsonWriter.write(msg));

                if (i++ == batchSize)
                {
                    if (!redisClient.sendCommand(pipe.str(), batchSize, errMsg))
                    {
                        spdlog::error("error sending command: {}", errMsg);
                    }

                    i = 0;
                }
            }
        };

        std::thread t1(timer);
        std::thread t2(redisSender);

        conn.setEventCallback([&conn,
                               &channel,
                               &filter,
                               &msgCount,
                               &msgPerSeconds,
                               &conditionVariableMutex,
                               &condition,
                               &queue](ix::CobraConnectionEventType eventType,
                                       const std::string& errMsg,
                                       const ix::WebSocketHttpHeaders& headers,
                                       const std::string& subscriptionId,
                                       CobraConnection::MsgId msgId) {
            if (eventType == ix::CobraConnection_EventType_Open)
            {
                spdlog::info("Subscriber connected");

                for (auto it : headers)
                {
                    spdlog::info("{}: {}", it.first, it.second);
                }
            }
            else if (eventType == ix::CobraConnection_EventType_Authenticated)
            {
                spdlog::info("Subscriber authenticated");

                conn.subscribe(
                    channel,
                    filter,
                    [&msgPerSeconds, &msgCount, &conditionVariableMutex, &condition, &queue](
                        const Json::Value& msg) {
                        {
                            std::unique_lock<std::mutex> lock(conditionVariableMutex);
                            queue.push(msg);
                        }

                        condition.notify_one();

                        msgPerSeconds++;
                        msgCount++;
                    });
            }
            else if (eventType == ix::CobraConnection_EventType_Subscribed)
            {
                spdlog::info("Subscriber: subscribed to channel {}", subscriptionId);
            }
            else if (eventType == ix::CobraConnection_EventType_UnSubscribed)
            {
                spdlog::info("Subscriber: unsubscribed from channel {}", subscriptionId);
            }
            else if (eventType == ix::CobraConnection_EventType_Error)
            {
                spdlog::error("Subscriber: error {}", errMsg);
            }
            else if (eventType == ix::CobraConnection_EventType_Published)
            {
                spdlog::error("Published message hacked: {}", msgId);
            }
        });

        while (true)
        {
            std::chrono::duration<double, std::milli> duration(10);
            std::this_thread::sleep_for(duration);
        }

        return 0;
    }
} // namespace ix
