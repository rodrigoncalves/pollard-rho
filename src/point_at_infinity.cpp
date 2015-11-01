/*
 * Point at Infinity class implementation
 *
 * Author: Rodrigo
 * Date: 01/11/2015
 * License: LGPL. No copyright.
 */
#include "point.h"
#include "point_at_infinity.h"

bool
PointAtInfinity::isInfinite() const { return true; }

bool
PointAtInfinity::operator==(const Point &other) const { return other.isInfinite(); }

bool
PointAtInfinity::operator!=(const Point &other) const { return not other.isInfinite(); }

Point
PointAtInfinity::operator+(const Point &other) const { return other; }

Point
PointAtInfinity::operator*(const BigInt &) const { return PointAtInfinity(); }

Point
PointAtInfinity::operator-(const Point &P) const { return -P; }

PointAtInfinity
PointAtInfinity::operator-() const { return PointAtInfinity(); }
