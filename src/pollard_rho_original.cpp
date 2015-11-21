/*
 * Implementation of Pollard's rho algorithm (Original)
 *
 * Author: Rodrigo
 * Date: 31/10/2015
 * License: LGPL. No copyright.
 */
#include "bigint.h"
#include "elliptic_curve.h"
#include "point.h"
#include "pollard_rho.h"
#include <iostream>
#include <vector>

// #define DEBUG

using namespace std;

BigInt pollardRho_original(EllipticCurve &E, const Point &P, const Point &Q)
{
    BigInt n = E.order();

    std::vector<Point> v;
    Point R = P;
    v.push_back(R);

    vector<BigInt> a, b;
    a.push_back(1);
    b.push_back(0);
    BigInt am, an, bm, bn;
    unsigned long i = 0;

    while (1)
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

        if (v[i].x() == v[i/2].x() and v[i].y() == v[i/2].y() and i > 2 and i%2 == 0)
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

        i++;
    }

    BigInt c = an-am;
    BigInt d = (bm-bn).invMod(n);
    BigInt res = (c * d) % n;
    return res < 0 ? res + n : res;
}
