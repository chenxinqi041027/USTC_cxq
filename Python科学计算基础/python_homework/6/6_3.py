# -*- coding: utf-8 -*-
"""
Created on Thu Apr 20 18:31:28 2023

@author: 28932
"""

import scipy.sparse as sps
import numpy as np
import scipy.sparse.linalg as spla

row = np.array([0, 0, 1, 2, 2, 3, 3, 4, 4])
col = np.array([0, 2, 3, 1, 4, 2, 4, 3, 4])
data = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])
csr1 = sps.csr_matrix((data,(row,col)),shape = (5,5))
print(csr1.toarray())
'''
[[1 0 2 0 0]
 [0 0 0 3 0]
 [0 4 0 0 5]
 [0 0 6 0 7]
 [0 0 0 8 9]]
'''

indptr = np.array([0, 2, 3, 5, 7, 9])
indices = np.array([0, 2, 3, 1, 4, 2, 4, 3, 4])
data = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])
csr2 = sps.csr_matrix((data,indices,indptr),shape = (5,5))
print(csr2.toarray())
'''
[[1 0 2 0 0]
 [0 0 0 3 0]
 [0 4 0 0 5]
 [0 0 6 0 7]
 [0 0 0 8 9]]
'''

b = np.array([4,2,1,3,5])
print(spla.spsolve(csr2,b)) # 求解方程组 csr2*x = b
# [2.91358025 0.2962963 0.54320988 0.66666667 -0.03703704]
