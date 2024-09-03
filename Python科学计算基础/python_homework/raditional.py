# -*- coding: utf-8 -*-
"""
Module for performing arithmetic operations for rational numbers.

To run the module, user needs to supply three named parameters:
1. op stands for the operation:
    add for addition
    sub for subtraction
    mul for multiplication
    div for division
2. x stands for the first operand
3. y stands for the second operand

x and y must be enclosed in paired parentheses.

For example:

>>> run rational.py --op add --x (2/3) --y (-70/40)
-13/12
>>> run rational.py --op sub --x (-20/3) --y (120/470)
-976/141
>>> run rational.py --op mul --x (-6/19) --y (-114/18)
2/1
>>> run rational.py --op div --x (-6/19) --y (-114/-28)
-28/361
"""

import sys, math

def test_all_functions():  
    l_x=['(2/3)','(-20/3)','(-6/19)','(-6/19)']
    l_y=['(-70/40)','(120/470)','(-114/18)','(-114/-28)']
    l_op=['add','sub','mul','div']
    f = {'add':add, 'sub':sub, 'mul':mul, 'div':div}
    for i in range(4):
        l_x[i]=get_rational(l_x[i])
        l_y[i]=get_rational(l_y[i])
        print(f[l_op[i]](l_x[i],l_y[i]))
        

def gcd(a, b):  
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    return a

def reduce(n, d):  
    if n == 0:
        d = 1
    else:
        n //= gcd(abs(n), abs(d))
        d //= gcd(abs(n), abs(d))
    if n<0 and d<0:
        n=abs(n);d=abs(d)
    if d<0:
        n=n*-1;d=abs(d)
    return [n, d]

def add(x, y):  
    ax, bx = x
    ay, by = y
    return reduce(ax*by + ay*bx, bx*by)

def sub(x, y):
    ay, by = y
    return add(x,[-ay,by])

def mul(x, y):  
    ax, bx = x
    ay, by = y
    return reduce(ax*ay, bx*by)

def div(x, y): 
    ay, by = y
    return mul(x, [by, ay])

def output(x):  
    ax, bx = x
    print(ax,"/",bx)

def get_rational(s):  
    s = s.lstrip('(')
    s = s.rstrip(')')       
    num = s.split('/')     
    n, d = int(num[0]), int(num[1])
    return [n, d]

if __name__ == '__main__':
    if len(sys.argv) == 1:
        print(__doc__)
    elif len(sys.argv) == 2 and sys.argv[1] == '-h':
        print(__doc__)
    elif len(sys.argv) == 2 and sys.argv[1] == 'test':
        test_all_functions()
    else:
        import argparse
        parser = argparse.ArgumentParser()
        parser.add_argument('--op', type=str)
        parser.add_argument('--x', type=str)
        parser.add_argument('--y', type=str)
        args = parser.parse_args()
        op = args.op
        x = get_rational(args.x); y = get_rational(args.y)
        f = {'add':add, 'sub':sub, 'mul':mul, 'div':div}
        output(f[op](x, y))