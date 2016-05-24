# -*- coding: UTF-8 -*-

from ecc.model import *
from pollardrho.original import *
from pollardrho.serial import *
from pollardrho.parallelized import *
from pollardrho.multiprocess import *
from send_email import *
import csv
import time

def main(args):
    start = time.time()

    nbits = int(args[0])
    A = int(args[1])
    B = int(args[2])
    p = int(args[3])
    order = int(args[4])
    Px = int(args[5])
    Py = int(args[6])
    Qx = int(args[7])
    Qy = int(args[8])

    E = EllipticCurve(p, A, B, order)
    P = E.point(Px, Py)
    Q = E.point(Qx, Qy)

    # E = EllipticCurve(47, 34, 10)
    # P = E.point(30, 26)
    # Q = E.point(35, 41)

    # E = EllipticCurve(229, 1, 44)
    # P = E.point(5, 116)
    # Q = E.point(155, 166)

    print 'Bits =', nbits
    print 'E =', E
    print 'P =', P
    print 'Q =', Q

    while (True):
        try:
            # x = original(E, P, Q)
            # x = parallelized(E, P, Q, 16)
            # x = serial(E, P, Q)
            x = multiprocess(E, P, Q)
            # x = P.discrete_log(Q)
            print 'x =', x
            break
        except Exception, e:
            print 'Error:', str(e)

    print 'Correct!' if (P*x == Q) else 'Wrong!'

    end = time.time()
    timer = end - start

    print 'Tempo de execução: ', format_time(timer)
    send_email(E, P, Q, x, nbits, timer, 'multiprocess', 0)
    print '\n---------------------------------------\n'

if __name__ == '__main__':
    with open('curves.csv', 'r') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=',')
        spamreader.next()
        for row in spamreader:
            if not len(row):
                break
            main(row)
