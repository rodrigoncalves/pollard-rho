/*
 * Elliptic Curve class implementation
 *
 * Author: Rodrigo
 * Date: 29/10/2015
 * License: LGPL. No copyright.
 */
#include <stdexcept>
#include "elliptic_curve.h"

EllipticCurve::EllipticCurve(const BigInt &A, const BigInt &B, \
							 const BigInt &field, const BigInt &order)
    : m_A(A), m_B(B), m_field(field), m_order(order) {}

BigInt
EllipticCurve::A() const { return m_A; }

BigInt
EllipticCurve::B() const { return m_B; }

BigInt
EllipticCurve::field() const { return m_field; }

BigInt
EllipticCurve::order() const { return m_order; }

Point
EllipticCurve::point(const BigInt &x, const BigInt &y)
{
    if ((y * y) % m_field == (x*x*x + m_A*x + m_B) % m_field)
    {
        return Point(this, x, y);
    }

    throw std::invalid_argument("Point does not belong to curve");
}
