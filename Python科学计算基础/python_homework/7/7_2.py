# -*- coding: utf-8 -*-
"""
Created on Thu Apr 27 16:48:48 2023

@author: 28932
"""
import math

class InvalidTriangleError(Exception):
    def __init__(self, message):
        self.message = message
        
def triangle(a, b, c):
    if a + b > c and a + c > b and b + c > a:
        s = (a+b+c)/2
        area = math.sqrt(s*(s-a)*(s-b)*(s-c))
        return area
    else:
        raise InvalidTriangleError('The three input parameters cannot form a triangle.')
        
import sys
try:
    # sys.argv = input('Please input three parameters:')
    x = float(sys.argv[1])
    y = float(sys.argv[2])
    z = float(sys.argv[3])
    print('The three input parameters can form a triangle.\nThe area is %f.' %triangle(x, y, z))
except IndexError: # 参数小于三个
    print('Three arguments must be supplied on the command line.')
except ValueError: # 参数不全为float类型
    print('The three input parameters are not all of float type.')
except InvalidTriangleError as ex: # 不能构成三角形
    print(ex.message)
finally:
    print("executing finally clause")
    




