#include <iostream>
#include <set>

using namespace std;

multiset<int> mset;
multiset<int>::iterator mset_it;

int main()
{
    int N;
    while(1)
    {
        mset.clear();
        cin >> N;
        if(N == 0)break;
        for(int i = 0, a, b; i < N; i++)
        {
            cin >> a >> b;
            mset.insert(a);
            mset_it = mset.upper_bound(b);
            if(mset_it != mset.end())mset.erase(mset_it);
        }
        cout << mset.size() << endl;
    }

    return 0;
}
