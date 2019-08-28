//
// Created by roeyby on 8/27/19.
//

#include "GField.h"
#include "GFNumber.h"
#include <cmath>

GField::GField() : _p(2), _l(1)
{}

GField::GField(long p, long l) : _p(p), _l(l)
{}

GField::GField(const GField& field)
{
    _p = field.getChar();
    _l = field.getDegree();
}

long GField::getChar() const
{ return _p; }

long GField::getDegree() const
{ return _l; }

long GField::getOrder() const
{ return (long) pow(_p, _l); }

bool GField::isPrime(long p)
{
    if ( p < 2 )
    { return false; }
    long d = 2;
    return GField::isPrimeHelper(p, d);
}

bool GField::isPrimeHelper(long p, long d)
{
    if ( d > sqrt(p))
    { return true; }
    else if ( p % d == 0 )
    { return false; }
    else
    { return isPrimeHelper(p, (d + 1)); }
}

GFNumber& GField::gcd(GFNumber a, GFNumber b) const
{
    long a1 = a.getNumber();
    long b1 = b.getNumber();
    long gcdNum = gcdHelper(a1, b1);
    GFNumber& num = *new GFNumber(gcdNum, a.getField());
    return num;
}

long GField::gcdHelper(long a, long b) const
{
    if ( a == 0 )
    { return b; }
    else if ( b == 0 )
    { return a; }

    else if ( a == b )
    { return a; }
    else if ( b < a )
    {
        return GField::gcdHelper(a - b, b);
    }
    else
    { return GField::gcdHelper(a, b - a); }
}

GFNumber& GField::createNumber(long k) const
{
    long num = k % _p;
    const GField& ref = *this;
    GFNumber& numberRef = *(new GFNumber(k, ref));
    return numberRef;
}

bool GField::operator==(const GField& field2) const
{
    return this->getOrder() == field2.getOrder();
}

// no need to overload. default is good enough

GField& GField::operator=(GField other)
{
    this->_p = other.getChar();
    this->_l = other.getDegree();
    return *this;
}

ostream& operator<<(ostream& out, const GField& GF)
{
    cout << "GF("<<GF.getChar()<<"**"<<GF.getDegree()<<")";
}

istream& operator>>(istream& in, GField& GF)
{
    long GFChar;
    long GFDegree;
    cin >> GFChar >> GFDegree;
    GF = * new GField(GFChar,GFDegree);

}