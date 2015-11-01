/*
 * Class that represents a Point
 *
 * Author: Rodrigo
 * Date: 29/10/2015
 * License: LGPL. No copyright.
 */
#ifndef POINT_H
#define POINT_H

#include "bigint.h"

class EllipticCurve;

class Point
{
public:
    bool isInfinite() const;
    BigInt x() const;
    BigInt y() const;

    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
    Point operator+=(const Point &other);
    Point operator+(const Point &other) const;
    Point operator*(const BigInt &n) const;
    Point operator-() const;

    friend class EllipticCurve;

protected:
    Point();

private:
    EllipticCurve *m_curve;
    BigInt m_x;
    BigInt m_y;

    Point(EllipticCurve *curve, const BigInt x, const BigInt y);

    BigInt lambda(const Point &P, const Point &Q) const;
    BigInt lambda(const Point &P) const;

};

#endif
