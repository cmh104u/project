#include <iostream>

using namespace std;

int main()
{
    string n;
    long long p, y;
    long long mod;
    int n_length, k;

    while(cin >> n >> p){
        //Initialize variable
        y = 1;
        mod = 0;

        //Calculate n % p
        n_length = n.length();
        for(int i = 0; i < n_length; i++){
            mod = ((mod*10)%p + (n[i] - '0'))%p;
        }

        //Calculate (a%p) to the power of p-2 by fast exponentiation
        k = p-2;
        while(k > 0){
            if(k % 2 == 1){
                y = (y*mod)%p;
            }
            k >>= 1;
            mod = (mod*mod)%p;
        }

        //output the answer
        cout << y << endl;
    }

    return 0;
}
