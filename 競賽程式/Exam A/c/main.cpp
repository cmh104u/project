#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

deque<ll> MaxQ;
deque<ll> MinQ;
vector<ll> v;

int main()
{
    ll n, L, input, result;

    while(cin >> n >> L)
    {
        if(n == 0 && L == 0)break;

        cin >> input;
        MaxQ.push_back(input);
        MinQ.push_back(input);
        v.push_back(input);
        result = MaxQ.front() - MinQ.front();
        for(int i = 1; i < n; i++)
        {
            cin >> input;
            v.push_back(input);
            if(i > L){
                if(v[i-L-1] == MaxQ.front())MaxQ.pop_front();
                if(v[i-L-1] == MinQ.front())MinQ.pop_front();
            }
            while(!MaxQ.empty() && MaxQ.back() < input)MaxQ.pop_back();
            MaxQ.push_back(input);
            while(!MinQ.empty() && MinQ.back() > input)MinQ.pop_back();
            MinQ.push_back(input);

            if(result < MaxQ.front() - MinQ.front())result = MaxQ.front() - MinQ.front();
        }
        cout << result << endl;

        v.clear();
        MaxQ.clear();
        MinQ.clear();
    }

    return 0;
}

