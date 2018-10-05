#ifndef BIGINT_h
#define BIGINT_h
#include <iostream>
using namespace std;
namespace BI
{
class BigInt
{
public:
    BigInt();
    BigInt(long long int inint);
    BigInt(string s);
    BigInt(const BigInt& c);
    friend ostream& operator <<(ostream& outputStream,const BigInt& amount);
    friend BigInt operator +(BigInt amount1,BigInt amount2);
    friend BigInt operator -(BigInt amount1,BigInt amount2);
    friend BigInt operator *(BigInt amount1,BigInt amount2);
    friend BigInt operator /(BigInt amount1,BigInt amount2);
    friend BigInt operator %(BigInt amount1,BigInt amount2);
    friend bool operator !=(BigInt amount1,BigInt amount2);
    BigInt factorial();
    int getOflag();
    void changeOflag(int newOflag);
    int changeSize();
    BigInt& operator =(const BigInt& amount);
    ~BigInt();
private:
    int *in;
    int size;
    int oflag;
};
}
#endif // BIGINT_h
