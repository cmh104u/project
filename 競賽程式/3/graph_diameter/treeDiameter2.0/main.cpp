#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> adj[100001];
int TC, N, diameter;

int DFS(int x);

int main()
{
    long long root;
    int p, c;

    cin >> TC;
    while(TC--)
    {
        diameter = 0;

        cin >> N;
        root = 0;
        for(int i = 0; i < N; i++)root += i;
        for(int i = 0; i < N-1; i++)
        {
            cin >> p >> c;
            adj[p].push_back(c);
            root -= c;
        }

        DFS(root);
        cout << diameter << endl;

        for(int i = 0; i < N; i++)adj[i].clear();
    }
    return 0;
}

int DFS(int x)
{
    int max1 = 0, max2 = 0, h;
    for(vector<int>::iterator it = adj[x].begin(); it != adj[x].end(); it++)
    {
        h = DFS(*it) + 1;
        if(h > max1){
            max2 = max1;
            max1 = h;
        }else if(h > max2){
            max2 = h;
        }
    }
    diameter = max(diameter, max1+max2);
    return max1;
}
