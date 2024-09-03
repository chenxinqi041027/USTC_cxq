# -*- coding: utf-8 -*-
"""
Created on Fri Jun  2 19:18:15 2023

@author: 28932
"""

import numpy as np
import sympy as sym
from scipy import optimize as optm

x,y = sym.symbols("x, y")
f_mat = sym.Matrix([y*sym.sin(x)-4,x*y-x-5])
j = f_mat.jacobian(sym.Matrix([x,y]))

def f(x):
    return [x[1]*np.sin(x[0])-4,x[0]*x[1]-x[0]-5]

def f2(x):
    f_j = np.array([[x[1]*np.cos(x[0]),np.sin(x[0])],[x[1]-1,x[0]]])
    return f(x),f_j

print(optm.root(f2,[1,1],jac=True,method = 'lm'))