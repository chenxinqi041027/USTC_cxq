# -*- coding: utf-8 -*-
"""
Created on Wed Apr 19 11:10:19 2023

@author: 28932
"""

def gcd(a,b):
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    return a

class Rational:
    def __init__(self, n = 0, d = 1):
        if n > 0:
            if d > 0:
                flag = 1
            else:
                d = -d
                flag = -1
        else:
            n = -n
            if d < 0:
                d = -d
                flag = 1
            else:
                flag = -1
        g = gcd(n, d)
        n /= g
        d /= g
        _nu = n * flag
        _de = d
        self.__dict__['nu'] = _nu
        self.__dict__['de'] = _de
    
    def __setattr__(self, name, value):
        raise TypeError('Error: Rational object are immutable')
        
    def __str__(self):return '%d/%d' % (self.nu, self.de)
    
    def __add__(self, other):
        other = be_Rational(other)
        a = self.nu * other.de + self.de * other.nu
        b = self.de * other.de
        return Rational(a,b)
    
    def __sub__(self, other):
        other = be_Rational(other)
        a = self.nu * other.de - self.de * other.nu
        b = self.de * other.de
        return Rational(a,b)
    
    def __mul__(self, other):
        other = be_Rational(other)
        a = self.nu * other.nu
        b = self.de * other.de
        return Rational(a,b)
    
    def __truediv__(self, other):
        other = be_Rational(other)
        if other.nu == 0:
            raise ZeroDivisionError('Error: division by 0')
        a = self.nu * other.de
        b = self.de * other.nu
        return Rational(a,b)
    
    def __eq__(self, other):
        other = be_Rational(other)
        self = Rational(self.nu,self.de)
        other = Rational(other.nu,other.de)
        if self.de == other.de and self.nu == other.nu:
            return True
        return False
       
    
    def __ne__(self, other):
        if self.__eq__(other) is True:
            return False
        return True
    
    def __gt__(self, other):
        if self.__sub__(other).nu > 0:
            return True
        return False
    
    def __lt__(self, other):
        if self.__sub__(other).nu < 0:
            return True
        return False
    
    def __ge__(self, other):
        if self.__lt__(other) is True:
            return False
        else: return True
    
    def __le__(self, other):
        if self.__gt__(other) is True:
            return False
        return True

def test():
    testsuite = [
        ('Rational(2, 3) + Rational(-70, 40)',
         Rational(-13, 12)),
        ('Rational(-20, 3) - Rational(120, 470)',
         Rational(-976, 141)),
        ('Rational(-6, 19) * Rational(-114, 18)',
         Rational(2, 1)),
        ('Rational(-6, 19) / Rational(-114, -28)',
         Rational(-28,361)),
        
        ('Rational(-6, 19) == Rational(-14, 41)',False),
        ('Rational(-6, 19) != Rational(-14, 41)',True),
        ('Rational(6, -19) > Rational(14, -41)',True),
        ('Rational(-6, 19) < Rational(-14, 41)',False),
        ('Rational(-6, 19) >= Rational(-14, 41)',True),
        ('Rational(6, -19) <= Rational(14, -41)',False),
        ('Rational(-15, 8) == Rational(120, -64)',True),
    ]
    for t in testsuite:
        try:
            result = eval(t[0])
        except:
            print('Error in evaluating ' + t[0]); continue
            
        if result != t[1]:
            print('Error:  %s != %s' % (t[0],t[1]))
   
def is_Rational(oth):
    return hasattr(oth, 'nu') and hasattr(oth, 'de')

def be_Rational(oth):
    if is_Rational(oth):
        return oth  
    elif isinstance(oth, tuple):  
        if len(oth) <= 2:  
            return Rational(*oth)  
        else:
            raise TypeError('Error: <= 2 numbers expected')
    else:
        return Rational(oth)
             
if __name__ == '__main__':
    test()






























        
        