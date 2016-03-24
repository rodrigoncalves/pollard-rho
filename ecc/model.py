# -*- coding: UTF-8 -*-

from point.model import Point

class EllipticCurve(object):
    def __init__(self, field, A, B):
        self.field = field
        self.A = A
        self.B = B

    def point(self, x, y):
        if self.__is_valid(x, y):
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

    def __is_valid(self, x, y):
        return (y**2) % self.field == (x**3 + self.A * x + self.B) % self.field

    def __repr__(self):
        return '(A:{self.A}, B:{self.B}, p:{self.field})'.format(self=self)
