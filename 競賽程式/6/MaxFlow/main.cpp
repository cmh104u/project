#include <iostream>
#include <queue>
#include <algorithm>
#define MAX_N 600
#define oo 100000000
using namespace std;

int R[MAX_N][MAX_N], C[MAX_N][MAX_N], F[MAX_N][MAX_N];
bool visit[MAX_N];
int path[MAX_N], bottleneck[MAX_N];
int TC, N, M;

int BFS(int s, int t)
{
    for(int i = 0; i < N; i++)
        visit[i] = false;

    queue<int> qu;
    visit[s] = true;
    path[s] = s;
    bottleneck[s] = oo;
    qu.push(s);

    while(!qu.empty())
    {
        int d = qu.front();
        qu.pop();
        for(int i =0; i < N; i++)
        {
            if(!visit[i] && R[d][i] > 0)
            {
                visit[i] = true;
                path[i] = d;
                bottleneck[i] = min(R[d][i], bottleneck[d]);
                qu.push(i);
                if(i == t)return bottleneck[t];
            }
        }
    }
    return 0;
}

int Edmonds_Karp(int s, int t)
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            F[i][j] = 0;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            C[i][j] = R[i][j];

    int f, df;
    for(f = 0; df = BFS(s, t); f += df)
    {
        for(int i = path[t], j = t; i != j; i = path[j=i])
        {
            F[i][j] = F[i][j] + df;
            F[j][i] = -F[i][j];
            R[i][j] = C[i][j] - F[i][j];
            R[j][i] = C[j][i] - F[j][i];
        }
    }

    return f;
}

int main()
{
    cin >> TC;
    while(TC--)
    {
        cin >> N >> M;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                R[i][j] = 0;

        for(int i = 0, s, e, w; i < M; i++)
        {
            cin >> s >> e >> w;
            R[s][e] = w;
        }

        cout << Edmonds_Karp(0, N-1) << endl;
    }

    return 0;
}
