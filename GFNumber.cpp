//
// Created by roeyby on 8/27/19.
//

#include "GFNumber.h"
#include "GField.h"
#include <iostream>

using namespace std;

GFNumber::GFNumber()
{
    _n = 0;
    GField field = *new GField;
    GField& field1 = field;
    _field = field;
}

GFNumber::GFNumber(long n)
{
    _n = n;
    _field = *new GField;

}

GFNumber::GFNumber(long n, GField field)
{
    _n = n;
    _field = field;
}

GFNumber::GFNumber(const GFNumber& number)
{
    if ( this == &number )
    {
    }
    this->_n = number.getNumber();
    this->_field = *new GField(number.getField());
}

long GFNumber::getNumber() const
{ return _n; }

GField& GFNumber::getField() const
{
    GField& ref = (GField&) _field;
    return ref;
}

std::vector<GFNumber> GFNumber::getPrimeFactors() const
{
//    long num = this->getNumber();
//    long div = 2;
//    vector<GFNumber> vec;
//    GFNumber::getPrimeFactorsHelper(num, div, vec);
//    return vec;
}

void GFNumber::getPrimeFactorsHelper(long num, long div, vector<GFNumber> vec)
{
//    if ( num & div == 0 )
//    {
//        GFNumber = new GFNumber(div,);
//        vec.insert();
//    }
}

void GFNumber::printFactors() const
{}

bool GFNumber::getIsPrime() const
{

}

GFNumber& GFNumber::operator=(GFNumber number2)
{
    this->_n = number2.getNumber();
    this->_field = number2.getField();
}

GFNumber& GFNumber::operator+(GFNumber other) const
{
    if ( other.getField() == this->getField())
    {
        long mod = this->getField().getChar();
        long num = (this->getNumber() + other.getNumber()) % mod;
        GFNumber& number3 = *new GFNumber(num, this->_field);
        return number3;
    }
    else
    {}//todo: handle error
}

GFNumber& GFNumber::operator+=(GFNumber other)
{
    if ( other.getField() == this->getField())
    {
        long mod = this->getField().getChar();
        long num = (this->getNumber() + other.getNumber()) % mod;
        this->_n = num;
        return *this;
    }
    else
    {}//todo: handle error
}

GFNumber& GFNumber::operator-(GFNumber other) const
{
//    if (other.getField() == this->getField())
    {
        long mod = this->getField().getChar();
        long num = (this->getNumber() - other.getNumber()) % mod;
        GFNumber& number3 = *new GFNumber(num, this->_field);
        return number3;
    }
//    else {}//todo: handle error

}

GFNumber& GFNumber::operator-=(GFNumber other)
{
    if ( other.getField() == this->getField())
    {
        long mod = this->getField().getChar();
        long num = (this->getNumber() - other.getNumber()) % mod;
        this->_n = num;
        return *this;
    }
    else
    {}//todo: handle error
}

GFNumber& GFNumber::operator*(GFNumber other) const
{
    if ( other.getField() == this->getField())
    {
        long mod = this->getField().getChar();
        long num = (this->getNumber() * other.getNumber()) % mod;
        GFNumber& number3 = *new GFNumber(num, this->_field);
        return number3;
    }
    else
    {}//todo: handle error
}

GFNumber& GFNumber::operator*=(GFNumber other)
{
    if ( other.getField() == this->getField())
    {
        long mod = this->getField().getChar();
        long num = (this->getNumber() * other.getNumber()) % mod;
        this->_n = num;
        return *this;
    }
    else
    {}//todo: handle error
}

GFNumber& GFNumber::operator%(GFNumber other) const
{
    if ( other.getField() == this->getField())
    {
        long mod = this->getField().getChar();
        long num = (this->getNumber() % other.getNumber()) % mod;
        GFNumber& number3 = *new GFNumber(num, this->_field);
        return number3;
    }
    else
    {}//todo: handle error
}

GFNumber& GFNumber::operator%=(GFNumber other)
{
    if ( other.getField() == this->getField())
    {
        long mod = this->getField().getChar();
        long num = (this->getNumber() % other.getNumber()) % mod;
        this->_n = num;
        return *this;
    }
    else
    {}//todo: handle error
}

bool GFNumber::operator==(GFNumber other) const
{
    if ( other.getField() == this->getField())
    {
        return (this->_n == other._n);
    }
    else
    { /*TODO: handle error*/ }
}

bool GFNumber::operator!=(GFNumber other) const
{
    if ( other.getField() == this->getField())
    {
        return (this->_n != other._n);
    }
    else
    { /*TODO: handle error*/ }
}

bool GFNumber::operator<(GFNumber other) const
{
    if ( other.getField() == this->getField())
    {
        return (this->_n < other._n);
    }
    else
    { /*TODO: handle error*/ }
}

bool GFNumber::operator<=(GFNumber other) const
{
    if ( other.getField() == this->getField())
    {

        return (this->_n <= other._n);
    }
    else
    { /*TODO: handle error*/ }
}

bool GFNumber::operator>(GFNumber other) const
{
    if ( other.getField() == this->getField())
    {

        return (this->_n > other._n);
    }
    else
    { /*TODO: handle error*/ }

}

bool GFNumber::operator>=(GFNumber other) const
{
    if ( other.getField() == this->getField())
    {

        return (this->_n >= other._n);
    }
    else
    { /*TODO: handle error*/ }

}

GFNumber& GFNumber::operator+(long other) const
{
    const GField& ref = this->getField();
    GFNumber& numRef = *new GFNumber(other, ref);
    return (numRef + *this);
}

GFNumber& GFNumber::operator+=(long other)
{
    const GField& ref = this->getField();
    GFNumber& numRef = *new GFNumber(other, ref);
    return (numRef += *this);
}

GFNumber& GFNumber::operator-(long other) const
{
    const GField& ref = this->getField();
    GFNumber& numRef = *new GFNumber(other, ref);
    return (numRef - *this);
}

GFNumber& GFNumber::operator-=(long other)
{
    const GField& ref = this->getField();
    GFNumber& numRef = *new GFNumber(other, ref);
    return (numRef -= *this);
}

GFNumber& GFNumber::operator*(long other) const
{
    const GField& ref = this->getField();
    GFNumber& numRef = *new GFNumber(other, ref);
    return (numRef * *this);
}

GFNumber& GFNumber::operator*=(long other)
{
    const GField& ref = this->getField();
    GFNumber& numRef = *new GFNumber(other, ref);
    return (numRef *= *this);
}

GFNumber& GFNumber::operator%(long other) const
{
    const GField& ref = this->getField();
    GFNumber& numRef = *new GFNumber(other, ref);
    return (numRef % *this);
}

GFNumber& GFNumber::operator%=(long other)
{
    const GField& ref = this->getField();
    GFNumber& numRef = *new GFNumber(other, ref);
    return (numRef %= *this);
}

ostream& operator<<(ostream& out, const GFNumber& GFN)
{
    cout << GFN.getNumber() << GFN.getField();
    return out;
}

istream& operator>>(istream& in, GFNumber& GFN)
{
    long num, GFChar, GFDegree;
    cin >> num >> GFChar >> GFDegree;
    GField field(GFChar, GFDegree);
    GFN = *new GFNumber(num, field);
    return in;

}