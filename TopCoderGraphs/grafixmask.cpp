//
//  grafixmask.cpp - TopCoder Problem
//  reads strings in the format:
//  Created by kirangoud on 15/03/14.
//  Copyright (c) 2014 ___KIRANGOUD___. All rights reserved.
//
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

#define H 400
#define W 600

#define VK_DFS 0
#define VK_BFS 0
#define TC_SOL 1 // Solution provided by the top coder contestant

int pic[H][W];

#if TC_SOL
int que[W*H];
int head;
int tail;
#endif

void readRectangleStrings(vector<string>& rects);


class node {
    
public:
    int x;
    int y;
    node (int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

#if TC_SOL
void add(int x, int y)
{
    if (x < 0 || y < 0 || x>= 600 || y >= 400) return;
    
    if (pic[y][x] == 1) return;
    
    que[tail++] = y * 600 + x;
    
    pic[y][x] = 1;
    
}// end of function
#endif

#if VK_BFS
//BFS based connected components area
int doFillBFS (int x, int y)
{
    int area = 0;
    
    // Declare our queue of nodes, and enqueue our starting node.
    queue<node> q;
    q.push(node(x,y));
    
    while (q.empty() == false)
    {
        node top = q.front();
        q.pop();
        // Check to ensure that we are within the bounds of the grid, if not continue
        if(top.x < 0 || top.x >= W || top.y < 0 || top.y >= H) continue;
        
        //Check that we haven't already visited this position, as we don't want to count it twice
        if (pic[top.y][top.x] == true) continue;
        
        // Since visited this node, mark as visited
        pic[top.y][top.x] = 1;
        
        /// We have found this node to be empty, and part
        // of this connected area, so add 1 to the result
        area++;
        // Now we will visit the adjacent node to this node
        q.push(node(top.x+1, top.y));
        q.push(node(top.x, top.y+1));
        q.push(node(top.x-1,top.y));
        q.push(node(top.x, top.y-1));
    }
    
    return area;
}// End of function

#elif VK_DFS
// DFS based connected components area
int doFillDFS (int x, int y)
{
    int result = 0; // Keeps track of area (number of pixels in connected component)
    
    // Declare our stack of nodes, and push our starting node onto the stack
    stack<node> s;
    s.push(node(x,y));
    
    while (s.empty() == false)
    {
        node top = s.top();
        s.pop();
        
        // Check to ensure that we are within the bounds of the grid, if not, continue
        if (top.x < 0 || top.x >=W || top.y < 0 || top.y >= H) continue;
        
        // Check that we haven't already visited this position, as we don't want to count it twice
        if (pic[top.y][top.x] == true) continue;
        
        // Since visited this node, mark as visited
        pic[top.y][top.x] = 1;
        
        /// We have found this node to be empty, and part
        // of this connected area, so add 1 to the result
        result++;
        
        // Now we will visit every node adjacent to this node
        s.push(node(top.x+1, top.y));
        s.push(node(top.x, top.y+1));
        s.push(node(top.x-1, top.y));
        s.push(node(top.x, top.y-1));
    }
    
    return result;
}// End of function

#else

#endif

class grafixMask {
public:
    vector<int> sortedAreas(vector<string> rectangles) {
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                pic[y][x] = 0;
        
        for (int i = 0; i < rectangles.size(); i++)
        {
            istringstream ss(rectangles[i]);
            int x1, y1, x2, y2;
            ss >> y1 >> x1 >> y2 >> x2;
            
            for (int y = y1; y <=y2; y++)
                for(int x = x1; x <=x2; x++)
                    pic[y][x] = 1;
        }
        vector<int> holes;
        for (int y = 0; y < H; y++)
        {
            for (int x = 0; x < W; x++)
            {
                if(pic[y][x] == 0)
                {
#if VK_BFS
                    holes.push_back(doFillBFS(x,y));
#elif VK_DFS
                    holes.push_back(doFillDFS(x,y));
                    
#else
                    // TC solution
                    // new connected component will start
                    head = 0;
                    tail = 0;
                    add(x, y);
                    while(head < tail)
                    {
                        int cx = que[head] % 600;
                        int cy = que[head] / 600;
                        head++;
                        
                        add(cx+1, cy);
                        add(cx, cy+1);
                        add(cx-1, cy);
                        add(cx, cy-1);
                    }
                    holes.push_back(tail);
#endif
                }
            }
        }
        
        sort(holes.begin(), holes.end());
        
        return holes;
    }// end of function
};


void readRectangleStrings(vector<string>& rectangles)
{
    // input : {"12 34 35 45", "12 23 45 32"}
    // output: 12 34 35 45
    //         12 23 45 32
    
    string inpStrs;
    
    getline(cin, inpStrs);
    
    cout << "String read = " << inpStrs << endl;
    
    unsigned long int stIdx  = inpStrs.find('\"');
    unsigned long int endIdx = inpStrs.find('\"', stIdx+1);
    unsigned long int len = endIdx - stIdx - 1;
    string a = inpStrs.substr(stIdx+1, len);
    cout << " String read = " << a << endl;
    
    
    rectangles.emplace_back(a);
    
    
    while (true)
    {
        stIdx = inpStrs.find('\"',  endIdx+1);
        if (stIdx == string::npos) break;
        endIdx = inpStrs.find('\"', stIdx+1);
        
        
        len = endIdx - stIdx - 1;
        a = inpStrs.substr(stIdx+1, len);
        cout << " String read = " << a << endl;
        rectangles.emplace_back(a);
    }
    
}// end of function

int main(int argc, const char * argv[])
{
    vector<string> rectangles;
    readRectangleStrings(rectangles);
    
    cout << "Number of rectangles = " << rectangles.size() << endl;
    grafixMask frame;
    
    vector<int> holes = frame.sortedAreas(rectangles);
    
    cout << "Number of holes = " << holes.size() << endl;
    
    for (vector<int>:: iterator i = holes.begin(); i != holes.end(); i++)
    {
        cout << *i << endl;
    }
    
    return 0;
}



