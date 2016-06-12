#include <iostream>
#include "elliptic_curve.h"
#include "pollard_rho.h"
#include <time.h>
#include <string>

using namespace std;
using namespace PollardRho;

int main(int argc, char **argv)
{
    srand(time(NULL));

    BigInt p, A, B, order, Px, Py, Qx, Qy;
    BigInt x;

    int nbits = stoi(argv[1]);
    A = argv[2];
    B = argv[3];
    p = argv[4];
    order = argv[5];
    Px = argv[6]; 
    Py = argv[7]; 
    Qx = argv[8]; 
    Qy = argv[9]; 

    // p = 47; A = 34; B = 10;
    // EllipticCurve E(p, A, B);
    // Point P = E.point(30, 26);
    // Point Q = E.point(35, 41);

    // p = 229; A = 1; B = 44;
    // EllipticCurve E(p, A, B);
    // Point P = E.point(5, 116);
    // Point Q = E.point(155, 166);

    // p = 7919; A = 1001; B = 75;
    // EllipticCurve E(p, A, B);
    // Point P = E.point(4023, 6036);
    // Point Q = E.point(4135, 3169);

    EllipticCurve E(p, A, B, order);
    Point P = E.point(Px, Py);
    Point Q = E.point(Qx, Qy);

    cout << "\n\nnbits = " << nbits << "\n";
    cout << "E(A: " << A << ", B: " << B << ", p: " << p << ", order: " \
         << order << ")\n";
    cout << "P = (" << P.x() << ", " << P.y() << ")\n";
    cout << "Q = (" << Q.x() << ", " << Q.y() << ")\n";

    try
    {
        // x = original(E, P, Q);
        x = serial(E, P, Q);
        cout << "x = " << x << endl;
    }
    catch (std::exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
