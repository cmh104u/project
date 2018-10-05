#include <iostream>
#include <cstdio>
#include <vector>
#define MAX_N 5100
#define oo 100000000

using namespace std;

int TC, N, M, Q;

struct Edge{
    int to;
    int w;
    Edge(){}
    Edge(int a, int b):to(a), w(b){}
};

vector<Edge> point[MAX_N];
int d[MAX_N];

int bellman_ford(int src, int tar)
{
    for(int i = 0; i < N; i++)
        d[i] = oo;

    d[src] = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(d[j] != oo){
                for(int k = 0; k < point[j].size(); k++)
                {
                    if(d[j] + point[j][k].w < d[point[j][k].to]){
                        d[point[j][k].to] = d[j] + point[j][k].w;
                    }
                }
            }
        }
    }

    return d[tar];
}

bool neg_circle(int tar)
{
    int preValue = d[tar];
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < N; j++)
        {
            if(d[j] != oo){
                for(int k = 0; k < point[j].size(); k++)
                {
                    if(d[j] + point[j][k].w < d[point[j][k].to]){
                        d[point[j][k].to] = d[j] + point[j][k].w;
                    }
                }
            }
        }
    }
    if(d[tar] != preValue)return true;
    return false;
}

int main()
{
    int ans;

    cin >> TC;
    while(TC--)
    {
        scanf("%d %d %d", &N, &M, &Q);
        for(int i = 0, a, b ,w; i < M; i++)
        {
            scanf("%d %d %d", &a, &b, &w);
            point[a].push_back(Edge(b, w));
        }

        for(int i = 0, s, e; i < Q; i++)
        {
            scanf("%d %d", &s, &e);
            ans = bellman_ford(s, e);
            if(neg_circle(e)){
                cout << "No" << endl;
            }else if(ans == oo){
                cout << "No" << endl;
            }else{
                cout << ans << endl;
            }
        }

        for(int i = 0; i < N; i++)point[i].clear();
    }

    return 0;
}
