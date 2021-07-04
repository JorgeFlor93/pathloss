#!/usr/bin/env python3.8

# WS client example

import sys
import asyncio
import websockets
import json
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import warnings
import logging
logger = logging.getLogger('websockets')
logger.setLevel(logging.INFO)
logger.addHandler(logging.StreamHandler())

async def recvPathloss():
    uri = "ws://0.0.0.0:8080"
    store_array = []
    parameters = []
    final_array = []
    async with websockets.connect(uri, max_size=None, ping_interval=20, ping_timeout=20, close_timeout=50) as websocket:
        model = await modelCase()
        with open('/home/fpjorge/pathloss/calculator-path/ws-client/JSONfiles/' + str(model)) as f:
            data = json.loads(f.read())
        await websocket.send(json.dumps(data)) 
        while True:
            greeting = await websocket.recv()              
            data = json.loads(greeting) # Dictionary
            if data["type"] == "initial":
                parameters = data["Parameters"]
            # if data["type"] == "partial":
                # store_array.extend(data["result"]) # extend mejor en vez de append para ir añadiendo datos    
            if data["type"] == "final":
                for value in data["Final"]:
                    final_array.extend(value["result"])                   
                break
        return store_array, final_array, parameters

async def heatmapImage(st, p):
   
    arr = np.array(st)
    img = arr.reshape((p["height"], p["width"]))
    topleft = [p["corners"]["topleft"]["lat"], p["corners"]["topleft"]["lon"]]
    botright = [p["corners"]["botright"]["lat"], p["corners"]["botright"]["lon"]]
    ax = plt.subplot()
    im = ax.imshow(img, cmap='inferno_r', extent=(topleft[1],botright[1], botright[0], topleft[0]))
    divider = make_axes_locatable(ax)
    cax = divider.append_axes("right", size="5%", pad=0.05)
    cbar = plt.colorbar(im, cax=cax)
    cbar.ax.set_ylabel('decibels [dB]', rotation = 270, labelpad=10)
    ax.set_title('[' + str(sys.argv[1]) + ']Pathloss heatmap' )
    plt.show()

async def modelCase():
    model = sys.argv[1]
    if model == "hata":
        ofile = "AreaHATA.json"
    elif model == "fspl":
        ofile = "AreaFSPL.json"
    elif model == "egli":
        ofile = "AreaEGLI.json"
    elif model == "cost":
        ofile = "AreaCOST.json"
    elif model == "ericcson":
        ofile = "AreaERICCSON.json"
    elif model == "pel":
        ofile = "AreaPEL.json"
    elif model == "soil":
        ofile = "AreaSOIL.json"
    elif model == "sui":
        ofile = "AreaSUI.json"
    elif model == "ecc33":
        ofile = "AreaECC33.json"
    elif model == "prueba":
        ofile = "prueba1.json"
    elif model == "SS":
        ofile = "SS.json"
    else:
        ofile = ""
    return ofile

async def main():
    st, fa, p = await recvPathloss()  
    await heatmapImage(fa, p)

asyncio.get_event_loop().run_until_complete(main())
