//Sagi Muki
// Created by roeyby on 8/27/19.
//

#ifndef CPP_EX1_GFNUMBER_H
#define CPP_EX1_GFNUMBER_H

#include <stdio.h>
#include <vector>
#include "GField.h"

using namespace std;

class GFNumber
{
private:
    long _n;
    GField _field;
public:
    GFNumber();

    explicit GFNumber(long n);

    explicit GFNumber(long n, GField field);

    GFNumber(const GFNumber& number);

    long getNumber() const;

    GField& getField() const;

    std::vector<GFNumber> getPrimeFactors()const;

    void getPrimeFactorsHelper(long num, long div, vector<GFNumber> vec);

    void printFactors()const;

    bool getIsPrime()const;

    GFNumber& operator=(GFNumber);

    GFNumber& operator+(GFNumber) const;

    GFNumber& operator+=(GFNumber);

    GFNumber& operator-(GFNumber)const;

    GFNumber& operator-=(GFNumber);

    GFNumber& operator*(GFNumber)const;

    GFNumber& operator*=(GFNumber);

    GFNumber& operator%(GFNumber)const;

    GFNumber& operator%=(GFNumber);

    bool operator==(GFNumber)const;

    bool operator!=(GFNumber)const;

    bool operator<(GFNumber)const;

    bool operator<=(GFNumber)const;

    bool operator>(GFNumber)const;

    bool operator>=(GFNumber)const;

    // for longs

    GFNumber& operator+(long)const;

    GFNumber& operator+=(long);

    GFNumber& operator-(long)const;

    GFNumber& operator-=(long);

    GFNumber& operator*(long)const;

    GFNumber& operator*=(long);

    GFNumber& operator%(long)const;

    GFNumber& operator%=(long);

};

ostream & operator << (ostream &out, const GFNumber &GFN) ;

istream & operator >> (istream &in,  GFNumber &GFN) ;

#endif //CPP_EX1_GFNUMBER_H
