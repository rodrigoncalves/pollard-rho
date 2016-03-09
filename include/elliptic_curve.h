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
    EllipticCurve(const BigInt &field, const BigInt &A, const BigInt &B);

    BigInt field() const;
    BigInt A() const;
    BigInt B() const;
    Point point(const BigInt &x, const BigInt &y) throw();
    BigInt order();

private:
    BigInt m_field;
    BigInt m_A;
    BigInt m_B;
};

#endif
