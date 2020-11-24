#include <vector>
#include <csignal>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#define VERT_NUM  5

using namespace std;
vector<int> cur_best_clique;

vector<vector<int>> graph(VERT_NUM);

vector<int> my_set_intersection(vector<int> &a , vector<int> &b)
{
    vector<int> c(a.size() + b.size());
    vector<int>::iterator it = set_intersection(a.begin(),a.end(),b.begin(),b.end(),c.begin());
    c.resize(it - c.begin());
    return c;
}

void easy_clique_finder(vector<vector<int>> &graph , vector<int> &cur_candidate , vector<int> &cur_clique)
{
    
    /*
    Enumerate all possible combination
    This will not work, just for example, write a smarter algorithm
    */
    for(int i = 0 ; i < cur_candidate.size() ; i ++){
        int v = cur_candidate[i];
        vector<int> new_candidate = my_set_intersection(cur_candidate , graph[v]);
        cur_clique.push_back(v);
        
        if( cur_clique.size() > cur_best_clique.size() ){
            cur_best_clique = cur_clique;   // store the largest clique you can find
        }
        easy_clique_finder( graph , new_candidate , cur_clique );
        cur_clique.pop_back(); 
    }
    
    

    return ;
}

void signalHandler( int signum ) {
    /*

    In the signal handler, we output the current best clique that we found.

    */
    fstream out;
    out.open("clique.txt" , ios::out);
    sort(cur_best_clique.begin() , cur_best_clique.end());

    for(int v : cur_best_clique){
        out<<v<<endl;
    }

    exit(signum);
}


int main(int argc , char *argv[])
{
    
    signal(SIGINT, signalHandler);
    freopen(argv[1] , "r" , stdin);
    int K = stoi(argv[2]);
    
    vector<int> candidates , cur_clique;
    for(int i = 0 ; i < VERT_NUM ; i++){
        candidates.push_back(i);
    }
    int A , B;

    while(cin >> A >> B){
        if(A == B){
            continue;
        }
        graph[A].push_back(B);
        graph[B].push_back(A);
    }
    for(int i = 0 ; i < VERT_NUM ; i++){
        sort(graph[i].begin(), graph[i].end());
    }
    easy_clique_finder(graph , candidates , cur_clique);


    /*

    Don't forget to write normal output here, in case your program terminated before SIGINT is received 

    */

    fstream out;
    out.open("clique.txt" , ios::out);
    sort(cur_best_clique.begin() , cur_best_clique.end());

    for(int v : cur_best_clique){
        out<<v<<endl;
    }
}

