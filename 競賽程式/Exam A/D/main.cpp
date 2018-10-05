#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <algorithm>
#define MAX_N 35000
#define INF 1000000000

using namespace std;

typedef pair<int, int> pii;

struct Edge{
    int to;
    int w;
    int r;
    Edge(){};
    Edge(int a, int b, int c){
        to = a;
        r = b;
        w = c;
    };
};

bool visit[MAX_N];
vector<Edge> vertex[MAX_N];
int d[MAX_N];

bool havePath(int r);
int findMinRisk(int maxR);
int dijkstra(int r);

int n, m;

int main()
{
    int c, risk;
    int maxRisk;
    cin >> c;

    while(c--)
    {
        maxRisk = -1;
        cin >> n >> m;
        for(int i = 0; i < n; i++)vertex[i].clear();

        for(int i = 0; i < m; i++)
        {
            int u, v, r, w;
            cin >> u >> v >> r >> w;
            vertex[u].push_back(Edge(v, r, w));
            maxRisk = max(maxRisk, r);
        }

        risk = findMinRisk(maxRisk);

        if(risk == -1){
            cout << -1 << endl;
        }else{
            cout << risk << " " << dijkstra(risk) << endl;
        }
    }

    return 0;
}


//Precondition: determine if there is any paths consisting of edges whose risk is no bigger than r from 0 to n-1
bool havePath(int r)
{
    stack<int> s;
    int stackOut;
    Edge e;

    memset(visit, false, sizeof(visit));
    s.push(0);
    visit[0] = true;
    while(!s.empty())
    {
        stackOut = s.top();
        s.pop();
        if(stackOut == n-1)return true;
        for(int i = 0; i < vertex[stackOut].size(); i++)
        {
            e = vertex[stackOut][i];
            if(e.r <= r && !visit[e.to]){
                s.push(e.to);
                visit[e.to] = true;
            }
        }
    }
    return false;
}

//find miniRisk by binary search
int findMinRisk(int maxR)
{
    int left = 0;
    int right = maxR;
    int mid;

    if(havePath(left) == true)return 0;
    if(havePath(right) == false)return -1;

    while(right - left > 1)
    {
        mid = (right + left)/2;
        if(havePath(mid) == true){
            right = mid;
        }else{
            left = mid;
        }
    }

    return right;
}

int dijkstra(int r)
{
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pii top;
    int v;
    Edge e;

    fill(d, d+n, INF);

    d[0] = 0;
    pq.push(pii(0,0));

    while(!pq.empty())
    {
        top = pq.top();
        pq.pop();
        v = top.second;

        if(d[v] < top.first)continue;

        for(int i = 0; i < vertex[v].size(); i++)
        {
            e = vertex[v][i];
            if(e.r <= r && d[e.to] > d[v] + e.w){
                d[e.to] = d[v] + e.w;
                pq.push(pii(d[e.to], e.to));
            }
        }
    }

    return d[n - 1];
}

