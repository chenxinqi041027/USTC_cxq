# -*- coding: utf-8 -*-
"""
Created on Fri May 26 14:20:18 2023

@author: 28932
"""

import sympy as sym
a = sym.Symbol("a")
b = sym.Symbol("b")
A = sym.Matrix([[3, -2, a, a],[0, 2, b, b],[-5, 2, -9, -7],[a, -2, a, 3]])
print("矩阵的逆：")
print(A**(-1))
print("矩阵的特征值：")
print(A.eigenvals())
print("矩阵的特征向量：")
print(A.eigenvects())