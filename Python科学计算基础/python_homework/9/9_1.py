# -*- coding: utf-8 -*-
"""
Created on Fri May 19 17:45:40 2023

@author: 28932
"""

import math
import matplotlib.pyplot as plt

class Integrator:
    def __init__(self, a, b, n):
        self.a, self.b, self.n = a, b, n
        self.points, self.weights = self.compute_points()

    def compute_points(self):
        raise NotImplementedError(self.__class__.__name__)

    def integrate(self, f):  
        I = 0
        for i in range(0, self.n + 1):
            I += self.weights[i] * f(self.points[i])
        return I

class Trapezoidal(Integrator):
    def compute_points(self):
        h = (self.b - self.a) / self.n
        weights = []; points = []
        for i in range(0, self.n + 1):
            weights.append(h)
            points.append(self.a + i * h)
        weights[0] = weights[self.n] = h / 2
        return points, weights
        
class Simpson(Integrator):
    def compute_points(self):  
        if self.n % 2:
            self.n += 1
        h = (self.b - self.a) / self.n
        weights = []; points = []
        for i in range(0, self.n + 1):
            points.append(self.a + i * h)
        weights.append(h / 3)
        for i in range(1, self.n, 2):
            weights.append(4 * h / 3)
            weights.append(2 * h / 3)
        weights.append(h / 3)
        return points, weights

class GaussLegendre(Integrator):
    def compute_points(self):  
        if self.n % 2 == 0:
            self.n += 1
        h = 2 * (self.b - self.a) / (self.n  + 1)
        weights = []; points = []
        for i in range(0, self.n, 2):
            points.append(self.a + (i + 1) / 2 * h - math.sqrt(3) / 6 * h)
            points.append(self.a + i / 2 * h + math.sqrt(3) / 6 * h)
        for i in range(0, self.n + 1):
            weights.append(h / 2)
        return points, weights
    
def f(x):
    return (x * math.cos(x) + math.sin(x)) * math.exp(x * math.sin(x))
def F(x):
    return math.exp(x * math.sin(x))

I_exact = F(3) - F(2)
x = [2, 4, 8, 16, 32, 64, 128, 256]
y_1 = []; y_2 = []; y_3 = []

for i in x:
    integrator = Trapezoidal(2, 3, i)
    y_1.append(abs((I_exact - integrator.integrate(f)) / I_exact))
    integrator = Simpson(2, 3, i)
    y_2.append(abs((I_exact - integrator.integrate(f)) / I_exact))
    integrator = GaussLegendre(2, 3, i)
    y_3.append(abs((I_exact - integrator.integrate(f)) / I_exact))
    
plt.plot(x, y_1, color = 'y', label = 'Trapezoidal')
plt.plot(x, y_2, color = 'g', label = 'Simpson')
plt.plot(x, y_3, color = 'r', label = 'GaussLegendre')

plt.ylabel('relative error')
plt.xlabel('n')
plt.title("definite integral")

plt.legend()
plt.grid(linestyle = ':')
plt.show()