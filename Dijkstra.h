//
//  Dijkstra.h
//  Algorithm_PA2
//
//  Created by 蕭弈均 on 2020/1/3.
//  Copyright © 2020 蕭弈均. All rights reserved.
//

#ifndef Dijkstra_h
#define Dijkstra_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

const int inf=2147483647;
struct point
{
    int d;
    int pi;
};

int pow(int a,int b)
{
    if(b==0)
        return 1;
    else
    {
        int j=a;
        for(int i=1; i<b;i++)
        {
            a=a*j;
        }
        return a;
    }
}


int Find_intex_of_min(vector<point> &vertex,set<int> Q)
{
    int key=inf;
    int index=0;
    set<int>::iterator it;
    for(it=Q.begin();it!=Q.end();it++)
    {
      if(vertex[*it].d<key)
      {
          key=vertex[*it].d;
          index=*it;
      }
    }
    return index;
}


pair<int,int> index2cordinate(int grid, int i)
{
    int x=i%grid;
    int y=i/grid;
    pair<int,int> p;
    p=make_pair(x, y);
    return p;
}


int FindVertex(int grid, int x, int y)
{
    return grid*y+x;
}



void addEdge(vector<vector<int> >& graph, int u, int v)
{
    graph[u][v] = 1;
    graph[v][u] = 1;
}



void Findadj(vector<vector<int> >& graph, int grid, vector<int> &adj, int u)
{
    adj.clear();
    for(int v=0;v<grid*grid;v++)
    {
        if(u!=v && graph[u][v]!=inf)
        {
            adj.push_back(v);
        }
    }
}

void FindadjV2(vector<vector<int> >& graph, int grid, vector<int> &adj, int u)
{
    adj.clear();
    pair<int,int> point;
    point=index2cordinate(grid, u);
    int x[4];
    int y[4];
    x[0]=point.first+1; y[0]=point.second;
    x[1]=point.first; y[1]=point.second+1;
    x[2]=point.first-1; y[2]=point.second;
    x[3]=point.first; y[3]=point.second-1;
    for(int i=0;i<4;i++)
    {
        if(x[i]>=0 && x[i]<grid && y[i]>=0 && y[i]<grid)
        {
            adj.push_back(FindVertex(grid, x[i], y[i]));
        }
    }
}



void Initialize_Single_Source( vector<point> &vertex,int s)
{
    for(int i=0;i<vertex.size();i++)
    {
       vertex[i].d=inf;
       vertex[i].pi=-1; //-1="NIL"
    }
    vertex[s].d=0;
    vertex[s].pi=s;
}

void Relax(vector<point> &vertex, int u, int v, vector<vector<int> >& W)
{
    if(vertex[v].d>vertex[u].d+W[u][v])
    {
        vertex[v].d=vertex[u].d+W[u][v];
        vertex[v].pi=u;
    }
}



void Dijkstra(int grid, vector<point> &vertex, vector<vector<int> >& graph, int s)
{
    Initialize_Single_Source(vertex, s);
    int u=0;
    vector<int> adj;
    adj.resize(0);
    set<int> Q;
    for(int i=0;i<vertex.size();i++)     //Q=G.V
    {
        Q.insert(i);
    }

    
    while(!Q.empty())
    {
        u=Find_intex_of_min(vertex,Q);   //Extract-Min(Q)
        Q.erase(u);
        FindadjV2(graph,grid,adj, u);
        for(int v=0;v<adj.size();v++)
        {
            Relax(vertex,u,adj[v],graph);
        }
    }
}






#endif /* Dijkstra_h */
