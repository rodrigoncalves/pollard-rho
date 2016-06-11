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

        for j in range(2):
            h = __H(Xm, L)
            Xm += R[h]
            am += c[h]
            bm += d[h]

        if Xn == Xm:
            break

    if (bn == bm):
        raise ArithmeticError('Undefined value')

    f = an-am
    g = invmod(bm-bn, n)
    ret = (f * g) % n
    ret = (ret + n) % n
    sendToServer(ret)

def sendToServer(arg):
    client_pipe.send(arg)

def server_func(n, return_dict):
    triples = {}
    triple_collided = []

    while (True):
        arg = server_pipe.recv()
        return_dict[0] = arg
        break

def parallelized(E, P, Q):
    print 'Algorithm: parallelized'

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
