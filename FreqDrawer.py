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

ax.plot(np.sqrt(data[:,0]**2 + data[:,1]**2))
ax.set_xlabel("$\mathbf{n \cdot dt}$")

plt.show()
