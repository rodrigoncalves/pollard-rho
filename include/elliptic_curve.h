#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

#include "point.h"

class EllipticCurve {
public:
    EllipticCurve(const int p, const int A, const int B);

    int A() const;
    int B() const;
    int p() const;
    Point point(const int x, const int y);

private:
    int m_p;
    int m_A;
    int m_B;
    
};

#endif
