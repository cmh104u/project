#include <iostream>
#include <queue>
#define MAX_N 50000
#define MAX_M 1000000
using namespace std;

struct link{
    int node;
    struct link *nextPtr;
};

typedef struct link Link;
typedef Link *LinkPtr;

void myInsert(LinkPtr *sPtr,int n);
void myDelete(LinkPtr *sPtr);
void printLink(LinkPtr sPtr);
long long maxInArray(long long a[], int n);

int main()
{

    bool visit[MAX_N];
    long long componentWeight[MAX_N];
    int nodeWeight[MAX_N];
    int c, n, m, n1, n2;
    LinkPtr adjPtr[MAX_N];
    queue<int> myQueue;
    int queueOut;
    int componentCnt;

    for(int i = 0; i < MAX_N; i++)adjPtr[i] = NULL;

    cin >> c;
    while(c-- > 0)
    {
        //initialize
        for(int i = 0; i < MAX_N; i++)visit[i] = false;
        for(int i = 0; i < MAX_N; i++)componentWeight[i] = 0;

        cin >> n >> m;
        for(int i = 0; i < n; i++)cin >> nodeWeight[i];
        for(int i = 0; i < m; i++)
        {
            cin >> n1 >> n2;
            if(n1 == n2)continue;
                myInsert(&adjPtr[n1], n2);
                myInsert(&adjPtr[n2], n1);
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
                    for(LinkPtr currentPtr = adjPtr[queueOut]; currentPtr != NULL; currentPtr = currentPtr->nextPtr)
                    {
                        if(!visit[currentPtr->node]){
                            myQueue.push(currentPtr->node);
                            visit[currentPtr->node] = true;
                        }
                    }
                }
                componentCnt++;
            }
        }

        cout << maxInArray(componentWeight, componentCnt) << endl;

        for(int i = 0; i < n; i++)myDelete(&adjPtr[i]);
    }


    return 0;
}

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

void printLink(LinkPtr sPtr)
{
    while(sPtr)
    {
        cout << sPtr->node << " ";
        sPtr = sPtr->nextPtr;
    }
    cout << endl;
}

long long maxInArray(long long a[], int n)
{
    long long m = -1;
    for(int i = 0; i < n; i++)
    {
        if(a[i] > m)m = a[i];
    }
    return m;
}
