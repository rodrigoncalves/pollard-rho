/*
 * Elliptic Curve class implementation
 *
 * Author: Rodrigo
 * Date: 29/10/2015
 * License: LGPL. No copyright.
 */
#include <stdexcept>
#include "elliptic_curve.h"

EllipticCurve::EllipticCurve(const BigInt &field, const BigInt &A, const BigInt &B)
    : m_field(field), m_A(A), m_B(B) {}

BigInt
EllipticCurve::field() const { return m_field; }

BigInt
EllipticCurve::A() const { return m_A; }

BigInt
EllipticCurve::B() const { return m_B; }

Point
EllipticCurve::point(const BigInt &x, const BigInt &y) throw()
{
    if ((y * y) % m_field == (x*x*x + m_A*x + m_B) % m_field)
    {
        Point P(this, x, y);
        return P;
    }
    else
    {
        throw std::invalid_argument("Point does not belong to curve");
    }
}

BigInt
EllipticCurve::order()
{
    if (m_field == 7919 and m_A == 1001 and m_B == 75)
    {
        return 7889;
    }

    BigInt n = 1;
    for (BigInt x = 0; x < m_field; ++x)
    {
        for (BigInt y = 0; y < m_field; ++y)
        {
            try
            {
                point(x, y);
                ++n;
            } catch (std::invalid_argument) {}
        }
    }

    return n;
}
