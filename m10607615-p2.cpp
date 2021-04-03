//
//  main.cpp
//  Algorithm_PA2
//
//  Created by 蕭弈均 on 2019/12/25.
//  Copyright © 2019 蕭弈均. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include "Dijkstra.h"
#include <set>
#include <time.h>
using namespace std;




int main(int argc, const char * argv[]) {
    double START,END;
    START = clock();
    if(argc != 3)
     {
         cout << "Usage: ./[exe] [input file] [output file]" << endl;
     //    system("pause");
         exit(1);
     }

     // open the input file
     fstream fin;
     fin.open(argv[1], fstream::in);
     if(!fin.is_open())
     {
         cout << "Error: the input file is not opened!!" << endl;
         exit(1);
     }

     // parse the input file
     cout << "======================" << endl;
     cout << "        Parser        " << endl;
     cout << "======================" << endl;
    
    char buffer[100];
    int grid=0, capacity=0, numnet=0;
    
    //read file and store as pair
    
    
    
    for(int i=0;i<=2;i++)
     {
      fin >> buffer;
      grid= atoi(buffer);
     }
    for(int i=0;i<=1;i++)
     {
      fin >> buffer;
      capacity = atoi(buffer);
     }
    for(int i=0;i<=2;i++)
     {
      fin >> buffer;
      numnet = atoi(buffer);
     }
    
    cout << "Grid:" <<  grid  << endl;
    cout << "Capacity:" << capacity <<endl;
    cout << "#Net:" << numnet <<endl;
    
    vector<pair<int,int> > source;
    source.resize(numnet);
    

     for(int i = 0; i <numnet; ++i)
     {
         fin >> buffer;
         int node = atoi(buffer);
         fin >> buffer;
         int x1 = atoi(buffer);
         fin >> buffer;
         int y1 = atoi(buffer);
         fin >> buffer;
         int x2 = atoi(buffer);
         fin >> buffer;
         int y2 = atoi(buffer);
         source[i]=make_pair ( FindVertex(grid, x1, y1), FindVertex(grid, x2, y2) );
         
         //cout << "node"<<node<<" : ("<<x1<<","<<y1<<")("<<x2<<","<<y2<<")"<<endl;
     }
    int punish_capacity=capacity;
    if(capacity>10)
    {
        punish_capacity=capacity/10;
    }
    
    //create adjacency matrix of graph
    vector< vector<int> > graph;
    graph.resize(grid*grid);
    for(int i=0;i<grid*grid;++i)
    {
       graph[i].resize(grid*grid);
    }
    
    for(int i=0;i<grid*grid;++i)
    {
        for(int j=0;j<grid*grid;++j)
        {
            if(i==j)
                graph[i][j]=0;
            else
                graph[i][j]=inf;
        }
    }
    
    vector<point> vertex;
    vertex.resize(grid*grid);
    for(int i=0; i<grid*grid ;i++)
    {
        vertex[i].d=0;
    }
    
    for(int i=1;i<grid*grid;i++)
    {
        if( i%grid !=0)
            addEdge(graph,i-1,i);
        if( i/grid >0 )
            addEdge(graph,i-grid,i);
    }
    
    vector<vector<int> >demand;
    demand.resize(grid*grid);
    for(int i=0;i<grid*grid;i++)
    {
        demand[i].resize(grid*grid);
    }
    for(int i=0;i<pow(grid,2);i++)
    {
        for(int j=0;j<pow(grid,2);j++)
        {
            demand[i][j]=0;
        }
    }
    vector<int > adj_u;
    adj_u.clear();
    vector<vector<int> > solution_path;
    solution_path.resize(numnet);
    
    //execute Dijkstra's Algorithm for all input source vertrex
    for(int i=0;i<source.size();i++)
    {
      Dijkstra(grid, vertex, graph, source[i].first);
     
      int d=source[i].second;
      while(vertex[d].pi!=d) //reweight and find solution path of source vertex
       {
        
         FindadjV2(graph, grid, adj_u, d);
         
           for(int a=0;a<adj_u.size();a++)
           {
               if(adj_u[a]!=vertex[d].pi)
               {
                   demand[adj_u[a]][d]+=1;
                   demand[d][adj_u[a]]+=1;
                   graph[adj_u[a]][d]=pow(2, demand[adj_u[a]][d]/capacity)+1;
                   graph[d][adj_u[a]]=pow(2, demand[d][adj_u[a]]/capacity)+1;
                
               }
               
           }
         
         //storing th solution
         solution_path[i].push_back(d);
         d=vertex[d].pi;
       }
        
        FindadjV2(graph, grid, adj_u, d);
        for(int a=0;a<adj_u.size();a++)
        {
            demand[adj_u[a]][d]+=1;
            demand[d][adj_u[a]]+=1;
            graph[adj_u[a]][d]=pow(2, demand[adj_u[a]][d]/capacity)+1;
            graph[d][adj_u[a]]=pow(2, demand[d][adj_u[a]]/capacity)+1;
        }
        
        solution_path[i].push_back(d);
      
    }
    
    


     // open the output file
     fstream fout;
     fout.open(argv[2],fstream::out);
     if(!fout.is_open())
     {
         cout << "Error: the output file is not opened!!" << endl;
         exit(1);
     }

     // output something to the output file

    for(int k=0;k<numnet;k++)
    {
        fout<<k<<" "<<solution_path[k].size()-1<<endl;
        
        for(int j=solution_path[k].size()-1;j>0;j--)
        {
            int u=solution_path[k][j];
            int v=solution_path[k][j-1];
            int x1=index2cordinate(grid, u).first;
            int y1=index2cordinate(grid, u).second;
            int x2=index2cordinate(grid, v).first;
            int y2=index2cordinate(grid, v).second;
            fout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
    }
    
    END = clock();
    cout <<"Execute time : "<< (END - START) / CLOCKS_PER_SEC <<" second"<< endl;
    return 0;
}

