#!/usr/bin/env python

# WS client example

import asyncio
import websockets
import json
from image.image import OImage
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
                    parameters.append(value) # [antennas, percentage, height, total_points, width]
            if data["type"] == "partial":
                store_array.extend(data["result"]) # extend function instead of append or insert.
            if data["type"] == "final":
                final_array.append(data["Final"])
                break
        return store_array, final_array, parameters

async def drawImage(st, p):
    arr = np.array(st)
    img = arr.reshape((p[2], p[4]))
    plt.imshow(img)
    plt.show()

async def main():
    st, fa, p = await recvPathloss()  # fire and forget
    # print(st)
    await drawImage(st, p)
    # print(final_array)
    # image1 = OImage(store_array, parameters)
    # image1.printImg()

asyncio.get_event_loop().run_until_complete(main())



""" Apuntes """

# print(json.dumps(data, indent=3, sort_keys=True)) # print JSON string. param1 espaciado, param2 ordenación.

# asyncio.get_event_loop().run_until_complete(hello()) # Crea un bucle hasta que se termine la función hello