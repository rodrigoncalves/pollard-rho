#include <iostream>
#include <time.h>
#include <string>
#include "elliptic_curve.h"
#include "pollard_rho.h"
#include "utils.h"

using namespace std;
using namespace PollardRho;

void write_results(int, string&);

int main(int argc, char **argv)
{
    BigInt p, A, B, order, Px, Py, Qx, Qy;
    BigInt x;
    int nbits;

    if (argc >= 10)
    {
        nbits = stoi(argv[1]);
        A = argv[2]; B = argv[3]; p = argv[4]; order = argv[5];
        Px = argv[6]; Py = argv[7];
        Qx = argv[8]; Qy = argv[9];
    }
    else
    {
        nbits = 32;
        A = 48489; B = 97594; p = 2882746957; order = 2882734229;
        Px = 1366664103; Py = 1798920923;
        Qx = 2702135874; Qy = 2667016446;
    }

    EllipticCurve E(A, B, p, order);
    Point P = E.point(Px, Py);
    Point Q = E.point(Qx, Qy);

    cout << "nbits = " << nbits << "\n";
    cout << "E = (A: " << A << ", B: " << B << ", p: " << p << ", order: " \
         << order << ")\n";
    cout << "P = (" << P.x() << ", " << P.y() << ")\n";
    cout << "Q = (" << Q.x() << ", " << Q.y() << ")\n";

    while (1)
    {
        try {
            clock_t start = clock();

            x = parallel(E, P, Q);

            clock_t end = clock();
            string time = format_time(end-start);

            if (x == 0) continue;

            cout << "x = " << x << endl;
            cout << "Time execution: " << time << "\n";

            if (P*x == Q) {
                cout << "Correct!\n";
                write_results(nbits, time);
                break;
            } else {
                cout << "Wrong!\n";
            }
        } catch (std::exception &e) {
            cerr << e.what() << endl;
        }
    }

    return 0;
}

void write_results(int nbits, string &time)
{
    FILE *fp = fopen("results.txt", "a");
    char msg[50];
    memset(msg, 0, 50);
    sprintf(msg, "Bits: %d\nTime execution: %s", nbits, time.c_str());
    fputs(msg, fp);
    fclose(fp);
}
