# -*- coding: utf-8 -*-
"""
Created on Wed Apr 19 19:10:31 2023

@author: 28932
"""

import math

class Integrator:
    def __init__(self, a, b, n):
        self.a, self.b, self.n = a, b, n
        self.points, self.weights = self.compute_points()

    def compute_points(self):
        raise NotImplementedError(self.__class__.__name__)

    def integrate(self, f):
        answer = 0
        for i in range(1, self.n + 1):
            answer += self.weights[i]*f(self.points[i])
        return answer

class Trapezoidal(Integrator):
    def compute_points(self): 
        n = self.n
        h = (self.b - self.a)/n
        x = []
        w = []
        for i in range(0, n + 1):
            if i == 0 or i == n:
                w.append(h/2)
            else:
                w.append(h)
            x.append(self.a + i*h)
        return x, w
    
class Simpson(Integrator):
    def compute_points(self):
        n = self.n
        h = (self.b - self.a)/n
        x = []
        w = []
        if n % 2 != 0:
            n = n + 1
        for i in range(0, n + 1):
            if i == 0 or i == n:
                w.append(h/3)
            elif i % 2 == 0:
                w.append(2*h/3)
            else:
                w.append(4*h/3)
            x.append(self.a + i*h)
        return x, w
    
class GaussLegendre(Integrator):
    def compute_points(self):
        n = self.n
        h = 2*(self.b - self.a)/(n + 1)
        x = []
        w = []
        if n % 2 == 0:
            n = n + 1
        for i in range(0, n + 1):
            w.append(h/2)
            if i % 2 == 0:
                x.append(self.a + (i+1)/2*h - math.sqrt(3)/6*h)
            else:
                x.append(self.a + i/2*h + math.sqrt(3)/6*h)
        return x, w
    
def test():
    def f(x): return (x * math.cos(x) + math.sin(x)) * \
                      math.exp(x * math.sin(x))
    def F(x): return math.exp(x * math.sin(x))

    a = 2; b = 3; n = 200
    I_exact = F(b) - F(a)
    tol = 1E-3

    methods = [Trapezoidal, Simpson, GaussLegendre]
    for method in methods:
        integrator = method(a, b, n)
        I = integrator.integrate(f)
        rel_err = abs((I_exact - I) / I_exact)
        print('%s: %g' % (method.__name__, rel_err))
        if rel_err > tol:
            print('Error in %s' % method.__name__)

if __name__ == '__main__':
    test()