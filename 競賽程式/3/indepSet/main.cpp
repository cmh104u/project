#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Node{
    int key;
    int w;
    vector<Node *> child;
};

Node node[2000];
int M[2000], MP[2000];
int TC, N;

pair<int, int> answer(int r);

int main()
{
    int p;
    pair<int, int> ans;

    cin >> TC;
    for(int i = 1; i < 2000; i++)node[i].key = i;
    while(TC--)
    {
        //insert the tree
        cin >> N;
        cin >> node[1].w;
        for(int i = 2; i <= N; i++)
        {
            cin >> p;
            node[p].child.push_back(&node[i]);
            cin >> node[i].w;
        }
        for(int i = 1; i <= N; i++){
            if(node[i].child.empty())node[i].child.push_back(NULL);
        }

        //initial array M, MP
        for(int i = 1; i <= N; i++)
        {
            MP[i] = 0;
            M[i] = node[i].w;
        }

        //solve
        ans = answer(1);
        cout << max(ans.first, ans.second) << endl;

        //clear node
        for(int i = 1; i <= N; i++){
            node[i].child.clear();
        }
    }


    return 0;
}

pair<int, int> answer(int r)
{
    pair<int, int> result, tmp;

    if(node[r].child[0] != NULL){
        int childNum = node[r].child.size();
        for(int i = 0; i < childNum; i++)
        {
            tmp = answer(node[r].child[i]->key);
            M[r] += tmp.second;
            MP[r] += max(tmp.first, tmp.second);
        }
    }
    result.first = M[r];
    result.second = MP[r];
    return result;
}
