#include<iostream>
#include<map>
#include<vector>
#include <queue>
#define WHITE 0
#define GRAY 1
#define BLACK 2
using namespace std;
/*
 https://leetcode.com/problems/clone-graph/
 */
/* Grafo connesso non diretto, voglio creare una deep copy*/
//Voglio generare una deep copy di un grafo, ossia copiare elemento per elemento
//Partendo da un nodo sorgente genera una copia, posso usare la ricerca in ampiezza per ricostruire
//il mio grafo
//O(V+E)
map<int, vector<int>> deep_copy(map<int,vector<int> > graph, int source){
  map<int, vector<int>> copy;
  map<int,unsigned int> colors;
  int u;
  unsigned int adj_idx;
  queue<int> gray_queue;
  //Inizializzo.
  for(auto it=graph.cbegin(); it!= graph.cend();++it){
    colors[it-> first]=WHITE;
  }
  colors[source]=GRAY;
  gray_queue.push(source);
  while(!gray_queue.empty()){ //Finchè la coda nonn è vuota
    u=gray_queue.front();
    copy[u]=vector<int>();
    for(adj_idx=0;adj_idx<graph[u].size();adj_idx++){ //Copia i vicini
      copy[u].push_back(graph[u][adj_idx]);
      if(colors[graph[u][adj_idx]]==WHITE){ //Se non è stato ancora esplorato allora mettilo nella coda
        colors[graph[u][adj_idx]]=GRAY;
        gray_queue.push(graph[u][adj_idx]);
      }
    }
    gray_queue.pop();
    colors[u]=BLACK;
  }
  return copy;
}
int main(){
  int n1[]={2,4};
  int n2[]={1,3};
  int n3[]={3,4};
  int n4[]={1,3};
  map<int,vector<int>> graph;
  graph[1]=vector<int>(n1,n1+sizeof(n1)/sizeof(int));
  graph[2]=vector<int>(n2,n2+sizeof(n2)/sizeof(int));
  graph[3]=vector<int>(n3,n3+sizeof(n3)/sizeof(int));
  graph[4]=vector<int>(n4,n4+sizeof(n4)/sizeof(int));

  map<int,vector<int>> copy=deep_copy(graph,1);
  for(auto it=graph.cbegin();it!=graph.cend();++it){
      cout<< " per il nodo "<< it-> first << " i vicini sono ";
    for(unsigned int i=0;i<it->second.size();i++)
      cout<<  it-> second[i] << " ";
    cout<< endl;
  }
  cout<<"per il  grafo copia ho"<<endl;

  for(auto it=copy.cbegin();it!=copy.cend();++it){
      cout<< " per il nodo  copia "<< it-> first << " i vicini sono ";
    for(unsigned int i=0;i<it->second.size();i++)
      cout<<  it-> second[i] << " ";
    cout<< endl;
  }
  return 0;
}
