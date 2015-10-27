#include <iostream>
#include <vector>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int A, B, p;

int lambda(int yq, int yp, int xq, int xp)
{
    int a, b, d;
    a = (yq - yp) % p;
    if (a > p) a%=p;
    b = xq - xp;

    int aux;
    a < 0 ? aux = -a : aux = a;
    d = (int) GCD(aux, b);

    a /= d; b /= d;
    a = (a+p)%p;
    if (a % b) 
    {
        b = (int) InvMod(b, p);
        return a * b % p;
    }

    return a / b;
}

int lambda(int xp, int yp)
{
    int a, b, d;
    a = (3*xp*xp + A);
    if (a > p) a%=p;
    b = 2*yp;

    int aux;
    a < 0 ? aux = -a : aux = a;
    d = (int) GCD(aux, b);

    a /= d; b /= d;
    a = (a+p)%p;
    if (a % b) 
    {
        b = (int) InvMod(b, p);
        return a * b % p;
    }

    return a / b;
}

class Point
{
public:
    int x; int y;

    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    Point operator+(Point Q)
    {
        Point R;
        int delta;

        if (x == Q.x and y == Q.y) // if P == Q
            delta = lambda(x, y);
        else
            delta = lambda(Q.y, y, Q.x, x);
        
        int kx = (delta * delta - x - Q.x) % p;
        int ky = (delta * (x - kx) - y) % p;

        R.x = kx<0 ? kx+p : kx;
        R.y = ky<0 ? ky+p : ky;

        return R;
    }

    Point operator*(int n)
    {
        Point P = Point(x, y);
        for (int i=0; i<n-1; i++)
            P = P + Point(x, y);

        return P;
    }
};

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
    Point P = Point(5, 116);
    Point Q = Point(155, 166);

    std::vector<Point> v;
    Point R = P; v.push_back(R);

    std::vector<int> a, b;
    a.push_back(1);
    b.push_back(0);
    int am, an, bm, bn;
    for (int i = 0; i < 100; ++i)
    {
        cout << i << " | a: " << a.back() << " | b: " << b.back();
        int y = v.back().y;
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
        // v.push_back(P*a.back() + Q*b.back());
        cout << " | S:" << o;
        cout << "\t | (" << v[i].x << ", " << v[i].y << ")\n";

        if (v[i].x == v[i/2].x and v[i].y == v[i/2].y and i > 2 and i%2 == 0) {
            cout << "ACHOU! " << i << ": (" << v[i].x << ", " << v[i].y << ")\n";
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

    for (int i=0; i<v.size(); i++)
    {
        // cout << i << ": (" << v[i].x << ", " << v[i].y << ")\n";

    }
    // cout << i << ": (" << R.x << ", " << R.y << ")\n";

    return 0;
}
