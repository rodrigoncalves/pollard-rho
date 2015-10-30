#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

#include "point.h"

class EllipticCurve {
public:
    EllipticCurve(const int field, const int A, const int B);

    int field() const;
    int A() const;
    int B() const;
    Point point(const int x, const int y);

private:
    int m_field;
    int m_A;
    int m_B;
    
};

#endif
