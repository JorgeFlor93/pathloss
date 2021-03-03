#!/usr/bin/env python

# WS client example

import asyncio
import websockets
import json
import numpy as np
import matplotlib.pyplot as plt

async def recvPathloss():
    uri = "ws://0.0.0.0:8080"
    async with websockets.connect(uri) as websocket:
        with open('/home/jorge/git/pathloss/calculator-path/ws-client/AreaFSPL.json') as f:
           data = json.loads(f.read())
        await websocket.send(json.dumps(data))
        store_array = []
        parameters = []
        final_array = []
        while True:
            greeting = await websocket.recv()       
            data = json.loads(greeting) # Dictionary
            # if data["type"] == "dimensions":
            #     for key, value in data["parameters"].items():
            #         parameters.append(value) # [corners, height, antennas, percentage,  total_points, width]
            if data["type"] == "partial":
                store_array.extend(data["result"]) # extend function instead of append or insert.
            if data["type"] == "final":
                # for key, value in data["Parameters"].items():
                #     print(str(key) + " :" + str(value))
                print(data["Parameters"])
                parameters = data["Parameters"]
                #print("corners_bot_lat: " + parameters["corners"]["botright"]["lat"])
                final_array.append(data["Final"])
                break
        return store_array, final_array, parameters

async def heatmapImage(st, p):
   
    arr = np.array(st)
    img = arr.reshape((p["height"], p["width"]))
    topleft = [p["corners"]["topleft"]["lat"], p["corners"]["topleft"]["lon"]]
    botright = [p["corners"]["botright"]["lat"], p["corners"]["botright"]["lon"]]
    print(str(topleft[1]) + ", " + str(botright[0]) + ", " + str(botright[1]) + ", " + str(topleft[0]))
    plt.imshow(img, cmap='inferno_r', extent=(topleft[1],botright[1], botright[0], topleft[0]))
    cbar = plt.colorbar()
    cbar.ax.set_ylabel('decibels [dB]', rotation = 270, labelpad=10)
    plt.show()

async def main():
    st, fa, p = await recvPathloss() 
    # print(p) # print parameters
    # print(st) # print array 
    await heatmapImage(st, p)
    # print(final_array)
    # image1 = OImage(st, p)
    # image1.printImg()

asyncio.get_event_loop().run_until_complete(main())
