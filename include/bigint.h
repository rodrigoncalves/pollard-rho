/*
 * Class that represents a Big Integer
 *
 * Author: Rodrigo
 * Date: 30/10/2015
 * License: LGPL. No copyright.
 */
#ifndef BIGINT_H
#define BIGINT_H

#include <gmp.h>
#include <gmpxx.h>

#define DEFAULT_CONVERSION_BASE 10

class BigInt
{
public:
    BigInt();
    BigInt(const mpz_class &value);
    BigInt(const mpz_t &value);
    BigInt(const BigInt &value);
    BigInt(const int &value);

    BigInt pow(const BigInt &e) const;
    BigInt pow(const unsigned long int &e) const;
    BigInt pow_mod_p(const BigInt &e, const BigInt &p) const;
    BigInt gcd(const BigInt &other) const;
    BigInt invMod(const BigInt &mod) const;

    BigInt& operator=(const std::string &value);
    BigInt& operator=(const int &value);
    BigInt& operator=(const unsigned int &value);
    BigInt& operator=(const long &value);
    BigInt& operator=(const unsigned long &value);

    friend bool operator==(const BigInt &a, const BigInt &b);
    friend bool operator==(const BigInt &a, const long int &b);
    friend bool operator!=(const BigInt &a, const BigInt &b);
    friend bool operator>=(const BigInt &a, const BigInt &b);
    friend bool operator>(const BigInt &a, const BigInt &b);
    friend bool operator<(const BigInt &a, const BigInt &b);
    friend bool operator<=(const BigInt &a, const BigInt &b);

    friend BigInt operator+(const BigInt &a, const BigInt &b);
    friend BigInt operator+(const BigInt &a, const long &b);
    friend BigInt operator-(const BigInt &a);
    friend BigInt operator-(const BigInt &a, const BigInt &b);
    friend BigInt operator-(const BigInt &a, const long &b);
    friend BigInt operator*(const BigInt &a, const BigInt &b);
    friend BigInt operator*(const BigInt &a, const long &b);
    friend BigInt operator/(const BigInt &a, const BigInt &b);
    friend BigInt operator/(const BigInt &a, const long &b);
    friend BigInt operator%(const BigInt &a, const BigInt &b);
    friend BigInt operator%(const BigInt &a, const long &b);

    friend BigInt& operator+=(BigInt &a, const BigInt &b);
    friend BigInt& operator+=(BigInt &a, const long &b);
    friend BigInt& operator-=(BigInt &a, const BigInt &b);
    friend BigInt& operator-=(BigInt &a, const long &b);
    friend BigInt& operator*=(BigInt &a, const BigInt &b);
    friend BigInt& operator*=(BigInt &a, const long &b);
    friend BigInt& operator/=(BigInt &a, const BigInt &b);
    friend BigInt& operator/=(BigInt &a, const long &b);
    friend BigInt& operator%=(BigInt &a, const BigInt &b);
    friend BigInt& operator%=(BigInt &a, const long &b);

    friend BigInt& operator++(BigInt &a);
    friend BigInt operator++(BigInt &a, int dummy);
    friend BigInt& operator--(BigInt &a);
    friend BigInt operator--(BigInt &a, int dummy);

    friend std::ostream& operator<<(std::ostream &os, const BigInt &val);

protected:
    mpz_class m_value;
    static int m_conversionBase;
    
};

#endif
