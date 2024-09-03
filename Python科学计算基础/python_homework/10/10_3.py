# -*- coding: utf-8 -*-
"""
Created on Fri May 26 15:01:32 2023

@author: 28932
"""

import sympy as sym

x = sym.Symbol("x",positive=True)
y = sym.Function("y")
ode = y(x).diff(x, 2) + 2*y(x).diff(x) + 3*y(x) - 4
eq = sym.Eq(ode,0)
ode_sol = sym.dsolve(ode,ics = {y(0): 16, y(x).diff(x).subs(x, 0): 18})
sym.pprint(ode_sol)
