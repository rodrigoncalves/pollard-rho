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

// #define DEBUG

BigInt _H(Point&, BigInt&);

BigInt
PollardRho::parallel(EllipticCurve &E, const Point &P, const Point &Q) throw()
{
    BigInt L(4), k;
    BigInt an, bn;
    BigInt am, bm;
    std::vector<BigInt> c, d;
    std::vector<Point> R;

    k = E.order();

    for (int i = 0; i < L; ++i)
    {
        c.push_back(BigInt::random(k));
        d.push_back(BigInt::random(k));
        R.push_back(P*c.back() + Q*d.back());
    }

    an = BigInt::random(k);
    bn = BigInt::random(k);
    am = an;
    bm = bn;
    Point Xn = P*an + Q*bn;
    Point Xm = Xn;

    do
    {
        int i = _H(Xn, L).get_ui();
        Xn += R[i];
        an += c[i];
        bn += d[i];

        #ifdef DEBUG
            std::cout << "i = " << i << "\n";
            std::cout << "Xn = (" << Xn.x() << ", " << Xn.y() <<")" << "\n";
            std::cout << "an = " << an << "\n";
            std::cout << "bn = " << bn << "\n";
        #endif

        for (int j = 0; j < 2; j++)
        {
            int h = _H(Xm, L).get_ui();
            Xm += R[h];
            am += c[h];
            bm += d[h];
        }
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

BigInt _H(Point &P, BigInt &L)
{
    return P.x() % L;
}
