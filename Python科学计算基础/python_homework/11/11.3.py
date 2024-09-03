# -*- coding: utf-8 -*-
"""
Created on Fri Jun  2 19:21:06 2023

@author: 28932
"""

import numpy as np

from scipy.integrate import solve_ivp

import matplotlib.pyplot as plt

def f(x):
    return (49*np.sqrt(2)*np.sin(np.sqrt(2*x))+44*np.cos(np.sqrt(2*x)))/3*np.exp(-x)+4/3

def fvdp2(t,y):
    y0, y1 = y   
    dydt = [y1, 2*y1-3*y0+4] 
    return dydt
t = np.linspace(0, 10, 1000)
span = (0,10)
y0 = [16, 18] 
y_ = solve_ivp(fvdp2,t_span=span, y0=y0, t_eval=t)
plt.scatter(y_.t, y_.y[1,:], label='data points')
plt.plot(t, f(t),'r-', label = 'line')
plt.legend()