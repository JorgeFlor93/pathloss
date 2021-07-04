#!/usr/bin/env python3.8

import http.client
import json
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
#
# http client
#
conn = http.client.HTTPConnection("0.0.0.0", 5000)
top_lng = 1.08734
top_lat = 42.71638 
bot_lng = 2.22677
bot_lat = 42.15778
conn.request("GET", "/height-complete?top_lat=" + str(top_lat) + "&top_lng=" + str(top_lng) + "&bot_lat=" + str(bot_lat) + "&bot_lng=" + str(bot_lng))
r1 = conn.getresponse()

data1 = r1.read()
data = json.loads(data1)
store_array = data["data"]
# print(store_array)
nparr = np.array(store_array)
img = nparr.reshape((data["image"]["height"], data["image"]["width"]))
#
# show image
#
ax = plt.subplot()
im = ax.imshow(img, cmap='terrain', extent=(top_lng, bot_lng, bot_lat, top_lat))
divider = make_axes_locatable(ax)
cax = divider.append_axes("right", size="5%", pad=0.05)
cbar = plt.colorbar(im, cax=cax)
cbar.ax.set_ylabel('heights [m]', rotation = 270, labelpad=10)
ax.set_title('Heights heatmap')
plt.show()