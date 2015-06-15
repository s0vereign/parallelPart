
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
data = f["fft"]

fig = plt.figure()

ax = fig.add_subplot(111)

ax.plot(data[:,0])
ax.plot(data[:,1])
ax.set_xlabel("$\mathbf{n \cdot dt}$")

plt.show()