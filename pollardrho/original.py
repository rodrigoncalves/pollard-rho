# -*- coding: UTF-8 -*-

from libnum.modular import invmod

def original(E, P, Q):
    print 'Algorithm: original'

    a = []; b = []; v = []
    R = P

    n = E.order()
    v.append(R)
    a.append(1)
    b.append(0)

    i = 1
    while (True):
        # print str(i) + ' | a: ' + str(a[-1]) + ' | b: ' + str(b[-1]),
        # s = 0

        y = v[-1].y
        if (y >= 0 and y < 15):
            v.append(v[-1] + Q)
            a.append(a[-1])
            b.append(b[-1] + 1)
            # s = 1
        elif y >= 15 and y < 30:
            v.append(v[-1] * 2)
            a.append(2*a[-1] % n)
            b.append(2*b[-1] % n)
            # s = 2
        else:
            v.append(v[-1] + P)
            a.append(a[-1] + 1)
            b.append(b[-1])
            # s = 3

            # print ' | S:' + str(s),
            # print '\t| (' + str(v[i].x) + ', ' + str(v[i].y) + ')'

        if (v[i].x == v[i/2].x and
            v[i].y == v[i/2].y and
            i > 2 and i % 2 == 0):
            # print 'FOUND!\n' + str(i) + ': (' + str(v[i].x) + ', ' + str(v[i].y) + ')',
            # print 'and ' + str(i/2) + ': (' + str(v[i/2].x) + ', ' + str(v[i/2].y) + ')'
            am = a[i/2]
            an = a[i]
            bm = b[i/2]
            bn = b[i]
            break

        i += 1

    if bm == bn:
        raise ArithmeticError('Undefined value')

    c = an - am
    d = invmod(bm - bn, n)
    ret = (c * d) % n
    return (ret + n) % n
