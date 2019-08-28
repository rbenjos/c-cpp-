//
// Created by roeyby on 8/27/19.
//


#include <iostream>
#include <X11/X.h>

#ifndef CPP_EX1_GFIELD_H
#define CPP_EX1_GFIELD_H

using namespace std;
class GFNumber;

class GField
{
private:
    long _p;
    long _l;

    static bool isPrimeHelper(long p, long d) ;

public:
    GField();

    explicit GField(long p, long l = 1);

    GField(const GField& field);

    long getChar() const;

    long getDegree() const;

    long getOrder() const;

    static bool isPrime(long p) ;

    GFNumber& gcd(GFNumber a, GFNumber b) const;

    long gcdHelper(long a, long b) const;

    GFNumber& createNumber(long k) const;

    bool operator==(const GField& field2) const;

    // no need to overload. default is good enough

    GField& operator=(GField other);
};

ostream & operator << (ostream &out, const GField &GF) ;

istream & operator >> (istream &in,  GField &GF) ;

#endif //CPP_EX1_GFIELD_H
