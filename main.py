# -*- coding: UTF-8 -*-

from ecc.model import *
from pollardrho import *

if __name__ == '__main__':
    E = EllipticCurve(47, 34, 10)
    P = E.point(30, 26)
    Q = E.point(35, 41)
    R = P + Q

    x = original(E, P, Q)
    x = serial(E, P, Q)
    x = parallelized(E, P, Q)

    print x
