#include <iostream>

using namespace std;

struct matrix{
    long long m[3][3];
};

typedef struct matrix Matrix;

Matrix mul(Matrix a, Matrix b);
int fastMod(int n, int a, int b, int c);
long long p;

int main()
{
    long long n;
    int a, b, c;
    while(cin >> n >> p >> a >> b >> c){
        cout << fastMod(n,a,b,c)%p << endl;
    }

    return 0;
}

Matrix mul(Matrix a, Matrix b)
{
    Matrix tmp;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tmp.m[i][j] = 0;
            for(int k = 0; k < 3; k++){
                tmp.m[i][j] += a.m[i][k] * b.m[k][j];
            }
            tmp.m[i][j] %= p;
        }
    }
    return tmp;
}

/*
    [An+3]  [a b c] [An+2]
    [An+2]= [1 0 0]*[An+1]
    [An+1]  [0 1 0] [An  ]
*/
int fastMod(int n, int a, int b, int c)
{
    Matrix ans ,base;
    int k;

    base.m[0][0] = a;
    base.m[0][1] = b;
    base.m[0][2] = c;
    base.m[1][1] = base.m[2][0] = base.m[2][2] = base.m[1][2] = 0;
    base.m[1][0] = base.m[2][1] = 1;

    ans.m[0][0] = 1;
    ans.m[1][0] = 1;
    ans.m[2][0] = 1;
    ans.m[0][1] = ans.m[1][1] = ans.m[1][2] = ans.m[0][2] = ans.m[2][1] = ans.m[2][2] = 0;

    k = n - 3;
    while(k > 0){
        if(k % 2 == 1){
            ans = mul(base, ans);
        }
        k >>= 1;
        base = mul(base, base);
    }
    return ans.m[0][0];
}
