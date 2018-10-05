#include <iostream>
#include <cstdlib>
using namespace std;
#include "BigInt.h"
#include "Rational.h"
using namespace BI;
using namespace RT;

int main()
{
	BigInt an("57766478"),bn("543"),zero("0");
    BigInt ad("1564433446"),bd("10101010111");
    Rational a(an,ad),b(bn,bd);
    Rational c;

	cout<<"a = "<<a<<endl
        <<"b = "<<b<<endl;
    c=a+b;
    cout<<"a + b = "<<c<<endl;
    c=a-b;
    cout<<"a - b = "<<c<<endl;
    c=a*b;
    cout<<"a * b = "<<c<<endl;
    c=a/b;
    cout<<"a / b = "<<c<<endl;

    return 0;
}
