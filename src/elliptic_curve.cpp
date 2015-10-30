#include <stdexcept>
#include "elliptic_curve.h"

EllipticCurve::EllipticCurve(const int p, const int A, const int B)
    : m_p(p), m_A(A), m_B(B) {}

int
EllipticCurve::p() const { return m_p; }

int
EllipticCurve::A() const { return m_A; }

int
EllipticCurve::B() const { return m_B; }

Point
EllipticCurve::point(const int x, const int y) {
    if ((y * y) % m_p == (x*x*x + m_A*x + m_B) % m_p) {
        Point P(this, x, y);
        return P;
    } else {
        throw std::invalid_argument("Point does not belong to curve");
    }
}
