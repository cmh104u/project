#include <iostream>
#include <vector>

using namespace std;

vector<int> last;
int N;

void addToLast(int a);

int main()
{
    int TC, element;

    cin >> TC;
    while(TC--)
    {
        cin >> N;
        last.push_back(-1);
        for(int i = 0; i < N; i++)
        {
            cin >> element;
            addToLast(element);
        }

        cout << last.size() - 1 << endl;

        last.clear();
    }
    return 0;
}

void addToLast(int a)
{
    int lastLen = last.size();
    int l = 0, r = lastLen-1;
    int m;

    if(a > last[lastLen-1])
    {
        last.push_back(a);
        return;
    }

    while(r-l >= 1)
    {
        m = (l + r)/2;
        if(last[m] > a){
            r = m;
        }
        if(last[m] < a){
            l = m+1;
        }
        if(last[m] == a)return;
    }
    last[l] = a;
}
