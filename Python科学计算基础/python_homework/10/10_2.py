# -*- coding: utf-8 -*-
"""
Created on Fri May 26 14:34:39 2023

@author: 28932
"""

import sympy as sym
a = sym.Symbol("a")
b = sym.Symbol("b")
c = sym.Symbol("c")
x = sym.Symbol("x")
y = sym.Symbol("y")
z = sym.Symbol("z")
w = sym.Symbol("w")
print(sym.linsolve([3*x-2*y+a*z+a*w-1,2*y+b*z+b*w+2,-5*x+2*y-9*z-7*w-3,a*x-2*y+a*z+3*w-c], (x,y,z,w)))