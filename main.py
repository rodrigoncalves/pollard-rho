# -*- coding: UTF-8 -*-

from ecc.model import *

if __name__ == '__main__':
    E = EllipticCurve(47, 34, 10)
    P = E.point(30, 26)
    Q = E.point(35, 41)
    R = P + Q
