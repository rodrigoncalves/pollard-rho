#include <stdexcept>
#include "elliptic_curve.h"

EllipticCurve::EllipticCurve(const int field, const int A, const int B)
    : m_field(field), m_A(A), m_B(B) {}

int
EllipticCurve::field() const { return m_field; }

int
EllipticCurve::A() const { return m_A; }

int
EllipticCurve::B() const { return m_B; }

Point
EllipticCurve::point(const int x, const int y) {
    if ((y * y) % m_field == (x*x*x + m_A*x + m_B) % m_field) {
        Point P(this, x, y);
        return P;
    } else {
        throw std::invalid_argument("Point does not belong to curve");
    }
}
