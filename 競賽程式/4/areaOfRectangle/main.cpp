#include <iostream>
#include <vector>
#define MAX_Coo 120001
using namespace std;

struct XSweep{
    int pos;
    int y1;
    int y2;
    bool start;
    XSweep(int a, int c, int d, bool e)
        :pos(a),y1(c),y2(d),start(e){}
    XSweep(){}
};


int tree[4*MAX_Coo];
vector<XSweep> XS;
int TC, N;

bool XSComp(XSweep a, XSweep b);

int main()
{

    cin >> TC;
    while(TC--)
    {
        cin >> N;
        XS.clear();
        for(int i = 0, x1, x2, y1, y2; i < N; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            XS.push_back(XSweep(x1, y1, y2, true));
            XS.push_back(XSweep(x2, y1, y2, false));
        }
        sort(XS.begin(), XS.end(), XSComp);

        for(int i = 0; i < 2*N; i++)
        {
            if(XS[i].start){


            }else{


            }
        }
    }

    return 0;
}

bool XSComp(XSweep a, XSweep b)
{
    return a.pos<b.pos;
}

