#!/usr/bin/env sage -python

import sage.all as sg
import random

def genCurve(bits):
    p = sg.next_prime(random.randint(2**(bits-1), 2**(bits)))

    order = 0
    while not(sg.is_prime(order)) or order == p or order == p+1:
        A = random.randint(1, 10**5)
        B = random.randint(1, 10**5)
        if (4*A**3 + 27*B**2) % p != 0:   ## Avoid singular curves ##
            E = sg.EllipticCurve(sg.GF(p), [A,B])
            order = E.cardinality()

    P = E.random_point()
    Q = E.random_point()

    f = open("curves.csv", "a")
    f.write(str(bits)+",")
    f.write(str(A)+",")
    f.write(str(B)+",")
    f.write(str(p)+",")
    f.write(str(order)+",")
    f.write(str(P.xy()[0])+","+str(P.xy()[1])+",")
    f.write(str(Q.xy()[0])+","+str(Q.xy()[1])+"\n")
    f.close()

if __name__ == '__main__':
    f = open("curves.csv", "w")
    f.write("bits,A,B,p,order,P.x,P.y,Q.x,Q.y\n")
    f.close()
    for bits in xrange(32,161):
        print "bits: " + str(bits)
        genCurve(bits)
