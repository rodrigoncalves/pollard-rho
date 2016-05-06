# -*- coding: UTF-8 -*-

from ecc.model import *
from pollardrho.original import *
from pollardrho.serial import *
from pollardrho.parallelized import *
from send_email import *
import time

if __name__ == '__main__':
    start = time.time()

    # E = EllipticCurve(47, 34, 10)
    # P = E.point(30, 26)
    # Q = E.point(35, 41)

    # E = EllipticCurve(229, 1, 44)
    # P = E.point(5, 116)
    # Q = E.point(155, 166)

    # E = sg.EllipticCurve(sg.GF(3753773003), [41779, 81105])
    # P = E(1670032921, 3055253653)
    # Q = E(1040263251, 2395225033)

    E = EllipticCurve(3753773003, 41779, 81105)
    P = E.point(1670032921, 3055253653)
    Q = E.point(1040263251, 2395225033)

    # E = EllipticCurve(9455936384496576011,99923,27117)
    # P = E.point(489939106417691453,2796796515663053905)
    # Q = E.point(1379000454301407843,8095052157961271430)

    print 'E = ' + str(E)
    print 'P = ' + str(P)
    print 'Q = ' + str(Q)

    # x = original(E, P, Q)
    # x = parallelized(E, P, Q, 4)
    x = serial(E, P, Q)
    # x = P.discrete_log(Q)

    print 'x = ' + str(x)

    end = time.time()
    timer = end-start

    nbits = 32
    send_email(E, P, Q, x, nbits, timer, "serial", 0)
