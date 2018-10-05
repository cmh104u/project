#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node{
    vector<Node *> child;
};

int TC, N;
Node node[100001];

int depthOfTree(Node *cPtr);
int diameterOfTree(Node *cPtr);

int main()
{
    long long root;
    int c, p;
    cin >> TC;
    while(TC--)
    {
        root = 0;
        cin >> N;

        for(int i = 0; i < N; i++)root += i;
        for(int i = 1; i <= N-1; i++)
        {
            cin >> p >> c;
            root -= c;
            node[p].child.push_back(&node[c]);
        }
        for(int i = 0; i < N; i++){
            if(node[i].child.empty())node[i].child.push_back(NULL);
        }

        cout << diameterOfTree(&node[root])-1 << endl;

        for(int i = 0; i < N; i++)node[i].child.clear();
    }

    return 0;
}

int depthOfTree(Node *cPtr)
{
    int max_d = 0;

    if(cPtr == NULL)return 0;
    for(vector<Node *>::iterator it = cPtr->child.begin(); it != cPtr->child.end(); it++)
    {
        max_d = max(max_d, depthOfTree(*it));
    }
    return max_d + 1;
}

int diameterOfTree(Node *cPtr)
{
    int max1 = 0, max2 = 0, h, maxChild = 0;

    if(cPtr == NULL)return 0;
    for(vector<Node *>::iterator it = cPtr->child.begin(); it != cPtr->child.end(); it++)
    {
        h = depthOfTree(*it);
        if(h > max1){
            max2 = max1;
            max1 = h;
        }else if(h > max2){
            max2 = h;
        }
    }

    for(vector<Node *>::iterator it = cPtr->child.begin(); it != cPtr->child.end(); it++)
    {
        maxChild = max(maxChild, diameterOfTree(*it));
    }

    return max(maxChild, max1+max2+1);
}


