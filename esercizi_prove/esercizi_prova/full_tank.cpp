#include<iostream>
#include<map>
#include<vector>
#include<climits>
#include<fstream>
#define INF INT_MAX
#define IN_DBG 0
using namespace std;
/*
https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2352
*/
//O(n^2*max_c)
int find_path(vector<vector< vector<int > > > &dp,map<int,map< int,int> > graph, int source,int dest,int max_c, int actual_c,
vector<int> costs){

  if(dp[source][dest][actual_c]!=-1){
    //cout<<" Solved for"<< source << " "<<dest << " "<<dp[source][dest][actual_c]<<endl;
    return dp[source][dest][actual_c];
  }
  if(source==dest){
    dp[source][dest][actual_c]=0;
    return dp[source][dest][actual_c];
  }
  int actual=0,min=INF;
  for(auto it=graph[source].cbegin();it!=graph[source].cend();++it){
    //Se il percorso è percorribile
    if(it->second <= max_c){
        //Per ogni possibile ricarica che mi permetta di permettere il percorso e ricaricare a pieno la macchina
        for(unsigned int c=0;c<max_c;c++){
          if(actual_c+c >= it->second && actual_c+c <=max_c){
              int new_c=actual_c+c-it->second;
              actual=c*costs[source]+find_path(dp,graph, it-> first,dest,max_c,new_c,costs);
              //cout<<"Costo minimo per andare da i a j è"<<
              //cout<<actual<<endl;
              if(actual<min)
                min=actual;
          }
        }
    }
  }
  dp[source][dest][actual_c]=min;
  return dp[source][dest][actual_c];
}


int main(){
  ifstream myfile("full_tank_in.txt");
  if(myfile.is_open()){
    unsigned int n,m,u,v,d,num_queries,source,dest,cap;
    myfile>>n;
    myfile>>m;
    vector<int> costs(n,0);
    for(unsigned int i=0;i<costs.size();i++)
      myfile>>costs[i];
    map<int,map<int,int> >graph;

    for(unsigned int i=0;i<m;i++){
      myfile>>u;
      myfile>>v;
      myfile>>d;
      graph[u][v]=d;
      //Dovrebbe bastare un grafo diretto.
    }
#if IN_DBG
    cout<< n<< " "<<m<<endl;
    for(auto it=graph.cbegin();it!=graph.cend();++it){
      for(auto it2=it->second.cbegin();it2!=it->second.cend();++it2)
        cout<< it-> first<<" "<< it2-> first<<" "<< it2-> second<<endl;

    }
    cout<< endl;
#endif
    myfile>>num_queries;
    for(unsigned int i=0;i<num_queries;i++ ){
      vector<vector<vector<int> > >dp(n,vector<vector<int>> (n,vector<int>(cap,-1)));
      myfile>> cap;
      myfile>>source;
      myfile>>dest;
#if IN_DBG
      cout<< num_queries<<endl;
      cout<< cap<< " "<<source <<" "<<dest<<endl;
#endif
      bool check=false;
      for(auto it=graph.cbegin();it!=graph.cend();++it){
        for(auto it2=it->second.cbegin();it2!=it->second.cend();++it2)
          if(it2-> first==dest)
            check=true;
      }
      if(check)
        cout << find_path(dp,graph,source,dest,cap,0,costs)<<endl;
      else
        cout<<"Impossible"<<endl;
    }
#if IN_DBG
    cout<< "Fine"<<endl;
#endif
  }
  return 0;
}
