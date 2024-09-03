# -*- coding: utf-8 -*-
"""
Created on Thu Apr 20 16:24:30 2023

@author: 28932
"""

import numpy as np
from scipy import linalg

# 随机生成矩阵
B = np.random.rand(4, 6)
b = np.random.rand(1, 6)
print(B)
print(b)
print(np.linalg.matrix_rank(B))

C = linalg.inv(B.T@B)
A = C@B.T@B
print(A)


U, s, V = linalg.svd(B)
S = linalg.diagsvd(s, 4, 6)
print(U)
print(S)
print(V)
print(s)
D = B@V.T
E = s*U
print(D)
print(E)
p, l, u = linalg.lu(B)
print(p)
print(l)
print(u)


