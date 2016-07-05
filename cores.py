# -*- coding: UTF-8 -*-

from ecc.model import *
from email.mime.text import MIMEText
from pollardrho.original import *
from pollardrho.serial import *
from pollardrho.parallelized import *
from pollardrho.multiprocess import *
from send_email import *
from datetime import datetime
import csv
import time

def main(args):
    nbits = int(args[0])
    A = int(args[1])
    B = int(args[2])
    p = int(args[3])
    order = int(args[4])
    Px = int(args[5])
    Py = int(args[6])
    Qx = int(args[7])
    Qy = int(args[8])

    if nbits != 40:
        return

    E = EllipticCurve(p, A, B, order)
    P = E.point(Px, Py)
    Q = E.point(Qx, Qy)

    print 'Bits =', nbits
    print 'E =', E
    print 'P =', P
    print 'Q =', Q

    for n in xrange(100):
        print '#', n+1
        start = time.time()
        x = multiprocess(E, P, Q)
        print 'x = ', x

        if (P*x != Q):
            print 'Wrong!'
            continue

        print 'Correct!'
        end = time.time()
        runtime = end - start
        format_time(runtime)
        f = open('results_cores.txt', 'a')
        s = str(int(runtime)) + ','
        f.write(s)
        f.close()

        print 'Tempo de execução: ', format_time(runtime)
        print '\n---------------------------------------\n'

if __name__ == '__main__':
    with open('curves.csv', 'r') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=',')
        spamreader.next()
        for row in spamreader:
            if not len(row):
                break
            main(row)
