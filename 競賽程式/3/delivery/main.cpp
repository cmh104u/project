#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int N;
int time[2000];

int main()
{
    int TC;
    ll result;

    cin >> TC;
    while(TC--)
    {
        result = 0;
        cin >> N;
        for(int i = 0; i < N; i++)
        {
            cin >> time[i];
        }
        sort(time, time+N);

        for(int i = 0; i < N; i++)result += (2*N - 1 - 2*i)*time[i];

        cout << result << endl;
    }

    return 0;
}
