#include <iostream>
#include "complex.h"
#include "Rational.h"
#include "BigInt.h"

using namespace std;
using namespace BI;
using namespace RT;
using namespace CO;

int main(){
	
	BigInt b1("1"), b3("3"), b_6("-6"), b17("17"), b81("81"), b320("320"), b128("128"), b520("520");
	BigInt f81, f320, f128, f520;
	Rational a_re, a_im, b_re, b_im;
	Complex a, b, answer;
	
	f81 = b81.factorial();	//81!
	f320 = b320.factorial();	//320!
	f128 = b128.factorial();	//128!
	f520 = b520.factorial();	//520!

	a_re = Rational(b1, b3);	// 1/3
	a_im = Rational(b_6, b17);	// -6/17
	b_re = Rational(f81, f320);	// 81!/320!
	b_im = Rational(f128, f520);// 128!/520!

	a = Complex(a_re, a_im);	// 1/3 - 6/17 i
	b = Complex(b_re, b_im);	// 81!/320! + 128!/520! i

	answer = a/b;

	cout << "Answer is " << "\n\n\n";
	cout <<  answer  << endl;


	return 0;
}
