#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

priority_queue<int, vector<int>, less<int> > sm_pq;
priority_queue<int, vector<int>, greater<int> > la_pq;
int sm_cnt = 0;
int la_cnt = 0;

void balance();

int main()
{
    ll input, sum, mid;
    const int p = 1000000007;

    cin >> input;
    sm_pq.push(input);
    ++sm_cnt;
    sum = input;
    mid = input;
    while(cin >> input)
    {
        if(input >= mid){
            la_pq.push(input);
            ++la_cnt;
        }else{
            sm_pq.push(input);
            ++sm_cnt;
        }

        if(sm_cnt - la_cnt > 1 || la_cnt - sm_cnt > 1)balance();

        if(sm_cnt > la_cnt){
            mid = sm_pq.top();
        }else if(sm_cnt < la_cnt){
            mid = la_pq.top();
        }else{
            mid = (sm_pq.top() + la_pq.top())/2;
        }
        sum = (sum+mid)%p;
    }

    cout << sum << endl;

    return 0;
}

void balance(){
    ll tmp;
    if(sm_cnt - la_cnt > 1){
        tmp = sm_pq.top();
        sm_pq.pop();
        --sm_cnt;
        la_pq.push(tmp);
        ++la_cnt;
    }else if(la_cnt - sm_cnt > 1){
        tmp = la_pq.top();
        la_pq.pop();
        --la_cnt;
        sm_pq.push(tmp);
        ++sm_cnt;
    }
}
