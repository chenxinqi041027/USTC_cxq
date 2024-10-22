# -*- coding: utf-8 -*-
"""
Created on Wed Apr 19 19:57:13 2023

@author: 28932
"""

def gcd(a, b):  
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    return a

class Rational:
    def __init__(self, n=0, d=1):  
        if n > 0:
            if d > 0:
                s = 1
            else:
                d = -d
                s = -1
        else:
            n = -n
            if d > 0:
                s = -1
            else:
                d = -d
                s = 1
        origcd = gcd(n, d)
        n = s*n/origcd
        d = d/origcd
        _nu = n; _de = d
        self.__dict__['nu'] = _nu; self.__dict__['de'] = _de

    def __setattr__(self, name, value):
        raise TypeError('Error: Rational objects are immutable')

    def __str__(self): return '%d/%d' % (self.nu, self.de)

    def __add__(self, other):  
        other = to_Rational(other)
        ansn = self.nu*other.de + self.de*other.nu
        ansd = self.de*other.de
        if ansn > 0:
            if ansd > 0:
                anss = 1
            else:
                ansd = -ansd
                anss = -1
        else:
            ansn = -ansn
            if ansd > 0:
                anss = -1
            else:
                ansd = -ansd
                anss = 1
        ansgcd = gcd(ansn, ansd)
        ansn = anss*ansn/ansgcd
        ansd = ansd/ansgcd
        return Rational(ansn, ansd)
    
    def __sub__(self, other):  
        other = to_Rational(other)
        ansn = self.nu*other.de - self.de*other.nu
        ansd = self.de*other.de
        if ansn > 0:
            if ansd > 0:
                anss = 1
            else:
                ansd = -ansd
                anss = -1
        else:
            ansn = -ansn
            if ansd > 0:
                anss = -1
            else:
                ansd = -ansd
                anss = 1
        ansgcd = gcd(ansn, ansd)
        ansn = anss*ansn/ansgcd
        ansd = ansd/ansgcd
        return Rational(ansn, ansd)
    
    def __mul__(self, other):  
        other = to_Rational(other)
        ansn = self.nu*other.nu
        ansd = self.de*other.de
        if ansn > 0:
            if ansd > 0:
                anss = 1
            else:
                ansd = -ansd
                anss = -1
        else:
            ansn = -ansn
            if ansd > 0:
                anss = -1
            else:
                ansd = -ansd
                anss = 1
        ansgcd = gcd(ansn, ansd)
        ansn = anss*ansn/ansgcd
        ansd = ansd/ansgcd
        return Rational(ansn, ansd)
    
    def __truediv__(self, other):  
        other = to_Rational(other)
        if other.nu == 0:
            raise ZeroDivisionError('Error: division by 0')
        ansn = self.nu*other.de
        ansd = self.de*other.nu
        if ansn > 0:
            if ansd > 0:
                anss = 1
            else:
                ansd = -ansd
                anss = -1
        else:
            ansn = -ansn
            if ansd > 0:
                anss = -1
            else:
                ansd = -ansd
                anss = 1
        ansgcd = gcd(ansn, ansd)
        ansn = anss*ansn/ansgcd
        ansd = ansd/ansgcd
        return Rational(ansn, ansd)
    
    def __eq__(self, other):  
        other = to_Rational(other)
        selfn = self.nu
        selfd = self.de
        othern = other.nu
        otherd = other.de
        if selfn > 0:
            if selfd > 0:
                selfs = 1
            else:
                selfd = -selfd
                selfs = -1
        else:
            selfn = -selfn
            if selfd > 0:
                selfs = -1
            else:
                selfd = -selfd
                selfs = 1
        if othern > 0:
            if otherd > 0:
                others = 1
            else:
                otherd= -otherd
                others = -1
        else:
            othern = -othern
            if otherd > 0:
                others = -1
            else:
                otherd = -otherd
                others = 1
        if selfn == othern and selfd == otherd and selfs == others:
            return True
        else: return False
        
    def __ne__(self, other):  
        if self.__eq__(other) is True:
            return False
        else: return True
        
    def __gt__(self, other):  
        other = to_Rational(other)
        if self.__sub__(other).nu > 0:
            return True
        else: return False
        
    def __lt__(self, other):  
        other = to_Rational(other)
        if self.__sub__(other).nu < 0:
            return True
        else: return False
        
    def __ge__(self, other):  
        other = to_Rational(other)
        if self.__lt__(other) is True:
            return False
        else: return True
        
    def __le__(self, other):  
        other = to_Rational(other)
        if self.__gt__(other) is True:
            return False
        
        else: return True
def test():
    testsuite = [
        ('Rational(2, 3) + Rational(-70, 40)',
          Rational(-13, 12)),
        ('Rational(-20, 3) - Rational(120, 470)',
          Rational(-976,141)),
        ('Rational(-6, 19) * Rational(-114, 18)',
          Rational(2, 1)),
        ('Rational(-6, 19) / Rational(-114, -28)',
          Rational(-28,361)),

        ('Rational(-6, 19) == Rational(-14, 41)', False),
        ('Rational(-6, 19) != Rational(-14, 41)', True),
        ('Rational(6, -19) > Rational(14, -41)', True),
        ('Rational(-6, 19) < Rational(-14, 41)', False),
        ('Rational(-6, 19) >= Rational(-14, 41)', True),
        ('Rational(6, -19) <= Rational(14, -41)', False),
        ('Rational(-15, 8) == Rational(120, -64)', True),
    ]
    for t in testsuite:
        try:
            result = eval(t[0])
        except:
            print('Error in evaluating ' + t[0]); continue

        if result != t[1]:
            print('Error:  %s != %s' % (t[0], t[1]))
            
def is_Rational(obj):
    return hasattr(obj, 'nu') and hasattr(obj, 'de')

def to_Rational(obj):
    if is_Rational(obj):
        return obj  
    elif isinstance(obj, tuple):  
        if len(obj) <= 2:  
            return Rational(*obj)  
        else:
            raise TypeError('Error: <= 2 numbers expected')
    else:
        return Rational(obj)
if __name__ == '__main__':
    test()