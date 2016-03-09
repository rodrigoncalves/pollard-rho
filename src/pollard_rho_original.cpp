/*
 * Implementation of Pollard's rho algorithm (Original)
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

using namespace std;

BigInt
PollardRho::original(EllipticCurve &E, const Point &P, const Point &Q) throw()
{
    BigInt n, am, an, bm, bn;
    vector<BigInt> a, b;
    vector<Point> v;
    unsigned long i = 0;
    Point R = P;

    n = E.order();
    v.push_back(R);
    a.push_back(1);
    b.push_back(0);

    while (++i)
    {
        #ifdef DEBUG
            cout << i << " | a: " << a.back() << " | b: " << b.back();
            int s;
        #endif

        BigInt y = v.back().y();
        if (y >= 0 and y < 15)
        {
            v.push_back(v.back() + Q);
            a.push_back(a.back());
            b.push_back(b.back()+1);
            #ifdef DEBUG
                s=1;
            #endif
        }
        else if (y >= 15 and y < 30)
        {
            v.push_back(v.back()*2);
            a.push_back(2*a.back() % n);
            b.push_back(2*b.back() % n);
            #ifdef DEBUG
                s=2;
            #endif
        }
        else
        {
            v.push_back(v.back() + P);
            a.push_back(a.back()+1);
            b.push_back(b.back());
            #ifdef DEBUG
                s=3;
            #endif
        }

        #ifdef DEBUG
            cout << " | S:" << s;
            cout << "\t | (" << v[i].x() << ", " << v[i].y() << ")\n";
        #endif

        if (v[i].x() == v[i/2].x() and
            v[i].y() == v[i/2].y() and
            i > 2 and i % 2 == 0)
        {
            #ifdef DEBUG
                cout << "FOUND!\n" << i << ": (" << v[i].x() << ", " << v[i].y() << ")";
                cout << " and " << i/2 << ": (" << v[i/2].x() << ", " << v[i/2].y() << ")\n";
            #endif
            am = a[i/2];
            an = a[i];
            bm = b[i/2];
            bn = b[i];
            break;
        }
    }

    if (bm == bn)
    {
        throw std::domain_error("Indefined value");
    }

    BigInt c = an-am;
    BigInt d = (bm-bn).invMod(n);
    BigInt ret = (c * d) % n;
    return ret < 0 ? ret + n : ret;
}
