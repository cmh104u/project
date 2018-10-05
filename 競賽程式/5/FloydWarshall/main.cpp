#include <iostream>
#define MAX_N 2000
#define oo 60000000

using namespace std;

int graph[MAX_N][MAX_N];
int TC, N, M;
long long sum[MAX_N];

void Floyd_Warshall()
{
    for(int k = 0; k < N; k++)
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                if(graph[i][k] + graph[k][j] < graph[i][j]){
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

int findMedian()
{
    int mi = oo, index = -1;
    for(int i = 0; i < N; i++)
    {
        sum[i] = 0;
        for(int j = 0; j < N; j++)
        {
            sum[i] += graph[i][j];
        }
        if(sum[i] < mi){
            mi = sum[i];
            index = i;
        }
    }

    return index;
}

int main()
{
    cin >> TC;
    while(TC--)
    {
        cin >> N >> M;
        //initialize graph
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                graph[i][j] = oo;

        for(int i = 0, a, b, w; i < M; i++)
        {
            cin >> a >> b >> w;
            graph[a][b] = w;
        }

        for(int i = 0; i < N; i++)
            graph[i][i] = 0;

        //Floyd Warshall
        Floyd_Warshall();

        //output result
        cout << findMedian() << endl;
    }


    return 0;
}
