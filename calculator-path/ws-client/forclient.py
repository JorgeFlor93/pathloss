#!/usr/bin/env python

# WS client example

import asyncio
import websockets
import json
from contextlib import suppress


async def hello():
    store_array = []
    uri = "ws://0.0.0.0:8080"
    async with websockets.connect(uri) as websocket:
        with open('./AreaFSPL.json') as f: 
           data = json.loads(f.read())
        # print(json.dumps(data, indent=4, sort_keys=True))
        await websocket.send(json.dumps(data))

        for item in 
        while True:
            greeting = await websocket.recv()
            data = json.loads(greeting) # Dictionary
            if data["type"] == "partial":
                store_array.append(data["result"])
                # print(json.dumps(data["result"], indent=3)) # JSON string
                #print(json.dumps(data["fflush"], indent=3))
                # j_out.update(data["result"])
                # print(json.dumps(data, indent=3, sort_keys=True)) 
            await asyncio.sleep(1)            
        print(store_array) 

async def main():
    asyncio.ensure_future(hello())  # fire and forget
    await asyncio.sleep(6)

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


# asyncio.get_event_loop().run_until_complete(hello())
