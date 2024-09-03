# -*- coding: utf-8 -*-
"""
Created on Fri May 19 17:46:52 2023

@author: 28932
"""

import numpy as np
import matplotlib.pyplot as plt

x = np.arange(100, 1005, 100)
y1 = [0.0004, 0.0016, 0.0034, 0.0063, 0.0104, 0.0153, 0.0209, 0.0275, 0.0355, 0.0437] 
y2 = [0.0002, 0.0005, 0.0008, 0.0011, 0.0013, 0.0017, 0.0020, 0.0023, 0.0025, 0.0029] 
y3 = [0.0001, 0.0003, 0.0004, 0.0006, 0.0007, 0.0009, 0.0011, 0.0013, 0.0015, 0.0017]

plt.figure(figsize = (8, 4), dpi = 300)
plt.xticks(x)

# 插入排序
plt.plot(x, y1, color = 'y', label = 'insertion_sort')
# 归并排序
plt.plot(x, y2, color = 'r', label = 'merge_sort')
# 快速排序
plt.plot(x, y3, color = 'g', label = 'qsort')

plt.ylabel('time')
plt.xlabel('n')
plt.title("Three types of sorting")

plt.legend()
plt.grid(linestyle = ':')
plt.show()

