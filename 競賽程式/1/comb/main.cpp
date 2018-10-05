#include <iostream>

using namespace std;

long long degree(long long a, long long b, long long mod);

int main()
{
    long long n, k, p;
    long long ans;
    long long denNum; //The number of denominator
    while(cin >> n >> k >> p){
        ans = 1;
        if(n > 2*k){
            denNum = k;
        }else{
            denNum = n - k;
        }

    //Find the module of numerator
        for(int i = 0; i < denNum; i++){
            ans = (ans*(n-i)) % p;
        }

    //Find the module of denominator and answer
        for(int i = 1; i <= denNum; i++){
            ans = (ans*degree(i, p-2, p)) % p;
        }

        cout << ans << endl;
    }
    return 0;
}

//a to the power of b module by mod
long long degree(long long a, long long b, long long mod){
    long long result = 1;
    while(b > 0){
        if(b & 1){
            result = (a*result)%mod;
        }
        b >>= 1;
        a = (a*a)%mod;
    }
    return result;
}
