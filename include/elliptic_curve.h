#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

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
    Point(EllipticCurve *curve, const int x, const int y);

    int lambda(const int yq, const int yp, const int xq, const int xp) const;
    int lambda(const int xp, const int yp) const;

    EllipticCurve *m_curve;
    int m_x;
    int m_y;
};

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
