# -*- coding: utf-8 -*-
"""
Created on Fri Jun  2 19:12:01 2023

@author: 28932
"""

import numpy as np

from scipy import interpolate
import matplotlib.pyplot as plt

x = np.linspace(0, 10, num=21, endpoint=True)
y = (5*np.sin(3*x/8)+3)*np.cos(-x*x/9)
xx = np.linspace(x.min(), x.max(), 100)
f = interpolate.interp1d(x, y, kind='cubic')
plt.scatter(x, y, label='data points')
plt.plot(xx, f(xx), color='g', linestyle='-', label=r'spline of order 3')
plt.legend()
