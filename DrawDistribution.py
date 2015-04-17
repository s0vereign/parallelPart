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
params = f["params"]

N = int(round(1.0 / (params[0] * params[1])))
dist = [0] * N
x, step = np.linspace(0, 2 * np.pi, N, False, True)
print(N)

n = len(data)
for i in range(0, len(data)):
#    print("x = "+ str( data[i]) +  " gerundet zu "+ str( data[i] / step))
    dist[int(np.floor(data[i] / step))] += 1.0

fig = plt.figure()

ax = fig.add_subplot(111)

ax.plot(x, dist)
#~ ax.plot(data[:i] if not singleCol else data, 'ro')
ax.set_xlabel("$\mathbf{n \cdot dt}$")

plt.show()
