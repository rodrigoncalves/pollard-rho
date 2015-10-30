/*
 * Elliptic Curve class implementation
 *
 * Author: Rodrigo
 * Date: 29/10/2015
 * License: LGPL. No copyright.
 */
#include <stdexcept>
#include "elliptic_curve.h"

EllipticCurve::EllipticCurve(const BigInt field, const BigInt A, const BigInt B)
    : m_field(field), m_A(A), m_B(B) {}

BigInt
EllipticCurve::field() const { return m_field; }

BigInt
EllipticCurve::A() const { return m_A; }

BigInt
EllipticCurve::B() const { return m_B; }

Point
EllipticCurve::point(const BigInt x, const BigInt y)
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
