#include <iostream>
#define MAX_N 30100

using namespace std;

int N, M;
int group[MAX_N];

int findGroup(int x)
{
    return (x == group[x])? x : findGroup(group[x]);
}

void unionGroup(int x, int y)
{
    group[findGroup(x)] = findGroup(y);
}

int main()
{
    int line, last, ans;
    while(cin >> N >> M)
    {
        if(N == 0)break;
        ans = 1;
        for(int i = 0; i < N; i++)
            group[i] = i;

        for(int i = 0; i < M; i++)
        {
            cin >> line;
            cin >> last;
            for(int i = 0, in; i < line - 1; i++)
            {
                cin >> in;
                unionGroup(last, in);
                last = in;
            }
        }

        for(int i = 1; i < N; i++)
        {
            if(findGroup(0) == findGroup(i))ans++;
        }

        cout << ans << endl;
    }


    return 0;
}
