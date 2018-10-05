#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
#define MAX_N 500

using namespace std;

struct Edge{
    int to;
    int w;
    int r;
    Edge();
    Edge(int a, int b);
};

bool visit[MAX_N];
vector<Edge> vertex[MAX_N];

bool havePath(int r, int v);

int main()
{
    int c, n, m, risk, answer;
    int maxRisk = -1;
    cin >> c;

    while(c--)
    {
        cin >> n >> m;
        for(int i = 0; i < n; i++)vertex[i].clear();

        for(int i = 0; i < m; i++)
        {
            int u, v, r;
            cin >> u >> v >> r;
            vertex[u].push_back(Edge(v, r));
            maxRisk = max(maxRisk, r);
        }

        risk = maxRisk;
        while(risk > 0)
        {
            if(!havePath(risk, n))break;
            --risk;
        }

        if(risk == maxRisk){
            answer = -1;
        }else{
            answer = risk + 1;
        }
        cout << answer << endl;
    }

    return 0;
}


//Precondition: determine if there is any paths consisting of edges whose risk is no bigger than r from 0 to n-1
bool havePath(int r, int v)
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
        if(stackOut == v-1)return true;
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

Edge::Edge(){
}

Edge::Edge(int a, int b){
    to = a;
    r = b;
}
