/*
 * Class that represents a Point at Infinity
 *
 * Author: Rodrigo
 * Date: 01/11/2015
 * License: LGPL. No copyright.
 */
#ifndef POINT_INFINITY
#define POINT_INFINITY

class Point;

class PointAtInfinity : public Point
{
public:
    bool isInfinite() const;

    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;

    Point operator+(const Point &other) const;
    Point operator*(const BigInt &n) const;
    Point operator-(const Point &P) const;
    PointAtInfinity operator-() const;
    
};

#endif
