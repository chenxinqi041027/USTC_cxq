# -*- coding: utf-8 -*-
"""
Created on Thu Apr 20 15:38:38 2023

@author: 28932
"""

import numpy as np
from scipy import linalg

A = np.random.rand(4,4)
b = np.random.rand(4,1)
print(A)
print(b)
print(np.linalg.matrix_rank(A))

x = np.linalg.solve(A, b)
print(x) # Ax = b的解
      
print(A.T) # 矩阵的转置

A_det = np.linalg.det(A)
print(A_det) # 矩阵的行列式

rank = np.linalg.matrix_rank(A)
print(rank) # 矩阵的秩

B = np.linalg.inv(A) #矩阵的逆矩阵
print(B)

w,v = np.linalg.eig(A)
print(w) # 特征值
print(v) # 特征向量


