#include <iostream>
#include <math.h>

using namespace std;

void aToLong(string& s, long long& l);
int toDigit(char c);

class BigInt{
public:
    BigInt(const string inputNumber);
    void showValue();
private:
    int *numberPtr;
    int numberBit;
};

int main()
{
    string n_string, n1_string, n2_string, n_subString;
    long long p;
    long long y;
    long long n_long, n1_long, n2_long;
    long long tmp;
    long long tenOf18Power = 1000000000000000000;
    int level;
    long long bigIntModValue;
    long long tenOf18PowerModP;
    int n_length;

    n_length = n_string.length();


    while(cin >> n_string >> p){
        y = -1;
        bigIntModValue = 0;
        tenOf18PowerModP = tenOf18Power % p;

//calculate bigIntModValue
        level = n_length / 18;
        if(n_length % 18 != 0)++level;

        for(int i = 1; i <= level; i++){
            if(n_length >= i*18){
                n_subString = n_string.substr(n_length-i*18, 18);
            }else{
                n_subString = n_string.substr(0, n_length-(i-1)*18);
            }

            aToLong(n_subString, n_long);
            tmp = n_long % p;
            for(int j = level; j > 1; j--){
                tmp *= tenOf18PowerModP;
            }

            bigIntModValue += tmp;
        }
        bigIntModValue %= p;
//        cout << bigIntModValue << endl;
 /*
        if(n_string.length() <= 18){
            aToLong(n_string, n_long);
            tmp = n_long % p;
        }else{
            n1_string = n_string.substr(n_string.length()-18,18);
            n2_string = n_string.substr(0,n_string.length()-18);
            aToLong(n1_string, n1_long);
            aToLong(n2_string, n2_long);

            tmp = (((n2_long%p)*(tenOf18Power%p))%p + n1_long%p) % p;
        }*/

        for(long long i = 1; i < p; i++){
            if((bigIntModValue*i) % p == 1){
                y = i;
                break;
            }
        }
        if(y != -1)cout << y << endl;
    }

    return 0;
}

int toDigit(char c){
    switch(c){
    case '0':
        return 0;
        break;
    case '1':
        return 1;
        break;
    case '2':
        return 2;
        break;
    case '3':
        return 3;
        break;
    case '4':
        return 4;
        break;
    case '5':
        return 5;
        break;
    case '6':
        return 6;
        break;
    case '7':
        return 7;
        break;
    case '8':
        return 8;
        break;
    case '9':
        return 9;
        break;
    }
}

void aToLong(string& s, long long& l){
    l = 0;
    long long powerOfTen = 1;
    for(int i = 0; i < s.length(); i++ , powerOfTen *= 10){
        l += (long long)(toDigit(s[s.length()-1-i])*powerOfTen);
    }
}

BigInt::BigInt(const string inputNumber)
{
    numberBit = inputNumber.length();
    for(int i = 0; i < numberBit; i++){
        switch(inputNumber[i]){
            case'0':
                numberPtr[i] = 0;
                break;
            case'1':
                numberPtr[i] = 1;
                break;
            case'2':
                numberPtr[i] = 2;
                break;
            case'3':
                numberPtr[i] = 3;
                break;
            case'4':
                numberPtr[i] = 4;
                break;
            case'5':
                numberPtr[i] = 5;
                break;
            case'6':
                numberPtr[i] = 6;
                break;
            case'7':
                numberPtr[i] = 7;
                break;
            case'8':
                numberPtr[i] = 8;
                break;
            case'9':
                numberPtr[i] = 9;
                break;
        }
    }
}

void BigInt::showValue()
{
    for(int i = 0; i < numberBit; i++){
        cout << numberPtr[i];
    }
}
