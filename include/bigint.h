#ifndef BIGINT_H
#define BIGINT_H

#include <NTL/ZZ.h>

class BigInt
{
public:
    BigInt();

    BigInt& operator=(const std::string &value);
    BigInt& operator=(const int &value);
    BigInt& operator=(const unsigned int &value);
    BigInt& operator=(const long &value);
    BigInt& operator=(const unsigned long &value);

private:
    ZZ m_value;
    
};

#endif