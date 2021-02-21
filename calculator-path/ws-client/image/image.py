#!/usr/bin/env python
from PIL import Image

class OImage:
    def __init__(self, array, parameters):
        self.parameters = parameters
        self.array = array
    
    def printImg(self):
        height = self.parameters[2]
        width = self.parameters[4]   
        size_i = width, height
        img = Image.new('RGBA', size_i, color = 'red')
        for i in range (0, width):
            for j in range (0, height):
                r, g, b = getColour(self.array[i + (j * width)])
                img.putpixel((i, j),(r, g, b, 255)) # RGBA
        img.show()
        img.save('pil_red.png')
        return img

def getColour(loss):
    if loss < 86.999999: 
        r = 0
        g = 255
        b = 0
    elif loss >= 87 and loss <= 90:
        r = 255
        g = 255
        b = 0
    elif loss > 90:
        r = 255
        g = 0
        b = 0
    else:
        r = 255
        g = 255
        b = 255
    return r, g, b