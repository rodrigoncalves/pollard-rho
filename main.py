# -*- coding: UTF-8 -*-

from ecc.model import *
from pollardrho.original import *
from pollardrho.serial import *
from pollardrho.parallelized import *


if __name__ == '__main__':
#    E = EllipticCurve(47, 34, 10)
#    P = E.point(30, 26)
#    Q = E.point(35, 41)

    E = EllipticCurve(229, 1, 44)
    P = E.point(5, 116)
    Q = E.point(155, 166)

    # x = original(E, P, Q)
    # x = serial(E, P, Q)
    x = parallelized(E, P, Q, 4)

    print 'E = ' + str(E)
    print 'P = ' + str(P)
    print 'Q = ' + str(Q)
    print 'x = ' + str(x)
