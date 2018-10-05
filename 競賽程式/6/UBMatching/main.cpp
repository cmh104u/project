#include <iostream>
#define MAX_V 600

using namespace std;

bool adj[MAX_V][MAX_V], visit_y[MAX_V];
int match_x[MAX_V], match_y[MAX_V];
int TC, A, B, M;

int DFS(int x)
{
    for(int i = 0; i < B; i++)
    {
        if(adj[x][i] && visit_y[i] == false){
            visit_y[i] = true;
            if(match_y[i] == -1 || DFS(match_y[i])){
                match_x[x] = i;
                match_y[i] = x;
                return true;
            }
        }
    }
    return false;
}

int bipartite_matching()
{
    for(int i = 0; i < A; i++)
        match_x[i] = -1;
    for(int i = 0; i < B; i++)
        match_y[i] = -1;

    int c = 0;
    for(int x = 0; x < B; ++x)
    {
        for(int i = 0; i < B; i++)
            visit_y[i] = false;
        if(DFS(x))c++;
    }
    return c;
}

int main()
{
    cin >> TC;
    while(TC--)
    {
        cin >> A >> B >> M;

        for(int i = 0; i < A; i++)
            for(int j = 0; j < B; j++)
                adj[i][j] = false;

        for(int i = 0, a, b; i < M; i++)
        {
            cin >> a >> b;
            adj[a][b] = true;
        }

        cout << bipartite_matching() << endl;
    }
    return 0;
}
