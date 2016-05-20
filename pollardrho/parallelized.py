# -*- coding: UTF-8 -*-

import threading
from libnum.modular import invmod
from random import SystemRandom


c = []; d = []; R = []
L = 32
gen = SystemRandom()
match = False
points = {}
lock = threading.Lock()
coefficients = []
n = 0
matchPoint = 0

def _initializeGlobalVars():
    global c, d, R, L, gen, match, points, lock, coefficients, n, matchPoint
    c = []; d = []; R = []
    L = 32
    gen = SystemRandom()
    match = False
    points = {}
    lock = threading.Lock()
    coefficients = []
    n = 0
    matchPoint = 0

def generate_points(E, P, Q, L):
    global points, lock, match, coefficients, matchPoint, n
    an = gen.randrange(n)
    bn = gen.randrange(n)
    Xn = P*an + Q*bn
    while True:
        if __isDistinguished(E, Xn, L):
            ct = threading.currentThread().getName()
            #print "{}: x = {}, y = {}\n".format(ct, Xn.x, Xn.y)
            pstr = str(Xn)
            lock.acquire()
            if match == True:
                break

            if pstr in points.keys():
                match = True
                matchPoint = Xn
                #print "Thread {} found a match in point {}".format(ct, pstr)
                coefficients = [an, bn]
                break

            #print threading.currentThread().getName() + ' inserted {}-{}'.format(Xn, [an, bn])
            points[pstr] = [an, bn]
            lock.release()

        i = __H(Xn, L)
        Xn += R[i]
        an = (an + c[i]) % n
        bn = (bn + d[i]) % n

    lock.release()

def parallelized(E, P, Q, numThreads):
    print 'parallelized'
    _initializeGlobalVars()

    global n, matchPoint, points
    n = E.order
    #print "Order is {}".format(n)

    for i in range(L):
        #print "branch created"
        c.append(gen.randrange(n))
        d.append(gen.randrange(n))
        R.append(P*c[-1] + Q*d[-1])

    threads = []
    for i in range(numThreads):
        #print "thread created"
        trName = "tr{}".format(i)
        tr = threading.Thread(target=generate_points, args=(E, P, Q, L,), name=trName)
        threads.append(tr)
        tr.start()

    for tr in threads:
        tr.join()

   # print points.items()
   # print "Match in {}".format(matchPoint)
    mstr = "({}, {})".format(matchPoint.x, matchPoint.y)
    if points.has_key(mstr):
        l = points.get(mstr)

    if (coefficients[1] == l[1]):
        raise ArithmeticError("Indefined value")

    f = l[0] - coefficients[0]
    g = invmod(coefficients[1]-l[1], n)
    ret = (f * g) % n
    return (ret + n) % n

def __H(P, L):
    return P.x % L

def __isDistinguished(E, P, L):
    f = E.field
    limit = f // L
    return P.y < limit
