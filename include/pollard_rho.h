/*
 * Pollard's rho algorithms
 *
 * Author: Rodrigo
 * Date: 31/10/2015
 * License: LGPL. No copyright.
 */
#ifndef POLLARD_RHO_H
#define POLLARD_RHO_H

namespace PollardRho
{
    BigInt original(EllipticCurve &E, const Point &P, const Point &Q) throw();
    BigInt serial(EllipticCurve &E, const Point &P, const Point &Q) throw();
    BigInt parallel(EllipticCurve &E, Point &P, Point &Q) throw();
}

BigInt H(Point&, BigInt&);

class Params
{
public:
    EllipticCurve *E; Point *P; Point *Q;

    Params() : E(0), P(0), Q(0) {}

    Params(EllipticCurve &_E, Point &_P, Point &_Q)
        : E(&_E), P(&_P), Q(&_Q) {}
};

class Args
{
public:
    BigInt a; BigInt b; Point P;

    Args() {}

    Args(BigInt _a, BigInt _b, Point _P)
        : a(_a), b(_b), P(_P) {}
};

struct pipe_arg
{
    char a[50];
    char b[50];
    char x[50];
    char y[50];
};

#endif
