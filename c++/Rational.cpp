//林義翔 404410013 CSIE 2017
#include<iostream>
using namespace std;
#include"BigInt.h"
#include"Rational.h"
using namespace BI;
namespace RT{
Rational::Rational():numerator(0),denominator(1)
{/*empty*/}
Rational::Rational(BigInt nu_value,BigInt de_value):numerator(nu_value),denominator(de_value)
{/*empty*/}
Rational::Rational(BigInt wholeNumber):numerator(wholeNumber),denominator(1)
{/*empty*/}
void Rational::normalize()
{
    BigInt i,j,t,zero("0");
    i=numerator;
    j=denominator;
    t=i%j;
    while(t!=zero){
        i=j; j=t; t=i%j;
    }
    numerator=numerator/j;
    denominator=denominator/j;
    if(numerator.getOflag()==1&&denominator.getOflag()==1){
        numerator=zero-numerator;
        denominator=zero-denominator;
    }
    else if(numerator.getOflag()==1||denominator.getOflag()==1){
        if(denominator.getOflag()==1){
            denominator=zero-denominator;
            numerator=zero-numerator;
        }
    }
}
const BigInt Rational::getNumerator() const
{
    return numerator;
}
const BigInt Rational::getDenominator() const
{
    return denominator;
}
//////////////////////////
istream& operator >>(istream& inputStream,Rational& n)
{
    string s;
    int flag,i;
    BigInt nValue,dValue,zero("0");
    getline(inputStream,s);
    if(s=="\0"){
        n=Rational();
        return inputStream;
    }
    //default
    else{
        nValue=dValue=0;
        flag=0;
        for(i=0;s[i]!='/'&&s[i]!='\0';i++){
            if(s[i]=='-'){
                flag=1;
                continue;
            }
            nValue=nValue*10+(s[i]-'0');
        }
        if(flag==1)
            nValue=zero-nValue;
        if(s[i]=='\0'){
            n=Rational(nValue);
            return inputStream;
        }
        //wholeNumber
        else if(s[i]=='/'){
            flag=0;
            for(i=i+1;s[i]!='\0';i++){
                if(s[i]=='-'){
                    flag=1;
                    continue;
                }
                dValue=dValue*10+(s[i]-'0');
            }
            if(flag==1)
                dValue=zero-dValue;
            n=Rational(nValue,dValue);
            return inputStream;
        }
        //two number
    }
    return inputStream;
}
ostream& operator <<(ostream& outputStream, Rational& n)
{
    BigInt nu,de;
    nu=BigInt(n.getNumerator());
    de=BigInt(n.getDenominator());
    outputStream<<nu<<'/'
                <<de;
    return outputStream;
}
//////////////////////////////
const Rational operator +(const Rational& a,const Rational& b)
{
    BigInt i,j,t,zero("0");
    Rational ans;
    i=BigInt(a.getDenominator());
    j=BigInt(b.getDenominator());
    t=i%j;
    while(t!=zero){
        i=j; j=t; t=i%j;
    }
    ans=Rational((a.getNumerator()*b.getDenominator()/j)+(b.getNumerator()*a.getDenominator()/j),a.getDenominator()*b.getDenominator()/j);
    ans.normalize();
    return ans;
}
const Rational operator -(const Rational& a,const Rational& b)
{
    BigInt i,j,t,zero("0");
    Rational ans;
    i=BigInt(a.getDenominator());
    j=BigInt(b.getDenominator());
    t=i%j;
    while(i%j!=zero){
        i=j; j=t; t=i%j;
    }
    ans=Rational((a.getNumerator()*b.getDenominator()/j)-(b.getNumerator()*a.getDenominator()/j),a.getDenominator()*b.getDenominator()/j);
    ans.normalize();
    return ans;
}
const Rational operator -(const Rational& n)
{
    BigInt zero("0");
    return Rational(zero-n.numerator,n.denominator);
}
const Rational operator *(const Rational& a,const Rational& b)
{
    Rational ans;
    ans=Rational(a.numerator*b.numerator,a.denominator*b.denominator);
    ans.normalize();
    return ans;
}
const Rational operator /(const Rational& a,const Rational& b)
{
    Rational ans;
    ans=Rational(a.numerator*b.denominator,a.denominator*b.numerator);
    ans.normalize();
    return ans;
}
//friend+member functions
}
