/*
 * BigInt class implementation
 *
 * Author: Rodrigo
 * Date: 30/10/2015
 * License: LGPL. No copyright.
 */
#include <sstream>
#include "bigint.h"

using std::stringstream;

int BigInt::m_conversionBase = DEFAULT_CONVERSION_BASE;

BigInt::BigInt()
{
    m_value = mpz_class(0);
}

BigInt::BigInt(const mpz_class &value)
{
    m_value = mpz_class(value);
}

BigInt::BigInt(const mpz_t &value)
{
    m_value = mpz_class(value);
}

BigInt::BigInt(const BigInt &other)
{
    m_value = mpz_class(other.m_value);
}

BigInt::BigInt(const int &value)
{
    m_value = mpz_class(value);
}

BigInt
BigInt::power(const BigInt &e) const
{
    stringstream str;
    str << e;
    unsigned long ui;
    str >> ui;
    return power(ui);
}

BigInt
BigInt::power(const unsigned long int &e) const
{
    mpz_t rop;
    mpz_init(rop);
    mpz_pow_ui(
        rop,                    // result
        m_value.get_mpz_t(),    // base
        e                       // exp
    );
    BigInt res(rop);
    mpz_clear(rop);
    return res;
}

BigInt
BigInt::powerMod(const BigInt &e, const BigInt &p) const
{
    mpz_t rop;
    mpz_init(rop);
    mpz_powm_sec(
          rop,                      // result
          m_value.get_mpz_t(),      // base
          e.m_value.get_mpz_t(),    // exponent
          p.m_value.get_mpz_t()     // modulo
    );
    BigInt res(rop);
    mpz_clear(rop);
    return res;
}


BigInt
BigInt::gcd(const BigInt &other) const
{
    mpz_t rop;
    mpz_init(rop);
    mpz_gcd(rop, m_value.get_mpz_t(), other.m_value.get_mpz_t());
    BigInt res(rop);
    mpz_clear(rop);
    return res;
}

BigInt
BigInt::invMod(const BigInt &mod) const
{
    mpz_t rop;
    mpz_init(rop);
    mpz_invert(rop, m_value.get_mpz_t(), mod.m_value.get_mpz_t());
    BigInt res(rop);
    mpz_clear(rop);
    return res;
}

/* Assignments */
BigInt& BigInt::operator=(const std::string &value)
{
    m_value = mpz_class(value, BigInt::m_conversionBase);
    return *this;
}

BigInt& BigInt::operator=(const int &value)
{
    m_value = mpz_class(value);
    return *this;
}

BigInt& BigInt::operator=(const unsigned int &value)
{
    m_value = mpz_class(value);
    return *this;
}

BigInt& BigInt::operator=(const long &value)
{
    m_value = mpz_class(value);
    return *this;
}

BigInt& BigInt::operator=(const unsigned long &value)
{
    m_value = mpz_class(value);
    return *this;
}

bool operator==(const BigInt &a, const BigInt &b)
{
    int res = mpz_cmp(a.m_value.get_mpz_t(), b.m_value.get_mpz_t());
    return res == 0;
}

bool operator==(const BigInt &a, const long int &b)
{
    int res = mpz_cmp_si(a.m_value.get_mpz_t(), b);
    return res == 0;
}

bool operator!=(const BigInt &a, const BigInt &b)
{
    int res = mpz_cmp(a.m_value.get_mpz_t(), b.m_value.get_mpz_t());
    return res != 0;
}

bool operator>=(const BigInt &a, const BigInt &b)
{
    int res = mpz_cmp(a.m_value.get_mpz_t(), b.m_value.get_mpz_t());
    return res >= 0;
}

bool operator>(const BigInt &a, const BigInt &b)
{
    int res = mpz_cmp(a.m_value.get_mpz_t(), b.m_value.get_mpz_t());
    return res > 0;
}

bool operator<(const BigInt &a, const BigInt &b)
{
    int res = mpz_cmp(a.m_value.get_mpz_t(), b.m_value.get_mpz_t());
    return res < 0;
}

bool operator<=(const BigInt &a, const BigInt &b)
{
    int res = mpz_cmp(a.m_value.get_mpz_t(), b.m_value.get_mpz_t());
    return res >= 0;
}

BigInt operator+(const BigInt &a, const BigInt &b)
{
    BigInt c;
    c.m_value = a.m_value + b.m_value;
    return c;
}

BigInt operator+(const BigInt &a, const long &b)
{
    BigInt c;
    c.m_value = a.m_value + b;
    return c;
}

BigInt operator-(const BigInt &a)
{
    return a * -1;
}

BigInt operator-(const BigInt &a, const BigInt &b)
{
    BigInt c;
    c.m_value = a.m_value - b.m_value;
    return c;
}

BigInt operator-(const BigInt &a, const long &b)
{
    BigInt c;
    c.m_value = a.m_value - b;
    return c;
}

BigInt operator*(const BigInt &a, const BigInt &b)
{
    BigInt c;
    c.m_value = a.m_value * b.m_value;
    return c;
}

BigInt operator*(const BigInt &a, const long &b)
{
    BigInt c;
    c.m_value = a.m_value * b;
    return c;
}

BigInt operator/(const BigInt &a, const BigInt &b)
{
    BigInt c;
    c.m_value = a.m_value / b.m_value;
    return c;
}

BigInt operator/(const BigInt &a, const long &b)
{
    BigInt c;
    c.m_value = a.m_value / b;
    return c;
}

BigInt operator%(const BigInt &a, const BigInt &b)
{
    BigInt res(a.m_value % b.m_value);
    return res;
}

BigInt operator%(const BigInt &a, const long &b)
{
    BigInt res(a.m_value % b);
    return res;
}

BigInt& operator+=(BigInt &a, const BigInt &b)
{
    a.m_value += b.m_value;
    return a;
}

BigInt& operator+=(BigInt &a, const long &b)
{
    a.m_value += b;
    return a;
}

BigInt& operator-=(BigInt &a, const BigInt &b)
{
    a.m_value -= b.m_value;
    return a;
}

BigInt& operator-=(BigInt &a, const long &b)
{
    a.m_value -= b;
    return a;
}

BigInt& operator*=(BigInt &a, const BigInt &b)
{
    a.m_value *= b.m_value;
    return a;
}

BigInt& operator*=(BigInt &a, const long &b)
{
    a.m_value *= b;
    return a;
}

BigInt& operator/=(BigInt &a, const BigInt &b)
{
    a.m_value /= b.m_value;
    return a;
}

BigInt& operator/=(BigInt &a, const long &b)
{
    a.m_value /= b;
    return a;
}

BigInt& operator%=(BigInt &a, const BigInt &b)
{
    a.m_value = a.m_value % b.m_value;
    return a;
}

BigInt& operator%=(BigInt &a, const long &b)
{
    a.m_value = a.m_value % b;
    return a;
}

BigInt& operator++(BigInt &a)
{
    a.m_value = mpz_class(a.m_value + 1);
    return a;
}

BigInt operator++(BigInt &a, int)
{
    BigInt tmp(a);
    a.m_value = mpz_class(a.m_value + 1);
    return tmp;
}

BigInt& operator--(BigInt &a)
{
    a.m_value = mpz_class(a.m_value - 1);
    return a;
}

BigInt operator--(BigInt &a, int)
{
    BigInt tmp(a);
    a.m_value = mpz_class(a.m_value - 1);
    return tmp;
}

std::ostream& operator<<(std::ostream &os, const BigInt &val)
{
    os << val.m_value.get_str(BigInt::m_conversionBase);
    return os;
}
