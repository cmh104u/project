#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include "Rational.h"
#include "BigInt.h"

using namespace std;
using namespace BI;
using namespace RT;


namespace CO{
	class Complex{
		public:
			Complex();
			Complex(Rational r, Rational i);
			friend const Complex operator /(const Complex& a, const Complex& b);
			friend ostream& operator <<(ostream& outputStream, Complex& a);
		private:
			Rational re;	//Real Quantity
			Rational im;	//Imaginary Quantity

	};


}

#endif
