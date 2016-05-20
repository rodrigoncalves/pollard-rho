# -*- coding: UTF-8 -*-

from libnum.modular import invmod
from random import SystemRandom
from multiprocessing import *
from multiprocessing.connection import Listener, Client
from send_email import format_time
from sage.rings.integer_ring import ZZ
import multiprocessing as mp

c = []; d = []; R = []
workers = []

def client_func(E, P, Q):
    L = 4
    n = E.order
    gen = SystemRandom()
    a = gen.randrange(n)
    b = gen.randrange(n)
    X = P*a + Q*b
    am = a
    bm = b
    Xm = X

    while (True):
        if (__isDistinguished(E, X, L)):
            arg = (a, b, X)
            sendToServer(arg)

        i = __H(X, L)
        X += R[i]
        a += c[i]
        b += d[i]

        for j in range(2):
            h = __H(Xm, L)
            Xm += R[h]
            am += c[h]
            bm += d[h]

        if X == Xm:
            break

    if (b == bm):
        raise ArithmeticError('Indefined value')

    f = a-am
    g = invmod(bm-b, n)
    ret = (f * g) % n
    x = (ret + n) % n

    sendToServer(x)

def server_func(n, return_dict):
    address = ('localhost', 6000)
    listener = Listener(address)

    triples = {}
    triple_collided = []

    while (True):
        conn = listener.accept()

        # Receive triple (a, b, P) from client
        arg = conn.recv()

        if (arg in ZZ):
            return_dict[0] = arg
            killProcesses()
            return

        a = arg[0]; b = arg[1]; P = arg[2]
        P = str(P)

        if (triples.has_key(P)):
            triple_collided = arg
            killProcesses()
            break

        triples[P] = [a, b]

    am = triple_collided[0]
    bm = triple_collided[1]
    P = str(triple_collided[2])
    an = triples.get(P)[0]
    bn = triples.get(P)[1]

    if (bn == bm):
        raise ArithmeticError('Indefined value')

    f = an-am
    g = invmod(bm-bn, n)
    ret = (f * g) % n
    x = (ret + n) % n

    conn.close()
    listener.close()
    print 'Server Done!'
    return_dict[0] = x

def sendToServer(arg):
    address = ('localhost', 6000)
    conn = Client(address)
    conn.send(arg)
    conn.close()

def killProcesses():
    for w in workers:
        w.terminate()

def multiprocess(E, P, Q):
    print 'multiprocess'

    n = E.order
    L = 4
    gen = SystemRandom()

    for i in range(L):
        c.append(gen.randrange(n))
        d.append(gen.randrange(n))
        R.append(P*c[-1] + Q*d[-1])

#------ for each M processor -----#
    manager = Manager()
    return_dict = manager.dict()

    server = Process(name='server', target=server_func, args=(n, return_dict))

    cores = mp.cpu_count()
    for i in range(cores):
        w = Process(name='worker_'+str(i+1), target=client_func, args=(E, P, Q))
        workers.append(w)
        w.start()

    server.start()
    server.join()

    x = return_dict[0]
    return x

def __H(P, L):
    return P.x % L

def __isDistinguished(E, P, L):
    return P.y < (E.field // L)
