#include <vector>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;

vector<int> e[100001];
bool flag[100001];
int depth[100001], ans, N, TC;

int bfs(int start){
    memset(flag, false, sizeof(flag));
    memset(depth, 0, sizeof(depth));
    queue<int> Q;
    Q.push(start);
    flag[start] = true;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(int i = 0; i < e[u].size(); ++i) {
            if(!flag[e[u][i]]) {
                depth[e[u][i]] = depth[u]+1;
                flag[e[u][i]] = true;
                Q.push(e[u][i]);
            }
        }
    }
    int point = -1;
    ans = -1;
    for(int i = 0; i < N; ++i) {
        if(depth[i] > ans) {
            ans = depth[i];
            point = i;
        }
    }
    return point;
}

int main(int argc, char **argv) {
    int x, y;

    cin >> TC;
    while(TC--){
        cin >> N;
        for(int i = 1; i < N; ++i) {
            cin >> x >> y;
            e[x].push_back(y);
            e[y].push_back(x);
        }
        bfs(bfs(1));
        cout  << ans << endl;
        for(int i = 0; i < N; ++i)e[i].clear();
    }
    return 0;
}
