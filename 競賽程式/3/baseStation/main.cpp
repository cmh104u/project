#include <iostream>
#include <algorithm>
using namespace std;

int service[50000];
int TC, N, K;

bool test(int D);
int tmp;
int main()
{
    int left, right, middle;
    cin >> TC;
    while(TC--)
    {
        cin >> N >> K;
        for(int i = 0; i < N; i++)cin >> service[i];
        sort(service, service+N);
        left = 1;
        right = ((service[N-1]-service[0])/K)+1;
        while(left < right)
        {
            middle = (left + right)/2;
            if(test(middle)){
                right = middle;
            }else{
                left = middle+1;
            }
        }
        cout << right << endl;
    }

    return 0;
}

bool test(int D)
{
    int currentPos;
    int stationCnt = 0;
    int i = 0;
    while(1)
    {
        stationCnt++;
        currentPos = service[i];
        currentPos += D;
        if(currentPos >= service[N-1])return true;
        for(;(i < N && service[i] <= currentPos); i++);
        if(stationCnt >= K)return false;
    }
}
