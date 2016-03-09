/*
 * Implementation of Pollard's rho algorithm (Single Processor)
 *
 * Author: Rodrigo
 * Date: 31/10/2015
 * License: LGPL. No copyright.
 */
#include <iostream>
#include <vector>
#include "bigint.h"
#include "elliptic_curve.h"
#include "point.h"
#include "pollard_rho.h"

BigInt H(Point&, BigInt&);

BigInt
PollardRho::serial(EllipticCurve &E, const Point &P, const Point &Q) throw()
{
    BigInt L=4, k;
    BigInt an, bn;
    BigInt am, bm;
    std::vector<BigInt> c, d;
    std::vector<Point> R;

    k = E.order();

    for (int i = 0; i <= L; ++i)
    {
        c.push_back(BigInt::random() % k);
        d.push_back(BigInt::random() % k);
        R.push_back(P*c.back() + Q*d.back());
    }

    an = BigInt::random() % k;
    bn = BigInt::random() % k;
    am = an;
    bm = bn;
    Point Xn = P*an + Q*bn;
    Point Xm = Xn;

    do
    {
        int i = H(Xn, L).get_ui();
        Xn += R[i];
        an += c[i];
        bn += d[i];
    } while (Xn != Xm);

    if (bn == bm)
    {
        throw std::domain_error("Indefined value");
    }

    BigInt f = an-am;
    BigInt g = (bm-bn).invMod(k);
    BigInt ret = (f * g) % k;
    return ret < 0 ? ret + k : ret;
}

BigInt H(Point &P, BigInt &L)
{
    return P.x() % (L + 1);
}
