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

singleCol = type(data[0]) is np.float64
upperBound = 1 if singleCol else len(data[0])
one = np.ones(data.size)


for i in range(0, int(upperBound)):
    if singleCol:
        ax.plot(data[:,i] if not singleCol else data, one , 'ro')
    else:
        ax.plot(data[:,i] if not singleCol else data, 'ro')
    #~ ax.plot(data[:i] if not singleCol else data, 'ro')
    ax.set_xlabel("$\mathbf{n \cdot dt}$")

plt.show()
