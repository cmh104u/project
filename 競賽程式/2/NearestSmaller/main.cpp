#include <iostream>
#include <stack>
using namespace std;

int main()
{

    stack<int> s;
    int n, value;
    long long sum;

    while(1)
    {
        sum = 0;
        cin >> n;
        if(n == 0)break;

        for(int i = 0; i < n; i++)
        {
            cin >> value;

            if(s.empty())
            {
                s.push(value);
                continue;
            }

            while(!s.empty() && value <= s.top())s.pop();

            if(!s.empty())
            {
                sum += value - s.top();
            }
            s.push(value);
        }

        cout << sum << endl;

        while(!s.empty())s.pop();
    }

    return 0;
}
