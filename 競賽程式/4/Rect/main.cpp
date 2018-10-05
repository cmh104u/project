#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct event{
   int x, ya, yb, t;
   event(int a, int b, int c, int d){
      x = a; ya = b; yb = c; t = d;
   }
   friend bool operator<( const event &A, const event &B ) {
      return ( A.x == B.x ) ? ( A.t > B.t ) : ( A.x < B.x );
   }
};
struct node {
   int cnt, lzy;
   node():cnt(0), lzy(0){}
};

vector<event> E;
vector<node> Tree;
int s, f, seg_size;

void Construct(int n){
   for(seg_size = 1; seg_size < n; seg_size <<= 1);
   Tree.resize(seg_size << 1);
}
void update( int x, int y, int v, int n ){
   if(x >= f || y <= s)return;
   if(x >= s && y <= f){
      Tree[n].lzy += v;
      if(Tree[n].lzy)Tree[n].cnt = y - x;
      if(Tree[n].lzy < 1){
         if(n >= seg_size)Tree[n].cnt = 0;
         else Tree[n].cnt = Tree[2*n].cnt + Tree[2*n+1].cnt;
      }
      return;
   }

   update(x, ( x + y )/2, v, 2*n);
   update(( x + y )/2, y, v, 2*n+1);

   if(Tree[n].lzy < 1)
      Tree[n].cnt = Tree[2*n].cnt + Tree[2*n+1].cnt;
}

void Update( int x, int y, int v ) {
   s = x; f = y;
   update( 0, seg_size, v, 1 );
}
int query( int x, int y, int n ){
   if( x >= f || y <= s )return 0;
   if( x >= s && y <= f )return Tree[n].cnt;
   if( Tree[n].lzy )return min(y, f) - max(x, s);

   return query(x, ( x + y )/2, 2*n) +
          query(( x + y )/2, y, 2*n+1);
}
int Query() {
   s = 0; f = 130000;
   return query(0, seg_size, 1);
}

int main( void )
{
   int N, TC;
   cin >> TC;
   while(TC--)
   {
        cin >> N;
        for(int i = 0; i < N; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if(x2 < x1)swap(x1, x2);
            if(y2 < y1)swap(y1, y2);
            E.push_back( event( x1, y1, y2, +1 ) );
            E.push_back( event( x2, y1, y2, -1 ) );
        }

        Construct(130000);

        sort(E.begin(), E.end());
        long long last = 0, sol = 0;

        for( int i = 0; i < E.size(); ++i ) {
            sol += (long long)Query()*(E[i].x - last);
            Update(E[i].ya, E[i].yb, E[i].t);
            last = E[i].x;
        }

        cout << sol << endl;
        E.clear();
        Tree.clear();
   }
   return 0;
}
