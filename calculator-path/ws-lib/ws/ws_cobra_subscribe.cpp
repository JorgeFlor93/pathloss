/*
 *  ws_cobra_subscribe.cpp
 *  Author: Benjamin Sergeant
 *  Copyright (c) 2019 Machine Zone, Inc. All rights reserved.
 */

#include <atomic>
#include <chrono>
#include <iostream>
#include <ixcobra/IXCobraConnection.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <thread>

namespace ix
{
    void writeToStdout(bool fluentd, Json::FastWriter& jsonWriter, const Json::Value& msg)
    {
        Json::Value enveloppe;
        if (fluentd)
        {
            enveloppe["producer"] = "cobra";
            enveloppe["consumer"] = "fluentd";
            enveloppe["message"] = msg;
        }
        else
        {
            enveloppe = msg;
        }

        std::cout << jsonWriter.write(enveloppe);
    }

    int ws_cobra_subscribe_main(const std::string& appkey,
                                const std::string& endpoint,
                                const std::string& rolename,
                                const std::string& rolesecret,
                                const std::string& channel,
                                const std::string& filter,
                                bool quiet,
                                bool fluentd,
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

        Json::FastWriter jsonWriter;

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

        std::thread t(timer);

        conn.setEventCallback(
            [&conn, &channel, &jsonWriter, &filter, &msgCount, &msgPerSeconds, &quiet, &fluentd](
                ix::CobraConnectionEventType eventType,
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
                    conn.subscribe(channel,
                                   filter,
                                   [&jsonWriter, &quiet, &msgPerSeconds, &msgCount, &fluentd](
                                       const Json::Value& msg) {
                                       if (!quiet)
                                       {
                                           writeToStdout(fluentd, jsonWriter, msg);
                                       }

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
                else if (eventType == ix::CobraConnection_EventType_Pong)
                {
                    spdlog::info("Received websocket pong");
                }
            });

        while (true)
        {
            auto duration = std::chrono::seconds(1);
            std::this_thread::sleep_for(duration);
        }

        return 0;
    }
} // namespace ix
