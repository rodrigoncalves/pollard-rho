# -*- coding: UTF-8 -*-

from libnum.modular import invmod
from random import SystemRandom

def serial(E, P, Q):
    print 'serial'

    c = []; d = []; R = []
    n = E.order()
    L = 4
    gen = SystemRandom()

    for i in range(L):
        c.append(gen.randrange(n))
        d.append(gen.randrange(n))
        R.append(P*c[-1] + Q*d[-1])

    an = gen.randrange(n)
    bn = gen.randrange(n)
    am = an
    bm = bn
    Xn = P*an + Q*bn
    Xm = Xn

    while (True):
        i = __H(Xn, L)
        Xn += R[i]
        an += c[i]
        bn += d[i]

        if not __debug__:
            print "i = " +  str(i)
            print "Xn = (" +  str(Xn.x) +  ", " +  str(Xn.y) + ")"
            print "an = " +  str(an)
            print "bn = " +  str(bn)
            print '---------------------------------------'

        for j in range(2):
            h = __H(Xm, L)
            Xm += R[h]
            am += c[h]
            bm += d[h]

        if Xn == Xm:
            break

    if (bn == bm):
        raise ArithmeticError("Indefined value")

    f = an-am
    g = invmod(bm-bn, n)
    ret = (f * g) % n
    return (ret + n) % n

def __H(P, L):
    return P.x % L
