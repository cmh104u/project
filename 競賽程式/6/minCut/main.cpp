#include <iostream>
#include<cstdio>
#include<cstring>
#define oo 100000000
const int maxn = 10100;

using namespace std;

int adj[maxn][maxn];
int TC, n, M;

void contract(int x,int y)
{
    int i,j;
    for (i=0; i<n; i++)
        if (i!=x)
        {
            adj[x][i]+=adj[y][i];
            adj[i][x]+=adj[i][y];
        }
    for (i=y+1; i<n; i++)
        for (j=0; j<n; j++)
        {
            adj[i-1][j]=adj[i][j];
            adj[j][i-1]=adj[j][i];
        }
    n--;
}

int w[maxn], visit[maxn];
int sx,tx;

int mincut()
{
    memset(visit, 0, sizeof(visit));
    visit[0] = 1;
    for(int i = 0; i < n; i++)
        w[i] = adj[0][i];
    for(int i = 1; i+1 < n; i++)
    {
        int ma = -1, x = -1;
        for(int j = 0; j < n; j++)
        {
            if(visit[j] == 0 && w[j] > ma){
                ma = w[j];
                x = j;
            }
        }
        sx = x;
        visit[x] = 1;
        for(int j=0; j < n; j++)
            w[j] += adj[x][j];
    }

    for(int i = 0; i < n; i++)
    {
        if(visit[i]==0){
            tx = i;
            return w[i];
        }
    }
}

int main()
{
    cin >> TC;
    while (TC--)
    {
        cin >> n >> M;
        memset(adj,0,sizeof(adj));
        for(int i = 0, a, b, w; i < M; i++)
        {
            scanf("%d %d %d", &a,&b,&w);
            adj[a][b]+=w;
            adj[b][a]+=w;
        }

        int mi = oo;
        while (n>1)
        {
            int tmp = mincut();
            if(tmp < mi)mi = tmp;
            contract(sx,tx);
        }
        cout << mi << endl;
    }
    return 0;
}
