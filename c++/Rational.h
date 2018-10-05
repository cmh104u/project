#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include "BigInt.h"
using namespace std;
using namespace BI;
namespace RT{
class Rational
{
    public:
        Rational();
        //initialize to 0/1
        Rational(BigInt nu_value,BigInt de_value);
        //precondition: legal numbers,aka denominator!=0
        Rational(BigInt wholeNumber);
        //initialize to wholeNumber/1
        void normalize();
        //postcondition:the number is normalized
        const BigInt getNumerator() const;
        const BigInt getDenominator() const;
        friend istream& operator >>(istream& inputStream,const Rational& n);
        friend ostream& operator <<(ostream& outputStream, Rational& n);
        friend const Rational operator +(const Rational& a,const Rational& b);
        friend const Rational operator -(const Rational& a,const Rational& b);
        friend const Rational operator -(const Rational& n);
        //negation
        friend const Rational operator *(const Rational& a,const Rational& b);
        friend const Rational operator /(const Rational& a,const Rational& b);
        //operations
    private:
        BigInt numerator;
        BigInt denominator;
};
}
#endif // RATIONAL_H
