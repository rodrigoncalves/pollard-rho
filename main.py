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

    if nbits < 66:
        return

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
            start = time.time()
            now = datetime.now()
            moment = str(now.day)+'/'+str(now.month)+'/'+str(now.year)+' '\
            +str(now.hour)+':'+str(now.minute)+':'+str(now.second)
            print 'Started at', moment

            x = multiprocess(E, P, Q)

            print 'x =', x
            break
        except Exception, e:
            print 'Error:', str(e)

            end = time.time()
            timer = end - start
            runtime = format_time(timer)

            msg = MIMEText(
                'Máquina: HighTower\n'
                'Algoritmo: multiprocess\n'
                'Bits = ' + str(nbits) + ' bits\n'
                'E = '+ str(E) + '\n'
                'P: ' + str(P) + '\n'
                'Q: ' + str(Q) + '\n'
                'Tempo de execução: ' + runtime)
            msg['Subject'] = 'Erro detectado na curva de ' + str(nbits) + ' bits - HighTower'
            send_email(msg)
            print '---------------------------------------'

    end = time.time()
    timer = end - start
    runtime = format_time(timer)

    iscorrect = (P*x == Q and 'Correct!') or 'Wrong'
    print iscorrect
    print 'Tempo de execução: ', runtime

    msg = MIMEText(
        'Máquina: HighTower\n'
        'Algoritmo: multiprocess\n'
        'Bits = ' + str(nbits) + ' bits\n'
        'E = '+ str(E) + '\n'
        'P: ' + str(P) + '\n'
        'Q: ' + str(Q) + '\n'
        'x = ' + str(x) + '\n'
        'Distinguished point: 24-bit\n'
        + str(iscorrect) + '\n'
        'Tempo de execução: ' + runtime)
    msg['Subject'] = 'Quebra da curva de ' + str(nbits) + ' bits - HighTower'
    send_email(msg)
    print '\n---------------------------------------\n'

if __name__ == '__main__':
    with open('curves.csv', 'r') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=',')
        spamreader.next()
        for row in spamreader:
            if not len(row):
                break
            main(row)
