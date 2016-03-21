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

bool isFound = false;

BigInt
PollardRho::parallelized(EllipticCurve &E, const Point &P, const Point &Q) throw()
{
    BigInt L(4), k(239);
    BigInt an, bn;
    BigInt am, bm;
    std::vector<BigInt> c, d;
    std::vector<Point> R;

    //k = E.order();

    for (int i = 0; i < L; ++i)
    {
        c.push_back(BigInt::random(k));
        d.push_back(BigInt::random(k));
        R.push_back(P*c.back() + Q*d.back());
    }


    // OBS: Paralelizar esse trecho de código
    //--------- Begin: Clientes --------------------
    an = BigInt::random(k);
    bn = BigInt::random(k);
    Point Xn = P*an + Q*bn;

    do
    {
        // if isDistinguished(Xn) { send_to_server(an, bn, Xn) }
        int i = H(Xn, L).get_ui();
        Xn += R[i];
        an += c[i];
        bn += d[i];

    } while (!isFound);
    // End: Clientes

    //--------- Begin: Servidor --------------------

    // recebe o ponto distinto Xn, an, bn
    if ( belongsTo(distinguishedPoints, Xn) )
    {
        isFound = true;
	// calcula o logaritmo discreto
    } else {
        // armazena Xn, an, bn
    }
    return discrete_log(an, am, bn, bm, k);
}

BigInt H(Point &P, BigInt &L)
{
    return P.x() % L;
}

BigInt discrete_log(BigInt &an, BigInt &am, BigInt &bn, BigInt &bm, BigInt &k)
{
    BigInt f = an-am;
    BigInt g = (bm-bn).invMod(k);
    BigInt ret = (f * g) % k;
    return ret < 0 ? ret + k : ret;
}
