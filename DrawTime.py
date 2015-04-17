#/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
import sys
import h5py

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

if len(sys.argv) < 2:
	print("You forgot the files!")
	sys.exit(1)

times = [0] * (len(sys.argv) - 1)

for i in range(1, len(sys.argv) - 1):

    f = h5py.File(sys.argv[i], "r")
    data = f["signal"]
    params = f["params"]

    N = int(round(1.0 / (params[0] * params[1])))
    dist = [0] * N
    x, step = np.linspace(0, 2 * np.pi, N, False, True)

    #n = len(data)
    for j in range(0, len(data)):
        dist[int(np.floor(data[j] / step))] += 1.0 #/ n
        
    f.close()
    times[i-1] = dist[0]
    print(dist[0])
#    print(str(100.0 * i / (len(sys.argv) - 1)) + "%")

fig = plt.figure()

ax = fig.add_subplot(111)


ax.plot(times)
#~ ax.plot(data[:i] if not singleCol else data, 'ro')
ax.set_xlabel("$\mathbf{n \cdot dt}$")

plt.show()
