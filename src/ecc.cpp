#include <iostream>
#include <vector>
#include <NTL/ZZ.h>

#include "elliptic_curve.h"

using namespace std;
using namespace NTL;

int A, B, p;

int main()
{
    // A = 34; B = 10;
    // p = 47;
    // int n = 41;
    // Point P = Point(30, 26);
    // Point Q = Point(35, 41);

    A = 1; B = 44;
    p = 229;
    int n = 239;
    // Point P = Point(5, 116);
    // Point Q = Point(155, 166);
    EllipticCurve E(p, A, B);
    Point P = E.point(5, 116);
    Point Q = E.point(155, 166);

    std::vector<Point> v;
    Point R = P; v.push_back(R);

    std::vector<int> a, b;
    a.push_back(1);
    b.push_back(0);
    int am, an, bm, bn;
    for (int i = 0; i < 100; ++i)
    {
        cout << i << " | a: " << a.back() << " | b: " << b.back();
        int y = v.back().y();
        int o;
        if (y >= 0 and y < 15) {
            v.push_back(v.back() + Q);
            a.push_back(a.back());
            b.push_back(b.back()+1);
            o=1;
        }
        else if (y >= 15 and y < 30) {
            v.push_back(v.back()*2);
            a.push_back(2*a.back() % n);
            b.push_back(2*b.back() % n);
            o=2;
        }
        else {
            v.push_back(v.back() + P);
            a.push_back(a.back()+1);
            b.push_back(b.back());
            o=3;
        }
// cout << "-----" << endl;
        // v.push_back(P*a.back() + Q*b.back());
        cout << " | S:" << o;
        cout << "\t | (" << v[i].x() << ", " << v[i].y() << ")\n";

        if (v[i].x() == v[i/2].x() and v[i].y() == v[i/2].y() and i > 2 and i%2 == 0) {
            cout << "ACHOU! " << i << ": (" << v[i].x() << ", " << v[i].y() << ")\n";
            am = a[i/2];
            an = a[i];
            bm = b[i/2];
            bn = b[i];
            break;
        }
    }

    cout << "am: " << am << endl;
    cout << "an: " << an << endl;
    cout << "bm: " << bm << endl;
    cout << "bn: " << bn << endl;

    int x;
    x = (int) InvMod((bm-bn), n);

    cout << "(" << an << "-" << am << ")/(" << bm << "-" << bn << ")" << endl;

    cout << "Resposta: " << (int) MulMod(an-am, x, n) << endl;

    for (unsigned int i=0; i<v.size(); i++)
    {
        // cout << i << ": (" << v[i].x() << ", " << v[i].y() << ")\n";

    }
    // cout << i << ": (" << R.x() << ", " << R.y() << ")\n";

    return 0;
}
