#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>

using namespace std;

struct Node{
    int value;
    int lazy;
    Node():value(0), lazy(0){}
};

int N, a, b, arr_size;

vector<Node> tree;
void build(int root, int arr[], int s, int e);
void pushDown(int root);
int query(int root, int s, int e, int a, int b);
void update(int root, int s, int e, int a, int b, int val);
int findIndex(int root, int tar);
int getMax(int root);

int main()
{
    int r, l, arr[250000];
    while(1)
    {
        cin >> N;
        if(N == 0)break;
        if(N == 1){
            cin >> a >> b;
            cout << 1 << endl;
            continue;
        }

        for(arr_size = 1; arr_size < N; arr_size <<= 1);
        tree.resize(2*arr_size);
        for(int i = arr_size+N; i <= arr_size*2-1; i++)tree[i].value = INT_MAX;

        for(int i = 0; i < N; i++)
        {
            cin >> a >> b;
            update(1, 0, N-1, a, b, 1);
            if(b == N-1)continue;
            l = query(1, 0, N-1, b, b);
            r = query(1, 0, N-1, b+1, b+1);
            if(l == r)continue;
            r = findIndex(1, r);
            cout << "i: " << r << endl;
            update(1, 0, N-1, b+1, r-arr_size, 1);
        }

        cout << query(1, 0, N-1, N-1, N-1) << endl;
        tree.clear();
    }

    return 0;
}

void build(int root, int arr[], int s, int e)
{
    if(s == e){
        tree[root].value = arr[s];
    }else{
        int mid = (s + e)/2;
        build(root*2, arr, s, mid);
        build(root*2+1, arr, mid+1, e);
        tree[root].value = min(tree[root*2].value, tree[root*2+1].value);
    }
}

void pushDown(int root)
{
    if(tree[root].lazy != 0){
        tree[root*2].lazy += tree[root].lazy;
        tree[root*2+1].lazy += tree[root].lazy;
        tree[root*2].value += tree[root].lazy;
        tree[root*2+1].value += tree[root].lazy;
        tree[root].lazy = 0;
    }
}


int query(int root, int s, int e, int a, int b)
{
    if(b < s || a > e)return INT_MAX;
    if(a <= s && e <= b)return tree[root].value;
    pushDown(root);
    int mid = (s + e)/2;
    return min(query(root*2, s, mid, a, b), query(root*2+1, mid+1, e, a, b));
}

void update(int root, int s, int e, int a, int b, int val)
{
    if(b < s || a > e)return;
    if(a <= s && e <= b){
        tree[root].value += val;
        tree[root].lazy += val;
        return;
    }
    pushDown(root);
    int mid = (s + e)/2;
    update(root*2, s, mid, a, b, val);
    update(root*2+1, mid+1, e, a, b, val);
    tree[root].value = min(tree[root*2].value, tree[root*2+1].value);
}

int findIndex(int root, int tar)
{
    while(1)
    {
        pushDown(root);
        if(tree[root*2+1].value == tar){
            if(root*2+1 <= arr_size*2-1 && root*2+1 >= arr_size)return root*2+1;
            root = root*2+1;
        }else if(tree[root*2+1].value < tar){
            if(root*2+1 <= arr_size*2-1 && root*2+1 >= arr_size)return -1;
            root = root*2+1;
        }else if(tree[root*2].value == tar){
            if(root*2 <= arr_size*2-1 && root*2 >= arr_size)return root*2;
            root = root*2;
        }else if(tree[root*2].value < tar){
            if(root*2 <= arr_size*2-1 && root*2 >= arr_size)return -1;
            root = root*2;
        }else return -1;
    }
}

int getMax(int root)
{
    while(1)
    {
        pushDown(root);
        if(root*2+1 <= arr_size*2-1 && root*2+1 >= arr_size)return tree[root*2+1].value;
        root = root*2+1;
    }
}
