#include <NTL/ZZ.h>
#include "point.h"
#include "elliptic_curve.h"

using namespace NTL;

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
    a = (yq - yp) % m_curve->field();
    if (a > m_curve->field()) a %= m_curve->field();
    b = xq - xp;

    int aux;
    a < 0 ? aux = -a : aux = a;
    d = (int) GCD(aux, b);

    a /= d; b /= d;
    a = (a + m_curve->field()) % m_curve->field();
    if (a % b)
    {
        b = (int) InvMod(b, m_curve->field());
        return a * b % m_curve->field();
    }

    return a / b;
}

int
Point::lambda(const int xp, const int yp) const
{
    int a, b, d;
    a = (3*xp*xp + m_curve->A());
    if (a > m_curve->field()) a %= m_curve->field();
    b = 2*yp;

    int aux;
    a < 0 ? aux = -a : aux = a;
    d = (int) GCD(aux, b);

    a /= d; b /= d;
    a = (a + m_curve->field()) % m_curve->field();
    if (a % b)
    {
        b = (int) InvMod(b, m_curve->field());
        return a * b % m_curve->field();
    }

    return a / b;
}

bool
Point::operator==(const Point &other) const {
    return m_x == other.m_x and m_y == other.m_y;
}

bool
Point::operator!=(const Point &other) const {
    return m_x != other.m_x or m_y != other.m_y;
}

Point
Point::operator+(const Point &other)
{
    Point R;
    int delta;

    if (*this == other)
        delta = lambda(m_x, m_y);
    else
        delta = lambda(other.m_y, m_y, other.m_x, m_x);

    int kx = (delta * delta - m_x - other.m_x) % m_curve->field();
    int ky = (delta * (m_x - kx) - m_y) % m_curve->field();

    R.m_curve = m_curve;
    R.m_x = kx<0 ? kx + m_curve->field() : kx;
    R.m_y = ky<0 ? ky + m_curve->field() : ky;

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
