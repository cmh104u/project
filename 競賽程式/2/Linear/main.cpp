#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

struct lineSegment{
    double p;  //the start point in the line
    int a;  //f_i(x) = a[i]x+b[i]
    int b;
    int order;
};

struct line{
    int a;
    int b;
};

typedef struct lineSegment LineSegment;
typedef struct line Line;

int top = -1;
LineSegment myStack[45000];

bool isEmpty();
void push(double p, int a, int b, int o);
LineSegment pop();
int cmp(const void* a, const void* b);
double intersectionForX(Line L1, Line L2);
int findLine(int n);

int main()
{
    int i, n, m, newPtrCnt, c;
    Line *oldPtr, *newPtr;
    long long sum;
    while(1)
    {
        cin >> n >> m;
        if(n == 0)break;
        sum = 0;
        newPtrCnt = 0;
        oldPtr = new Line[n];
        newPtr = new Line[n];

        for(i = 0; i < n; i++)cin >> oldPtr[i].a >> oldPtr[i].b;
        qsort(oldPtr, n, sizeof(oldPtr[0]), cmp);
        //remove the repeated slope
        i = 0;
        for(int maxNum,same, j, tmp; i < n; )
        {
            if(i == n-1 || oldPtr[i].a != oldPtr[i+1].a){
                newPtr[newPtrCnt].a = oldPtr[i].a;
                newPtr[newPtrCnt].b = oldPtr[i].b;
                i++;
            }else{
                same = 1;
                j = i;
                maxNum = oldPtr[i].b;
                tmp = i;
                while(oldPtr[i].a==oldPtr[j+1].a)
                {
                    if(maxNum < oldPtr[j+1].b){
                        tmp = j+1;
                        maxNum = oldPtr[j+1].b;
                    }
                    same++;
                    j++;
                }
                newPtr[newPtrCnt].a = oldPtr[tmp].a;
                newPtr[newPtrCnt].b = oldPtr[tmp].b;
                i += same;
            }
            newPtrCnt++;
        }

        push(INT_MIN, newPtr[0].a, newPtr[0].b, 0);
        for(i = 1; i < newPtrCnt ; i++)
        {
            while(myStack[top].p >= intersectionForX(newPtr[myStack[top].order],newPtr[i]))
            {
                pop();
            }
            push(intersectionForX(newPtr[myStack[top].order],newPtr[i]), newPtr[i].a, newPtr[i].b, i);
        }


        for(i = 0; i < m; i++)
        {
            cin >> c;
            sum += (c*myStack[findLine(c)].a + myStack[findLine(c)].b);
        }

        cout << sum << endl;

        while(!isEmpty())pop();

        delete [] oldPtr;
        delete [] newPtr;
        oldPtr = NULL;
        newPtr = NULL;
    }

    return 0;
}

bool isEmpty()
{
    if(top == -1)return true;
    return false;
}

void push(double p, int a, int b, int o)
{
    myStack[++top].p = p;
    myStack[top].a = a;
    myStack[top].b = b;
    myStack[top].order = o;
}

LineSegment pop()
{
    LineSegment tmp;
    tmp.p = myStack[top].p;
    tmp.a = myStack[top].a;
    tmp.order = myStack[top].order;
    tmp.b = myStack[top--].b;
    return tmp;
}

int cmp(const void* a, const void* b)
{
    Line *x = (Line *)a;
    Line *y = (Line *)b;

    return x->a - y->a;
}

double intersectionForX(Line L1, Line L2)
{
    return (double)(L1.b - L2.b) / (L2.a - L1.a);
}

int findLine(int n)
{
    int CurrentPos = top / 2;
    int left = 0;
    int right = top;
    while(1)
    {
        if(myStack[CurrentPos].p <= n && (CurrentPos == top || myStack[CurrentPos+1].p > n))return CurrentPos;
        if(n < myStack[CurrentPos].p){
            right = CurrentPos;
            if(CurrentPos == (CurrentPos + left)/2){
                CurrentPos--;
            }else{
                CurrentPos = (CurrentPos + left)/2;
            }
        }
        if(n >= myStack[CurrentPos+1].p){
            left = CurrentPos;
            if(CurrentPos == (CurrentPos + right) / 2){
                CurrentPos++;
            }else{
                CurrentPos = (CurrentPos + right) / 2;
            }
        }
    }
}
