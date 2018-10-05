#include <iostream>
#include "complex.h"
#include "Rational.h"
#include "BigInt.h"

using namespace std;
using namespace BI;
using namespace RT;

namespace CO{
		
		Complex::Complex():re(1), im(1){
		}

		Complex::Complex(Rational r, Rational i):re(r),im(i){
		}

		const Complex operator /(const Complex& a, const Complex& b){
			Complex result;
			
			result.re = (a.re*b.re + a.im*b.im)/(b.re*b.re + b.im*b.im);
			result.im = (a.im*b.re - a.re*b.im)/(b.re*b.re + b.im*b.im);

			return Complex(result.re ,result.im);
		}

		ostream& operator <<(ostream& outputStream, Complex& a){
			outputStream << a.re << " + " << a.im << " i";

			return outputStream;
		}

}
