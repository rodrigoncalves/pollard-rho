#include <iostream>
#include <vector>
#include <NTL/ZZ.h>
#include "elliptic_curve.h"

// #define DEBUG

using namespace std;

BigInt pollardRho(const EllipticCurve&, const Point&, const Point&);

int main()
{
    int p, A, B;

    p = 47; A = 34; B = 10;
    EllipticCurve E(p, A, B);
    Point P = E.point(30, 26);
    Point Q = E.point(35, 41);

    // p = 229; A = 1; B = 44;
    // EllipticCurve E(p, A, B);
    // Point P = E.point(5, 116);
    // Point Q = E.point(155, 166);

    BigInt x = pollardRho(E, P, Q);
    cout << "P = (" << P.x() << ", " << P.y() << ")\n";
    cout << "Q = (" << Q.x() << ", " << Q.y() << ")\n";
    cout << "x = " << x << endl;

    return 0;
}

BigInt pollardRho(const EllipticCurve&, const Point &P, const Point &Q)
{
    int n = 41;
    // int n = 239;
    // int n = E.order();

    std::vector<Point> v;
    Point R = P;
    v.push_back(R);

    std::vector<BigInt> a, b;
    a.push_back(1);
    b.push_back(0);
    BigInt am, an, bm, bn;
    for (int i = 0; i < 100; ++i)
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
    }

    BigInt c = an-am;
    BigInt d = (bm-bn).invMod(n);
    BigInt res = (c * d) % n;
    return res < 0 ? res + n : res;
}
