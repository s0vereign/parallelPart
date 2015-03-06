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

for i in range(0, int(upperBound)):
    ax.plot( data[:,i] if not singleCol else data, label="Curve "+str(i+1))
    ax.set_xlabel("$\mathbf{n \cdot dt}$")
    ax.set_ylabel("$\mathbf{v_x}$")
    ax.legend()

plt.show()