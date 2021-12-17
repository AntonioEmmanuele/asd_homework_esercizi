#include <iostream>
#include<vector>
#include <map>
#include <climits>
#include <queue>
#include<fstream>
#include<cmath>
using namespace std;
#define INF INT_MAX
/*
https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1219
*/
//Inizializza le distante
//Theta(V)
void initialize_single_source( map<int,vector<int> > graph,map <int,int> &d,const int source){
  for(auto it=graph.cbegin();it!=graph.cend();++it)
    d[it->first]=INF;
  d[source]=0;
}
//Theta(1)
void relax(const int u,const int v,const int v_idx, map<int, vector <int> >w ,map <int,int> &d){
  int n=w[u][v_idx]+d[u];
  if(d[v]>n)
    d[v]=n;
}
//Theta (VlogV+E)
map<int,int>  dijkstra( map<int,vector<int> > graph,  map<int,vector<int> > w,const int source ){
  map<int,int> d;
  unsigned int i;
  //Inizializza le distanze
  initialize_single_source(graph,d,source);
  //Genera la coda
  auto cmp=[&d](int v,int v2)-> bool{ return d[v2]<=d[v];};
  priority_queue<int,vector<int>,decltype(cmp)> q(cmp);
  for(auto it= d.cbegin();it!=d.cend();++it)
    q.push(it->first);
  //Esegui algoritmo
    while(!q.empty()){
      for(i=0;i<graph[q.top()].size();i++)
        relax(q.top(),graph[q.top()][i],i,w,d);
    q.pop();
  }
  return d;
}

//Trova la stazione + vicina a j
//O(M), M è il numero di stazioni
unsigned int nearest(vector<int>stazioni,map<int,map<int,int> > distances,int j){
  int actual=INF;
  unsigned int to_ret=0;
  for(unsigned int i=0;i<stazioni.size();i++){
    if(actual>distances[j][stazioni[i]]){
        actual=distances[j][stazioni[i]];
        to_ret=i;
    }
  }
  return to_ret;
}

//Theta(V*(VlogV+E))
map<int,map<int,int> > dijkstra_mul_source( map<int,vector<int> > graph,const  map<int,vector<int> > w){
  //per ogni sorgente calcola la distanza
  map <int,map<int,int> > distances;
  for(auto it=graph.cbegin();it!=graph.cend();++it)
    distances[it->first]=dijkstra(graph,w,it->first);
  return distances;
}

//Theta(V^2(logV+M))
int solve(const vector <pair<int,int>> incroci, vector<int> costi, vector< int> stazioni){
  map<int,vector<int> >graph;
  map<int,vector<int> > w;
  unsigned int i,j;
  //Theta(V)
  for( i=0;i<incroci.size();i++){
    graph[incroci[i].first]=vector<int> ();
    w[incroci[i].first]=vector<int> ();
  }
  for(unsigned int i=0;i<incroci.size();i++){
    graph[incroci[i].first].push_back(incroci[i].second);
    graph[incroci[i].second].push_back(incroci[i].first);
    w[incroci[i].first].push_back(costi[i]);
    w[incroci[i].second].push_back(costi[i]);
  }
  /*
  for(auto it=graph.cbegin();it!=graph.cend();++it){
    cout<< "Per il nodo "<< it-> first<<endl;
    for(i=0;i<it->second.size();i++)
      cout<< " " <<it-> second[i]<<" "<< w[it->first][i]<< " ";
    cout<<endl;
  }*/

  //V^2(logV)
  map<int,map<int,int> > distances=dijkstra_mul_source(graph,w);
  /*
  for(auto it=distances.cbegin();it!=distances.cend();++it){
    cout<< "Per il nodo "<< it-> first<< " Le distanze sono "<<endl;
    for(auto it2=it->second.cbegin();it2!=it->second.cend();++it2)
      cout<<"   Distanza con "<< it2-> first<< " "<< it2-> second<< endl;
    cout<<endl;
  }*/
  int soluzione;
  int actual_min;
  int min=INF;
  unsigned int n;
  //O(V2*M)
  //Ora passiamo all'algoritmo vero e proprio, per ogni stazione, determina la Distanza

  //Per ogni scelta
  for(auto it=graph.cbegin();it!=graph.cend();++it){ //O(V)
    stazioni.push_back(it->first);//O(1)

    /*for(unsigned int i=0;i<stazioni.size();i++)
      cout<<stazioni[i]<<endl;
    cout<<endl;*/

    actual_min=0;
    //Calcola le distanze
    for(auto it=graph.cbegin();it!=graph.cend();++it){ //O(V)
      //Trova la stazione più vicina
      n=nearest(stazioni,distances,it->first);
      //cout<<"la stazione più vicina ad"<< it-> first << "è "<<stazioni[n]<<endl;
      actual_min+=distances[it->first][stazioni[n]];
    }
    if(actual_min<min){
      min=actual_min;
      soluzione=it->first;
    }
    else if(actual_min==min){
      //Se sono uguali scegli il più Piccolo
      if(soluzione>=it->first)
        soluzione=it->first;
    }
    stazioni.pop_back();//O(1)
  }

  return soluzione;
}
int main(){
  ifstream myfile("fire_station_in.txt");
  if(myfile.is_open()){
    unsigned int t,f,i;
    myfile>>t;
    while(t>0){
      myfile>>f;
      myfile>>i;
      vector<int> stazioni(f,0);
      vector<pair<int,int>>incroci;
      pair<int,int> h;
      vector<int> costi(i,0);
      for(unsigned int j=0;j<f;j++)
        myfile>>stazioni[j];
      for(unsigned int j=0;j<i;j++){
        myfile>>h.first;
        myfile>>h.second;
        myfile>>costi[j];
        incroci.push_back(h);
      }
      cout<<solve(incroci,costi,stazioni)<<endl;
      t--;
    }
  }
  return 0;
}
