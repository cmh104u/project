#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#define MAX_N 10010
#define oo 100000000

using namespace std;

struct Edge{
    int to;
    int w;
    Edge(int a, int b):to(a), w(b){}
    Edge(){}
};

struct pq_item
{
    int a;
    int b;
    int w;
    pq_item(int x, int y, int z):a(x), b(y), w(z){}
    pq_item(){}
};

bool operator<(Edge a, Edge b)
{
    return a.w > b.w;
}

int TC, N, M, Q;
vector<Edge> point[MAX_N];

long long dijkstra(int src);

int main()
{
    cin >> TC;
    while(TC--)
    {
        cin >> N >> M >> Q;
        for(int i = 0, s, e, w; i < M; i++)
        {
            scanf("%d %d %d", &s, &e, &w);
            point[s].push_back(Edge(e, w));
        }

        for(int i = 0; i < Q; i++)
        {
            int q, ans;
            scanf("%d", &q);
            ans = dijkstra(q);
            if(ans == -1){
                cout << "No" << endl;
            }else{
                cout << ans << endl;
            }
        }

        for(int i = 0; i < N; i++)point[i].clear();
    }

    return 0;
}

long long dijkstra(int src)
{
    int dist[N];
    bool spt_set[N];
    long long ans = 0, a = src;
    priority_queue<Edge> pq;

    for(int i = 0; i < N; i++)
    {
        dist[i] = oo;
        spt_set[i] = false;
    }
    dist[src] = 0;
    spt_set[src] = true;

    for(int i = 0; i < N; i++)
    {
        ans += dist[a];
        if(i == N-1)break;
        for(int j = 0; j < point[a].size(); j++)
        {
            if(!spt_set[point[a][j].to] && point[a][j].w < dist[point[a][j].to]){
                dist[point[a][j].to] = point[a][j].w;
                pq.push(Edge(point[a][j].to, dist[point[a][j].to]));
            }
        }

        Edge e(-1, -1);
        while(!pq.empty())
        {
            e = pq.top();
            pq.pop();
            if(!spt_set[e.to])break;
        }
        if(e.to == -1)return -1;
        a = e.to;
        spt_set[e.to] = true;
    }
    return ans;
}
