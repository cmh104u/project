#include <iostream>
#include <climits>
#define MAX 1000000000

int w[10000][10000];
int d[10000];
int parent[10000];
bool visit[10000];

using namespace std;

void dijkstra(int start, int vertexNum);
int findMaxInArray(int a[], int n);

int main()
{
    int n, m, col, row;

    cin >> n >> m;

    //initialize matrix w
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)w[i][j] = MAX;
    }

    //insert the weight into matrix
    for(int i = 0; i < m; i++)
    {
        cin >> row >> col;
        cin >> w[row][col];
        w[col][row] = w[row][col];
    }

    dijkstra(0, n);

    cout << findMaxInArray(d, n) << endl;

    return 0;
}

void dijkstra(int start, int vertexNum)
{
    int currentVertex, minValue;
    //initialize
    for(int i = 0; i < vertexNum; i++)
    {
        visit[i] = false;
        d[i] = MAX;
    }
    d[start] = 0;
    parent[start] = start;

    //find the minimum distance of start vertex to the others vertex
    for(int i = 0; i < vertexNum; i++)
    {
        currentVertex = -1;
        minValue = MAX;
        for(int j = 0; j < vertexNum; j++)
        {
            if(!visit[j] && d[j] < minValue)
            {
                currentVertex = j;
                minValue = d[j];
            }
        }

        if(currentVertex == -1)break;

        visit[currentVertex] = true;

        for(int k = 0; k < vertexNum; k++)
        {
            if(!visit[k] && d[currentVertex] + w[currentVertex][k] < d[k])
            {
                d[k] = d[currentVertex] + w[currentVertex][k];
                parent[k] = currentVertex;
            }
        }



    }
}

int findMaxInArray(int a[], int n)
{
    int maxValue = INT_MIN;

    for(int i = 0; i < n; i++)
    {
        if(maxValue < a[i])maxValue = a[i];
    }
    return maxValue;
}
