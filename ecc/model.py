# -*- coding: UTF-8 -*-

from point.model import Point
import sage.all as sg

class EllipticCurve(object):
    def __init__(self, field, A, B, order=None):
        self.field = field
        self.A = A
        self.B = B
        self.order = self.__calc_order(order)

    def point(self, x, y):
        if self.__is_valid(x, y):
            return Point(self, x, y)

        raise ValueError("Point does not belong to curve")

    def nbits(self):
        nbits = 0
        field = self.field
        while (field):
            field >>= 1
            nbits += 1
        return nbits

    def __calc_order(self, order):
        if order:
            return order

        E = sg.EllipticCurve(sg.GF(self.field), [self.A, self.B])
        return E.cardinality()

    def __is_valid(self, x, y):
        return (y**2) % self.field == (x**3 + self.A * x + self.B) % self.field

    def __repr__(self):
        return '(A:{self.A}, B:{self.B}, p:{self.field}, order:{self.order})'.format(self=self)
