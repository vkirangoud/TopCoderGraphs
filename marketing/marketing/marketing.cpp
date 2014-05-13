//
//  marketing.cpp - TopCoder Problem
//  Marketing - DFS based problem
//
//  Created by kirangoud on 29/03/14.
//  Copyright (c) 2014 ___KIRANGOUD___. All rights reserved.
//



#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

#ifdef _WIN32
typedef __int64 int64;
#else
typedef long long int64;
#endif

void readInput(vector<string>& compete);

class Marketing {
public:
    bool adj[50][50];
    // 0 : no label
    // 1 : grp 1
    // 2 : grp 2
    int label[50];
    int n;
    bool error;
    
    void DFSbasedLabelling(int i, int color)
    {
        if (label[i] != 0) // if node i is labelled
        {
            if (label[i] != color)
            {
                error = true;
                return;
            }
        }
        else
        {
            label[i] = color;
            int other = 0;
            if (color == 1) other = 2;
            else other = 1;
            for (int j = 0; j < 50; j++)
            {
                if(adj[i][j]) DFSbasedLabelling(j, other);
            }
        }
    }
    
    int64 howMany(vector<string> compete)
    {
        error = false;
        for (int i = 0; i <50; i++)
            for(int j = 0; j<50;j++)
            {
                adj[i][j] = false;
            }
        // Initialize the graph
        for (int i = 0; i < compete.size(); i++)
        {
            // Competitors of product 'i' is given in "compete[i]
            istringstream in(compete[i]);
            int n;
            while (in >> n)
            {
                adj[i][n] = adj[n][i] = true;
            }
            label[i] = 0;
        }
        int64 ways = 1;
        
        for (int i = 0; i < compete.size(); i++)
        {
            if (label[i] == 0) // check if vertex is labelled
            {
                DFSbasedLabelling(i,1);
                if (error == true) return -1;
                ways *= 2; // each connected component 2 ways
                // one component x ways, another y ways, then total x*y ways
            }
        }
        return ways;
    }
};


//input format: {"1 4","2", "3",""}
void readInput(vector<string>& compete)
{
    string inputLine;
    getline(cin, inputLine);
    
    unsigned long int stIdx = inputLine.find('\"');
    unsigned long int endIdx = inputLine.find('\"', stIdx+1);
    unsigned long int len = endIdx - stIdx - 1;
    string a = inputLine.substr(stIdx+1, len);
    
    compete.emplace_back(a);
    
    while(true)
    {
        stIdx = inputLine.find('\"', endIdx + 1);
        if(stIdx == string::npos) break;
        endIdx = inputLine.find('\"', stIdx+1);
        len = endIdx - stIdx - 1;
        
        a = inputLine.substr(stIdx+1, len);
        
        compete.emplace_back(a);
    }
}

int main(int argc, const char* argv[])
{
    vector<string> compete;
    
    readInput(compete);
    
    for(vector<string>::iterator i = compete.begin(); i != compete.end(); i++)
    {
        cout << *i << endl;
    }
    
    Marketing obj;
    cout << " Number of ways = " << obj.howMany(compete) << endl;
    
    
    return 0;
}

