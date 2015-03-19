#/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
import sys

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

if len(sys.argv) < 2:
	print("You forgot the file!")
	sys.exit(1)

data = np.array(np.loadtxt(sys.argv[1]))

fig = plt.figure()

ax = fig.add_subplot(111)

plotData = []
for i in range(0,8):
    plotData.append(data[i::8])

one = np.ones(plotData[0].size)
colours = ('b', 'g', 'r', 'c', 'm', 'y', 'k', 'w')

for i in range(0, 8):
	print(len(plotData[i]))
        ax.plot(plotData[i], one , colours[i] + 'o')

plt.show()
