#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

struct Node{
    int key;
    int w;
    vector<Node *> child;
};

Node node[2000];
int M[2000], MP[2000], case1[1001];
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
        cout << ans.first << endl;

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
    int case2, case3 = 0, c2, childM[1001];
    if(node[r].child[0] != NULL){
        case1[r] = node[r].w;
        int childNum = node[r].child.size();
        for(int i = 0; i < childNum; i++)
        {
            childM[i] = node[r].child[i]->key;
            tmp = answer(node[r].child[i]->key);
            case1[r] += tmp.second;
            case3 += tmp.first;
        }
        case2 = INT_MAX;
        for(int i = 0; i < childNum; i++)
        {
//            cout << r  << ": " << M[childM[i]]  << " "  << childM[i] << endl;
            c2 = case3 - M[childM[i]] + case1[childM[i]];
            case2 = min(c2, case2);
        }
/*
        int childNum = node[r].child.size();
        for(int i = 0; i < childNum; i++)
        {
            tmp = answer(node[r].child[i]->key);
            M[r] += tmp.second;
            MP[r] += max(tmp.first, tmp.second);
        }*/
//        cout << r << ":" << case1[r] << " " << case2 << " " << case3 << endl;
        result.first = min(case1[r], case2);
        result.second = min(case1[r], case3);
        M[r] = result.first;
        MP[r] = result.second;
//        cout << r << ":" << result.first << " " << result.second << endl;
    }else{
        case1[r] = node[r].w;
        result.first = M[r];
        result.second = MP[r];
    }
    return result;
}
