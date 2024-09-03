# -*- coding: utf-8 -*-
"""
Created on Fri May 19 17:47:19 2023

@author: 28932
"""

import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

def title_and_labels(ax, title):
    ax.set_title(title)
    ax.set_xlabel("$x$")
    ax.set_ylabel("$y$")
    ax.set_zlabel("$z$")
    
fig, axes = plt.subplots(2, 2, figsize = (6, 6), subplot_kw = {'projection': '3d'})

x = y = np.linspace(-2, 2, 100)
X, Y = np.meshgrid(x, y)
Z = (3 * (X**3) - 2 * X + 4 * (X**2) * Y + 2 * (Y**2)) * np.exp(- X**2 - Y**2)

# 根据z值染色的表面图
norm = mpl.colors.Normalize(vmin = Z.min(), vmax = Z.max())
p = axes[0, 0].plot_surface(X, Y, Z, linewidth=0, rcount=20,
                            ccount=20, norm=norm,
                            cmap=mpl.cm.hot)
cb = fig.colorbar(p, ax=axes[0, 0], pad=0.1, shrink = 0.6)
title_and_labels(axes[0, 0], "surface plot")

# x坐标值相同的点连线得到的三维等高线图
cset = axes[0, 1].contour(X, Y, Z, zdir = 'x', levels = 20,
                          norm = norm, cmap = mpl.cm.hot)
title_and_labels(axes[0, 1], "contour x")

# y坐标值相同的点连线得到的三维等高线图
cset = axes[1, 0].contour(X, Y, Z, zdir = 'y', levels = 20,
                          norm = norm, cmap = mpl.cm.hot)
title_and_labels(axes[1, 0], "contour y")

#z坐标值相同的点连线得到的三维等高线图
cset = axes[1, 1].contour(X, Y, Z, zdir = 'z', levels = 20,
                          norm = norm, camp = mpl.cm.hot)
title_and_labels(axes[1, 1], "contour z")

fig.tight_layout(); plt.show()