/*
 * Point class implementation
 *
 * Author: Rodrigo
 * Date: 29/10/2015
 * License: LGPL. No copyright.
 */
#include <NTL/ZZ.h>
#include "point.h"
#include "elliptic_curve.h"

using namespace NTL;

Point::Point() : m_curve(nullptr), m_x(0), m_y(0) {}

Point::Point(EllipticCurve *curve, const BigInt x, const BigInt y)
    : m_curve(curve), m_x(x), m_y(y) {}

BigInt
Point::x() const { return m_x; }

BigInt
Point::y() const { return m_y; }

BigInt
Point::lambda(const Point &P, const Point &Q) const
{
    BigInt a, b, d;
    a = (Q.y() - P.y()) % m_curve->field();
    if (a > m_curve->field())
    {
        a %= m_curve->field();
    }

    b = Q.x() - P.x();

    BigInt aux;
    a < 0 ? aux = -a : aux = a;
    d = aux.gcd(b);

    a /= d; b /= d;
    a = (a + m_curve->field()) % m_curve->field();
    if (a % b != 0)
    {
        b = b.invMod(m_curve->field());
        return a * b % m_curve->field();
    }

    return a / b;
}

BigInt
Point::lambda(const Point &P) const
{
    BigInt a, b, d;
    a = (3*P.x()*P.x() + m_curve->A());
    if (a > m_curve->field())
    {
        a %= m_curve->field();
    }

    b = 2*P.y();

    BigInt aux;
    a < 0 ? aux = -a : aux = a;
    d = aux.gcd(b);

    a /= d; b /= d;
    a = (a + m_curve->field()) % m_curve->field();
    if (a % b != 0)
    {
        b = b.invMod(m_curve->field());
        return a * b % m_curve->field();
    }

    return a / b;
}

bool
Point::operator==(const Point &other) const
{
    return m_x == other.m_x and m_y == other.m_y;
}

bool
Point::operator!=(const Point &other) const
{
    return m_x != other.m_x or m_y != other.m_y;
}

Point
Point::operator+(const Point &other)
{
    Point R;
    BigInt delta;

    delta = *this == other ? lambda(*this) : delta = lambda(*this, other);

    BigInt kx = (delta * delta - m_x - other.m_x) % m_curve->field();
    BigInt ky = (delta * (m_x - kx) - m_y) % m_curve->field();

    R.m_curve = m_curve;
    R.m_x = kx<0 ? kx + m_curve->field() : kx;
    R.m_y = ky<0 ? ky + m_curve->field() : ky;

    return R;
}

Point
Point::operator*(const BigInt &n)
{
    Point P = *this;
    for (BigInt i=0; i<n-1; i++)
    {
        P = P + *this;
    }

    return P;
}
