#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Activity{
    int s;
    int f;
    int w;
    int q;
    Activity(){}
    Activity(int a, int b, int c){
        s = a;
        f = b;
        w = c;
    }
};

vector<Activity> act;
int OPT[100100];
int N;

bool cmp(Activity const &a, Activity const &b);
void findQ();
int getMaxWeight(int p);

int main()
{
    int TC, s, f, w;


    cin >> TC;
    while(TC--)
    {
        //insert
        act.push_back(Activity(-1, -1, -1));
        cin >> N;
        for(int i = 0; i < N; i++)
        {
            cin >> s;
            cin >> f;
            cin >> w;
            act.push_back(Activity(s,f,w));
        }

        //sort vector
        sort(act.begin(), act.end(), cmp);

        //find q
        findQ();

        //initialize
        for(int i = 0; i <= N; i++)OPT[i] = -1;

        //output
        cout << getMaxWeight(N) << endl;

        //clear
        act.clear();
    }

    return 0;
}

//used in sorting vector
bool cmp(Activity const &a, Activity const &b)
{
    return a.f < b.f;
}

void findQ()
{
    int l, r, m;
    for(int i = 1; i <= N; i++)
    {
        l = 1;
        r = N;
        while(l < r)
        {
            m = (l + r)/2;
            if(act[m].f > act[i].s){
                r = m;
            }else if(act[m].f <= act[i].s){
                l = m+1;
            }
        }
        act[i].q = r-1;
    }
}
/*
//recursive
int getMaxWeight(int p)
{
    if(p == 0){
        OPT[p] = 0;
    }else if(OPT[p]==-1){
        OPT[p] = max(act[p].w + getMaxWeight(act[p].q), getMaxWeight(p-1));
    }
    return OPT[p];
}
*/
int getMaxWeight(int p)
{
    OPT[0] = 0;
    for(int i = 1; i <= p; i++)
    {
        OPT[i] = max(act[i].w + OPT[act[i].q], OPT[i-1]);
    }
    return OPT[p];
}

