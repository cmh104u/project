#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct Edge{
    int a;
    int b;
    int w;
    Edge(int x, int y, int z):a(x), b(y), w(z){};
};


int TC, N, M;
vector<Edge> graph;
vector<int> tree;
bool cmp(const Edge& a, const Edge& b)
{
    return (a.w < b.w);
}
int findTree(int a);
void unionTree(int a, int b);

int main()
{
    int sum;

    cin >> TC;
    while(TC--)
    {
        cin >> N >> M;
        for(int i = 0, a, b, w; i < M; i++)
        {
            scanf("%d %d %d", &a, &b, &w);
            graph.push_back(Edge(a, b, w));
            tree.push_back(i);
        }
        sort(graph.begin(), graph.end(), cmp);

        int cnt = 0;
        sum = 0;
        for(int i = 0; i < M && cnt < N-1; i++)
        {
            if(findTree(graph[i].a) != findTree(graph[i].b)){
                sum += graph[i].w;
                unionTree(graph[i].a, graph[i].b);
                cnt++;
            }
        }
        cout << sum << endl;

        tree.clear();
        graph.clear();
    }

    return 0;
}

int findTree(int a)
{
    return (a == tree[a])?a:(tree[a] = findTree(tree[a]));
}

void unionTree(int a, int b)
{
    tree[findTree(a)] = findTree(b);
}
