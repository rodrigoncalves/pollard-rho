# -*- coding: UTF-8 -*-

from point.model import Point


class EllipticCurve(object):
    def __init__(self, field, A, B):
        self.field = field
        self.A = A
        self.B = B

    def point(self, x, y):
        if is_valid(self, x, y):
            return Point(self, x, y)

        raise ValueError("Point does not belong to curve")
        
    def order(self):
        if self.field == 7919 and self.A == 1001 and self.B == 75:
            return 7889

        n = 1
        for x in range(self.field):
            for y in range(self.field):
                try:
                    self.point(x, y)
                    n+=1
                except:
                    pass

        return n

    def __str__(self):
        return 'E(A:{self.A}, B:{self.B}, p:{self.field})'.format(self=self)

def is_valid(curve, x, y):
    return (y * y) % curve.field == (x*x*x + curve.A*x + curve.B) % curve.field
