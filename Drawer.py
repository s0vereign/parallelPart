#/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
import sys
import h5py

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

if len(sys.argv) < 2:
	print("You forgot the file!")
	sys.exit(1)

f = h5py.File(sys.argv[1], "r")
data = f["signal"]

fig = plt.figure()

ax = fig.add_subplot(111)

singleCol = type(data[0]) is np.float64
upperBound = 1 if singleCol else len(data[0])
one = np.ones(data.size)


for i in range(0, int(upperBound)):
    ax.plot(data[::2], data[1::2])
    #~ ax.plot(data[:i] if not singleCol else data, 'ro')
    ax.set_xlabel("$\mathbf{n \cdot dt}$")

plt.show()
