//
//  adjlist.cpp
//  BasicGraphs
//
//  Created by kirangoud on 27/04/14.
//  Copyright (c) 2014 ___KIRANGOUD___. All rights reserved.
//

#include <iostream>
using namespace std;

const int N = 10;

typedef struct _NODE_ {
    int v;
    _NODE_ *next;
    _NODE_ (int x, _NODE_* t)
    {
        v = x;
        next = t;
    }
}Node;

int main(int argc, const char * argv[])
{
    Node* adjList[N];
    for (int i = 0; i < N; i++) adjList[i] = 0;
    
    int i;
    int j;
    int nodes = 0;
    
    while(cin >> i >> j)
    {
        adjList[i] = new Node(j, adjList[i]);
        adjList[j] = new Node(i, adjList[j]);
        nodes++;
    }
    
    // Print the Graph
    for (i = 0; i < nodes; i++)
    {
        Node* headRef = adjList[i];
        cout << i <<" ->->";
        while(headRef)
        {
            cout << headRef->v << " -> ";
            headRef = headRef->next;
            
        }
        cout << endl;
    }
    

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

