#include <iostream>
#include <queue>
#include <forward_list>
#include <iterator>
#define MAX_N 5000
#define MAX_M 100000

using namespace std;

int maxInArray(int a[], int n);

int main()
{

    bool visit[MAX_N];
    int nodeWeight[MAX_N];
    int n, m, n1, n2, T;
    int t[100];
    forward_list<int> adj[MAX_N];
    queue<int> myQueue;
    int queueOut;
    int tMax[100];
    int start;

    while(1)
    {
        cin >> n >> m >> T;
        if(n == 0 && m == 0 && T == 0)break;

        //initialize
        for(int i = 0; i < T; i++)tMax[i] = -1;

        for(int i = 0; i < T; i++)cin >> t[i];
        for(int i = 0; i < n; i++)cin >> nodeWeight[i];
        for(int i = 0; i < m; i++)
        {
            cin >> n1 >> n2;
            if(n1 == n2)continue;
            adj[n1].push_front(n2);
        }

        for(int i = 0; i < T; i++)
        {
            for(int j = 0; j < n; j++)visit[j] = false;
            start = t[i];

            myQueue.push(start);
            visit[start] = true;
            while(!myQueue.empty())
            {
                queueOut = myQueue.front();
                myQueue.pop();
                if(tMax[i] < nodeWeight[queueOut])tMax[i] = nodeWeight[queueOut];
                forward_list<int>::iterator p;
                for(p = adj[queueOut].begin() ; p != adj[queueOut].end(); p++)
                {
                    if(!visit[*p]){
                        myQueue.push(*p);
                        visit[*p] = true;
                    }
                }
            }
        }

        cout << maxInArray(tMax, T) << endl;
        for(int i = 0; i < n; i++)adj[i].clear();
    }

    return 0;
}
int maxInArray(int a[], int n)
{
    int m = -1;
    for(int i = 0; i < n; i++)
    {
        if(a[i] > m)m = a[i];
    }
    return m;
}
