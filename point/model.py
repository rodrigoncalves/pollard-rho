# -*- coding: UTF-8 -*-

from fractions import gcd
from libnum.modular import invmod

class Point(object):
    def __init__(self, curve=None, x=None, y=None):
        if curve is not None:
            self.curve = curve
            self.x = x
            self.y = y
    
    def is_infinit(self):
        return False

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __ne__(self, other):
        return self.x != other.x or self.y != other.y

    def __add__(self, other):
        delta = (self == other and _lambda(self)) or _lambda(self, other)

        kx = (delta ** 2 - self.x - other.x) % self.curve.field
        ky = (delta * (self.x - kx) - self.y) % self.curve.field

        R = Point()
        R.curve = self.curve
        R.x = (kx < 0 and kx + self.curve.field) or kx
        R.y = (ky < 0 and ky + self.curve.field) or ky
        return R

    def __iadd__(self, other):
        return self.__eq__(self.__add__(other))

    def __str__(self):
        return 'Point({self.x}, {self.y})'.format(self=self)

def _lambda(P, Q=None):
    if Q is None:
        a = (3*P.x*P.x + P.curve.A)
        if (a > P.curve.field):
            a %= P.curve.field

        b = 2*P.y
        aux = abs(a)
        d = gcd(aux, b)

        a /= d; b /= d
        a = (a + P.curve.field) % P.curve.field
        if (a % b != 0):
            # b = b.invMod(P.curve.field)
            b = invmod(b, P.curve.field)
            print str(b) + " 1"
            return a * b % P.curve.field

        return a / b
    else:
        a = (Q.y - P.y) % P.curve.field
        if (a > P.curve.field):
            a %= P.curve.field

        b = Q.x - P.x

        aux = abs(a)
        d = gcd(aux, b)

        a /= d; b /= d
        a = (a + P.curve.field) % P.curve.field
        if (a % b != 0):
            # b = b.invMod(P.curve.field)
            b = invmod(b, P.curve.field)
            print str(b) + " 2"
            return a * b % P.curve.field

        return a / b
