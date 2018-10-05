#include <iostream>

using namespace std;

struct Node{
    int value;
    int weight;
    struct Node* nextPtr = NULL;

    Node(int v, int w){
        value = v;
        weight = w;
    }
};

typedef struct Node* NodePtr;


int main()
{
    NodePtr startPtr = NULL;

    return 0;
}

void addToLink(int v, int w, NodePtr *sPtr)
{
    NodePtr tmpPtr = new Node(v, w);
    if(*sPtr == NULL){
        *sPtr = tmpPtr;
    }else{

    }
}
