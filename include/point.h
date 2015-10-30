#ifndef POINT_H
#define POINT_H

#include "bigint.h"

class EllipticCurve;

class Point {
public:
    BigInt x() const;
    BigInt y() const;

    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
    Point operator+(const Point &other);
    Point operator*(const BigInt n);

    friend class EllipticCurve;

protected:
    Point();

private:
    EllipticCurve *m_curve;
    BigInt m_x;
    BigInt m_y;

    Point(EllipticCurve *curve, const BigInt x, const BigInt y);

    BigInt lambda(const BigInt yq, const BigInt yp, const BigInt xq, const BigInt xp) const;
    BigInt lambda(const BigInt xp, const BigInt yp) const;

};

#endif
