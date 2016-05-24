# -*- coding: UTF-8 -*-

from libnum.modular import invmod
from random import SystemRandom
from multiprocessing import *
import multiprocessing as mp

L = 64
c = []; d = []; R = []
client_pipe, server_pipe = Pipe()

def client_func(E, P, Q):
    n = E.order
    gen = SystemRandom()
    a = gen.randrange(n)
    b = gen.randrange(n)
    X = P*a + Q*b

    while (True):
        if (__isDistinguished(E, X, L)):
            arg = (a, b, X)
            sendToServer(arg)

        i = __H(X, L)
        X += R[i]
        a += c[i]
        b += d[i]

def sendToServer(arg):
    client_pipe.send(arg)

def server_func(n, return_dict):
    triples = {}
    triple_collided = []

    while (True):
        arg = server_pipe.recv()

        a = arg[0]; b = arg[1]; P = arg[2]
        P = str(P)

        if (triples.has_key(P)):
            triple_collided = arg
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

    return_dict[0] = x

def multiprocess(E, P, Q):
    print 'Algorithm: multiprocess'

    n = E.order
    gen = SystemRandom()

    for i in range(L):
        c.append(gen.randrange(n))
        d.append(gen.randrange(n))
        R.append(P*c[-1] + Q*d[-1])

    # create manager with the return value
    manager = Manager()
    return_dict = manager.dict()

    # create the server
    server = Process(name='server', target=server_func, args=(n, return_dict))
    cores = mp.cpu_count()
    workers = []

    # create the processes
    for i in range(cores):
        w = Process(name='worker_'+str(i+1), target=client_func, args=(E, P, Q))
        workers.append(w)
        w.start()

    server.start()
    server.join() # wait server end

    # kill the processes
    for w in workers:
        w.terminate()

    # empty lists
    del c[:], d[:], R[:], workers[:]

    x = return_dict[0]
    return x

def __H(P, L):
    return P.x % L

def __isDistinguished(E, P, L):
    return P.y < (E.field // L)
