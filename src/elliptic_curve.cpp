#include <NTL/ZZ.h>
#include <stdexcept>
#include "elliptic_curve.h"

using namespace NTL;

/* Point */
Point::Point() : m_curve(nullptr), m_x(0), m_y(0) {}

Point::Point(EllipticCurve *curve, const int x, const int y)
    : m_curve(curve), m_x(x), m_y(y) {}

int
Point::x() const { return m_x; }

int
Point::y() const { return m_y; }

int
Point::lambda(const int yq, const int yp, const int xq, const int xp) const
{
    int a, b, d;
    a = (yq - yp) % m_curve->p();
    if (a > m_curve->p()) a %= m_curve->p();
    b = xq - xp;

    int aux;
    a < 0 ? aux = -a : aux = a;
    d = (int) GCD(aux, b);

    a /= d; b /= d;
    a = (a + m_curve->p()) % m_curve->p();
    if (a % b)
    {
        b = (int) InvMod(b, m_curve->p());
        return a * b % m_curve->p();
    }

    return a / b;
}

int
Point::lambda(const int xp, const int yp) const
{
    int a, b, d;
    a = (3*xp*xp + m_curve->A());
    if (a > m_curve->p()) a %= m_curve->p();
    b = 2*yp;

    int aux;
    a < 0 ? aux = -a : aux = a;
    d = (int) GCD(aux, b);

    a /= d; b /= d;
    a = (a + m_curve->p()) % m_curve->p();
    if (a % b)
    {
        b = (int) InvMod(b, m_curve->p());
        return a * b % m_curve->p();
    }

    return a / b;
}

Point
Point::operator+(const Point &Q)
{
    Point R;
    int delta;

    if (m_x == Q.m_x and m_y == Q.m_y) // if P == Q
        delta = lambda(m_x, m_y);
    else
        delta = lambda(Q.m_y, m_y, Q.m_x, m_x);

    int kx = (delta * delta - m_x - Q.m_x) % m_curve->p();
    int ky = (delta * (m_x - kx) - m_y) % m_curve->p();

    R.m_curve = m_curve;
    R.m_x = kx<0 ? kx + m_curve->p() : kx;
    R.m_y = ky<0 ? ky + m_curve->p() : ky;

    return R;
}

Point
Point::operator*(const int n)
{
    Point P = *this;
    for (int i=0; i<n-1; i++)
        P = P + *this;

    return P;
}

/* Elliptic Curve */
EllipticCurve::EllipticCurve(const int p, const int A, const int B)
    : m_p(p), m_A(A), m_B(B) {}

int
EllipticCurve::p() const { return m_p; }

int
EllipticCurve::A() const { return m_A; }

int
EllipticCurve::B() const { return m_B; }

Point
EllipticCurve::point(const int x, const int y) {
    if ((y * y) % m_p == (x*x*x + m_A*x + m_B) % m_p) {
        Point P(this, x, y);
        return P;
    } else {
        throw std::invalid_argument("Point does not belong to curve");
    }
}
