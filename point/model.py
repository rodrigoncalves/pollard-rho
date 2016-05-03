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
        return self + other

    def __sub__(self, other):
        return Point(self.curve, self.x, -self.y)

    def __mul__(self, n):
        P = self
        for i in range(n - 1):
            P += self
        return P

    def __repr__(self):
        return '({self.x}, {self.y})'.format(self=self)

def _lambda(P, *args):
    if len(args):
        Q = args[0]
        a = (Q.y - P.y) % P.curve.field
        if (a > P.curve.field):
            a %= P.curve.field

        b = Q.x - P.x

        aux = abs(a)
        d = gcd(aux, b)

        a /= d; b /= d
        a = (a + P.curve.field) % P.curve.field
        if (a % b != 0):
            b = invmod(b, P.curve.field)
            return a * b % P.curve.field

        return a / b
    else:
        a = (3*P.x*P.x + P.curve.A)
        if (a > P.curve.field):
            a %= P.curve.field

        b = 2*P.y
        aux = abs(a)
        d = gcd(aux, b)

        a /= d; b /= d
        a = (a + P.curve.field) % P.curve.field
        if (a % b != 0):
            b = invmod(b, P.curve.field)
            return a * b % P.curve.field

        return a / b

def _toBinary(n):
    """Returns a little endian binary representation of n into a list"""
    binary = []
    while n >= 1:
        rest = n % 2
        binary.append(rest)
        n = n // 2
    return binary
