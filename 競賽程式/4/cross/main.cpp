#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#define MAX_N 20020
using namespace std;

struct PointInX{
    int pos;
    int value;
    int y1;
    int y2;
    bool start;
    PointInX(int a, int b, int c, int d, bool e)
        :pos(a),value(b),y1(c),y2(d), start(e){}
    PointInX(){}
};

struct Node{
    int value;
    int lazy;
    Node():value(0), lazy(0){}
};

int TC, N;
vector<Node> tree;;

bool XvalueComp(PointInX a, PointInX b);
int deleteRepeat(vector<int>& a);
int findIndex(vector<int> a, int n, int v);
int construct(int n);
void build(int root, int arr[], int s, int e);
void pushDown(int root);
void update(int root, int s, int e, int a, int b, int v);

int main()
{
    int  x_sum, result, y_size, seg_size;
    vector<PointInX> Xvalue;
    vector<int> point_y;
    int arr[MAX_N*2];

    cin >> TC;
    while(TC--)
    {
        Xvalue.clear();
        point_y.clear();
        tree.clear();
        for(int i = 0; i < MAX_N*2; i++)arr[i] = 0;

        cin >> N;
        for(int i = 0, x1, x2, y1, y2, w; i < N; i++){
            cin >> x1 >> y1 >> x2 >> y2 >> w;
            Xvalue.push_back(PointInX(x1, w, y1, y2, true));
            Xvalue.push_back(PointInX(x2+1, w, y1, y2, false));
            point_y.push_back(y1);
            point_y.push_back(y2);
        }
        sort(Xvalue.begin(), Xvalue.end(), XvalueComp);
        sort(point_y.begin(), point_y.end());
        y_size = deleteRepeat(point_y);
        seg_size = construct(y_size);

        for(int i = 0, j = 0; i < Xvalue.size(); i++)
        {
            if(Xvalue[i].start){
                int a = findIndex(point_y, y_size, Xvalue[i].y1);
                int b = findIndex(point_y, y_size, Xvalue[i].y2);
//                cout << "a: " << a << ", b: " << b << ", x =" << Xvalue[i].value <<endl;
                for(int k = a; k <= b; k++)arr[k] += Xvalue[i].value;
            }
        }
//        for(int i = 0; i <= 4; i++)cout << i << ": " << arr[i] << endl;
        build(1, arr, 0, seg_size-1);

        x_sum = 0;
        result = INT_MIN;
        for(int i = 0, a, b; i < 2*N; i++)
        {
            a = findIndex(point_y, y_size, Xvalue[i].y1);
            b = findIndex(point_y, y_size, Xvalue[i].y2);
            if(Xvalue[i].start){
                x_sum += Xvalue[i].value;
                update(1, 0, seg_size-1, a, b, -Xvalue[i].value);
                if(i == 2*N || Xvalue[i].pos != Xvalue[i+1].pos){
 //                   cout << tree[1].value << " " << x_sum << endl;
                if(result < x_sum + tree[1].value)result = x_sum + tree[1].value;
                }
            }else{
                x_sum += -Xvalue[i].value;
                update(1, 0, seg_size-1, a, b, Xvalue[i].value);
            }
        }

        cout << result << endl;
    }
    return 0;
}

int construct(int n)
{
    int seg_size;
    for(seg_size = 1; seg_size < n; seg_size <<= 1);
    tree.resize(seg_size<<1);
    return seg_size;
}

void build(int root, int arr[], int s, int e)
{
    if(s == e){
        tree[root].value = arr[s];
    }else{
        build(2*root, arr, s, (s+e)/2);
        build(2*root+1, arr, (s+e)/2+1, e);
        tree[root].value = max(tree[2*root].value, tree[2*root+1].value);
    }
}

void pushDown(int root)
{
    if(tree[root].lazy != 0){
        tree[2*root].lazy += tree[root].lazy;
        tree[2*root+1].lazy += tree[root].lazy;
        tree[2*root].value += tree[root].lazy;
        tree[2*root+1].value += tree[root].lazy;
        tree[root].lazy = 0;
    }
}

void update(int root, int s, int e, int a, int b, int v)
{
    if(s > b || e < a)return;
    if(s >= a && e <= b){
        tree[root].value += v;
        tree[root].lazy += v;
        return;
    }
    pushDown(root);
    update(2*root, s, (s+e)/2, a, b, v);
    update(2*root+1, (s+e)/2+1, e, a, b, v);
    tree[root].value = max(tree[2*root].value, tree[2*root+1].value);
}

bool XvalueComp(PointInX a, PointInX b)
{
    return a.pos<b.pos;
}

int deleteRepeat(vector<int>& a)
{
    int cnt;
    int a_size = a.size();
    int j = 0;
    for(int i = 0; i < a_size;)
    {
        while(i < a_size-1 && a[i] == a[i+1])i++;
        a[j++] = a[i++];
    }
    return j;
}

int findIndex(vector<int> a, int n, int v)
{
    int l = 0, r = n-1, m;
    while(l <= r)
    {
        m = (l+r)/2;
        if(a[m] == v)return m;
        if(a[m] < v){
            l = m + 1;
        }else{
            r = m - 1;
        }
    }
    return -1;
}
