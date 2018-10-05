#include <iostream>

using namespace std;

typedef long long ll;

ll bigMod(string s, ll mod);
ll fastMod(ll x, ll n, ll mod);

int main()
{
    string x, n;
    ll p, xMod, nMod;
    while(cin >> x >> n >> p)
    {
        xMod = bigMod(x, p);
        nMod = bigMod(n, p-1);
        cout << fastMod(xMod, nMod, p) << endl;
    }

    return 0;
}

ll bigMod(string s, ll mod)
{
    ll result = 0;
    int s_size;

    s_size = s.size();
    for(int i = 0; i < s_size; i++)
    {
        result = ((result*10)%mod + (s[i]-'0')%mod)%mod;
    }
    return result;
}

ll fastMod(ll x, ll n, ll mod)
{
    ll result = 1;
    while(n > 0)
    {
        if(n % 2 == 1){
            result = (result*x)%mod;
        }
        n >>= 1;
        x = (x*x)%mod;
    }
    return result;
}
