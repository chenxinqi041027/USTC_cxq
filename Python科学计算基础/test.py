# -*- coding: utf-8 -*-
"""
Created on Wed May  3 15:49:26 2023

@author: 28932
"""

def gcd(a,b):
    while a != b:
        if a>b:
            a-=b
        else:
            b-=a
    return a
    
import sys
try:
    x = int(sys.argv[1])
    y = int(sys.argv[2])
except IndexError:
    print('Two arguments must be supplied on the command line.')
except ValueError:
    print('Each argument shpuld be an integer.')
else:
    print('%d' %gcd(x,y))
