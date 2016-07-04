/*
 * Class that represents an Elliptic Curve
 *
 * Author: Rodrigo
 * Date: 29/10/2015
 * License: LGPL. No copyright.
 */
#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

#include "point.h"

class EllipticCurve
{
public:
    EllipticCurve(const BigInt &A, const BigInt &B, \
                  const BigInt &field, const BigInt &order);

    BigInt A() const;
    BigInt B() const;
    BigInt field() const;
    BigInt order() const;
    Point point(const BigInt &x, const BigInt &y);

private:
    BigInt m_A;
    BigInt m_B;
    BigInt m_field;
    BigInt m_order;
};

#endif
