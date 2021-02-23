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
        with open('./ws-client/AreaFSPL.json') as f:
           data = json.loads(f.read())
        await websocket.send(json.dumps(data))
        store_array = []
        parameters = []
        final_array = []
        while True:
            greeting = await websocket.recv()       
            data = json.loads(greeting) # Dictionary
            if data["type"] == "dimensions":
                for key, value in data["parameters"].items():
                    parameters.append(value) # [corners, height, antennas, percentage,  total_points, width]
            if data["type"] == "partial":
                store_array.extend(data["result"]) # extend function instead of append or insert.
            if data["type"] == "final":
                final_array.append(data["Final"])
                break
        return store_array, final_array, parameters

async def heatmapImage(st, p):
   
    arr = np.array(st)
    img = arr.reshape((p[1], p[5]))
    topleft = [p[0]["topleft"]["lat"], p[0]["topleft"]["lon"]]
    botright = [p[0]["botright"]["lan"], p[0]["botright"]["lon"]]
    plt.imshow(img, cmap='inferno_r', extent=(topleft[1],botright[1], botright[0], topleft[0]))
    cbar = plt.colorbar()
    cbar.ax.set_ylabel('decibels [dB]', rotation = 270, labelpad=10)
    plt.show()

async def main():
    st, fa, p = await recvPathloss()  # fire and forget
    # print(p)
    # print(p[0]["topleft"]["lat"])
    # print(st)
    await heatmapImage(st, p)
    # print(final_array)
   

asyncio.get_event_loop().run_until_complete(main())
