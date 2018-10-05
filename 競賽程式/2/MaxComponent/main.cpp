#include <iostream>
#include <queue>
#include <forward_list>
#include <iterator>
#include <cstring>
#define MAX_N 50000
#define MAX_M 1000000

using namespace std;

long long maxInArray(long long a[], int n);

int main()
{

    bool visit[MAX_N];
    long long componentWeight[MAX_N];
    int nodeWeight[MAX_N];
    int c, n, m, n1, n2;
    forward_list<int> adj[MAX_N];
    queue<int> myQueue;
    int queueOut;
    int componentCnt;

    cin >> c;
    while(c-- > 0)
    {
        //initialize
        memset(visit, false, sizeof(visit));
        memset(componentWeight, 0, sizeof(componentWeight));

        cin >> n >> m;
        for(int i = 0; i < n; i++)cin >> nodeWeight[i];
        for(int i = 0; i < m; i++)
        {
            cin >> n1 >> n2;
            if(n1 == n2)continue;
                adj[n1].push_front(n2);
                adj[n2].push_front(n1);
        }

        componentCnt = 0;
        for(int i = 0; i < n; i++)
        {
            if(!visit[i]){
                myQueue.push(i);
                visit[i] = true;
                while(!myQueue.empty())
                {
                    queueOut = myQueue.front();
                    myQueue.pop();
                    componentWeight[componentCnt] += nodeWeight[queueOut];
                    forward_list<int>::iterator p;
                    for(p = adj[queueOut].begin() ; p != adj[queueOut].end(); p++)
                    {
                        if(!visit[*p]){
                            myQueue.push(*p);
                            visit[*p] = true;
                        }
                    }
                }
                componentCnt++;
            }
        }


        cout << maxInArray(componentWeight, componentCnt) << endl;

        for(int i = 0; i < n; i++)adj[i].clear();
    }


    return 0;
}
/*
void myInsert(LinkPtr *sPtr,int n)
{
    LinkPtr tmpPtr = new Link;
    if(!tmpPtr){
        cout << "new fail!" << endl;
        return;
    }
    tmpPtr->node = n;
    tmpPtr->nextPtr = *sPtr;
    *sPtr = tmpPtr;
}

void myDelete(LinkPtr *sPtr)
{
    LinkPtr tmpPtr;
    while((*sPtr) != NULL)
    {
        tmpPtr = *sPtr;
        *sPtr = (*sPtr)->nextPtr;
        delete tmpPtr;
    }
}

bool isInLink(LinkPtr sPtr, int n)
{
    while(sPtr)
    {
        if(sPtr->node == n)return true;
        sPtr = sPtr->nextPtr;
    }
    return false;
}

void printLink(LinkPtr sPtr)
{
    while(sPtr)
    {
        cout << sPtr->node << " ";
        sPtr = sPtr->nextPtr;
    }
    cout << endl;
}
*/
long long maxInArray(long long a[], int n)
{
    long long m = -1;
    for(int i = 0; i < n; i++)
    {
        if(a[i] > m)m = a[i];
    }
    return m;
}
