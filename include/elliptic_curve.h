#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

class EllipticCurve;

class Point {
public:
    int x();
    int y();

    Point operator+(Point Q);
    Point operator*(int n);

    friend class EllipticCurve;

protected:
    Point();

private:
    Point(EllipticCurve *curve, int x, int y);

    int lambda(int yq, int yp, int xq, int xp);
    int lambda(int xp, int yp);

    EllipticCurve *m_curve;
    int m_x;
    int m_y;
};

class EllipticCurve {
public:
    EllipticCurve(int p, int A, int B);

    int A();
    int B();
    int p();
    Point point(int x, int y);

private:
    int m_p;
    int m_A;
    int m_B;
    
};

#endif
