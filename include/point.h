#ifndef POINT_H
#define POINT_H

class EllipticCurve;

class Point {
public:
    int x() const;
    int y() const;

    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
    Point operator+(const Point &other);
    Point operator*(const int n);

    friend class EllipticCurve;

protected:
    Point();

private:
    EllipticCurve *m_curve;
    int m_x;
    int m_y;

    Point(EllipticCurve *curve, const int x, const int y);

    int lambda(const int yq, const int yp, const int xq, const int xp) const;
    int lambda(const int xp, const int yp) const;

};

#endif
