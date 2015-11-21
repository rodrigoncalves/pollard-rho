#include <iostream>
#include "elliptic_curve.h"
#include "pollard_rho.h"

using namespace std;

int main()
{
    int p, A, B;

    // p = 47; A = 34; B = 10;
    // EllipticCurve E(p, A, B);
    // Point P = E.point(30, 26);
    // Point Q = E.point(35, 41);

    // p = 229; A = 1; B = 44;
    // EllipticCurve E(p, A, B);
    // Point P = E.point(5, 116);
    // Point Q = E.point(155, 166);

    p = 7919; A = 1001; B = 75;
    EllipticCurve E(p, A, B);
    Point P = E.point(4023, 6036);
    Point Q = E.point(4135, 3169);

    BigInt x = pollardRho_original(E, P, Q);
    cout << "P = (" << P.x() << ", " << P.y() << ")\n";
    cout << "Q = (" << Q.x() << ", " << Q.y() << ")\n";
    cout << "x = " << x << endl;

    return 0;
}
