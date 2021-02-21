#!/usr/bin/env python

# WS client example

import asyncio
import websockets
import json
from contextlib import suppress
from PIL import Image
from image.image import OImage
import numpy as np

store_array = []
dimensions = []
parameters = []

async def recvPathloss():
    uri = "ws://0.0.0.0:8080"
    async with websockets.connect(uri) as websocket:
        with open('./ws-client/AreaFSPL.json') as f:
           data = json.loads(f.read())
        await websocket.send(json.dumps(data))
        while True:     
            greeting = await websocket.recv() # Que devuelve greeting al final del recv()       
            data = json.loads(greeting) # Dictionary
            if data["type"] == "dimensions":
                for key, value in data["parameters"].items():
                    parameters.append(value) # [antennas, percentage, height, total_points, width]
            if data["type"] == "partial":
                store_array.extend(data["result"]) # extend function instead of append or insert.



async def main():
    asyncio.ensure_future(recvPathloss())  # fire and forget
    await asyncio.sleep(3)
    print(store_array)
    #await printstorearray()
    # image1 = OImage(store_array, parameters)
    # image1.printImg()

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())

    # Let's also cancel all running tasks:
    pending = asyncio.Task.all_tasks()
    for task in pending:
        task.cancel()
        # Now we should await task to execute it's cancellation.
        # Cancelled task raises asyncio.CancelledError that we can suppress:
        with suppress(asyncio.CancelledError):
            loop.run_until_complete(task)

async def printstorearray():
    # for h in range (0, parameters[2]):
        # print(str(store_array[h]) + ", " + str(store_array[h + 1]) + ", " + str(store_array[h + 2]) + ", " + str(store_array[h + 3]) + ", " + str(store_array[h + 4]) + ", " + str(store_array[h + 5]) + ", " + str(store_array[h + 6]) + ", " + str(store_array[h + 7]) + ", " + str(store_array[h + 8]) + "\n")
    # print(store_array)
    arrnumpy = np.reshape(store_array, (parameters[2], parameters[4]))
    # print(np.matrix(arrnumpy))
    # print(parameters)

""" Apuntes """

# print(json.dumps(data, indent=3, sort_keys=True)) # print JSON string. param1 espaciado, param2 ordenación.

# asyncio.get_event_loop().run_until_complete(hello()) # Crea un bucle hasta que se termine la función hello