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
            # if data["type"] == "partial":
                # store_array.extend(data["result"]) # extend function instead of append or insert.     
            if data["type"] == "final":
                # print(data["Parameters"]) # {'corners': {'botright': {'lat': 40.408624, 'lon': -3.7186151}, 'topleft': {'lat': 40.42062, 'lon': -3.741253}}, 'height': 43, 'numantennas': 3, 'progress': 35, 'totalpoints': 3483, 'width': 81}
                parameters = data["Parameters"] 
                # Almacenamos el array al final
                for value in data["Final"]:
                    final_array.extend(value["result"])                   
                break
        return store_array, final_array, parameters

async def heatmapImage(st, p):
   
    arr = np.array(st)
    img = arr.reshape((p["height"], p["width"]))
    topleft = [p["corners"]["topleft"]["lat"], p["corners"]["topleft"]["lon"]]
    botright = [p["corners"]["botright"]["lat"], p["corners"]["botright"]["lon"]]
    plt.imshow(img, cmap='inferno_r', extent=(topleft[1],botright[1], botright[0], topleft[0]))
    cbar = plt.colorbar()
    cbar.ax.set_ylabel('decibels [dB]', rotation = 270, labelpad=10)
    plt.show()

async def main():
    st, fa, p = await recvPathloss() 
    # print(p) # print parameters
    # print(st) # print array 
    # print(fa)
    await heatmapImage(fa, p)

asyncio.get_event_loop().run_until_complete(main())
