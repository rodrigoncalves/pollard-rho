#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

#include "point.h"

class EllipticCurve {
public:
    EllipticCurve(const BigInt field, const BigInt A, const BigInt B);

    BigInt field() const;
    BigInt A() const;
    BigInt B() const;
    Point point(const BigInt x, const BigInt y);

private:
    BigInt m_field;
    BigInt m_A;
    BigInt m_B;
    
};

#endif
