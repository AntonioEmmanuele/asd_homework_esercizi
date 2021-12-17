#include<iostream>
#include<map>
#include<vector>
#include <climits>
#include <stack>
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MINUS_INF INT_MIN
typedef char node_name;
using namespace std;
//Come prima cosa dobbiamo generare un ordinamento topologico del grafo.
//Per farlo andiamo a richiamare l'algoritmo di dfs ed andare ad  inserire un elemento in una linked list nel front
//Appena abbiamo finito con un nodo, diventa nero, dobbiamo inserirlo inn una linked list.
//O(E)
/*
void dfs_visit(map<node_name, vector<node_name>>graph,map<node_name,unsigned int> &colors,stack<node_name>& sorted,node_name source){
*/
void dfs_visit(map<node_name, vector<node_name>>graph,map<node_name,unsigned int> &colors,vector<node_name>& sorted,node_name source){

  colors[source]=GRAY;
  for(unsigned int i=0;i<graph[source].size();i++){ //Per ogni vicino adiacente di u
    if(colors[graph[source][i]]==WHITE){
      dfs_visit(graph, colors,sorted,graph[source][i]);
    }
  }
  colors[source]=BLACK;
  sorted.push_back(source); //Ho terminato l'esplorazione
}
//O(V+E)
/*
void dfs(map<node_name, vector<node_name>>graph,stack<node_name>&sorted){
*/
void dfs(map<node_name, vector<node_name>>graph,vector<node_name>&sorted){
  map<node_name,unsigned int> colors;
  for(auto it=graph.cbegin();it!=graph.cend();++it)
    colors[it->first]=WHITE;
  for(auto it=graph.cbegin();it!=graph.cend();++it)
    if (colors[it->first]==WHITE)
      dfs_visit(graph,colors,sorted,it->first);
}
//Theta(3V+2E)
int longest_path(map<node_name,vector<node_name> >graph,map<node_name,vector<int> > w, node_name source){
  map<node_name,int> distances;
  //stack<node_name> sorted;
  vector<node_name> sorted;
  node_name u,v;
  /*
  for(auto it=graph.cbegin();it!=graph.cend();++it)
    distances[it-> first]=MINUS_INF;
  distances[source]=0;*/


  dfs(graph,sorted);
  for( int i= sorted .size()-1;i>=0;i--)
      distances[sorted[i]]=MINUS_INF;
  distances[source]=0;

  //O(V+E)
  /*
  while (!sorted.empty()){ //Per ogni vertice nell'ordine topologico
  */
  for( int i= sorted .size()-1;i>=0;i--){
    u=sorted[i];
    for(unsigned int v=0;v<graph[u].size();v++){ //Per ogni suo vicino
      if(distances[graph[u][v]]<distances[u]+w[u][v]){ //Se la nuova distanza è maggiore della precedente, aggiorna
        //cout<< "Aggiorno l'attuale distanza " << distances[graph[u][v]]<<"per il nodo"<< graph[u][v] ;
        distances[graph[u][v]]=distances[u]+w[u][v];
        //cout << " con " <<distances[graph[u][v]] <<endl;
      }
    }
    //sorted.pop(); //posso rimuoverlo
  }
  //prendi la massima distanza
  int max=MINUS_INF;
  for(auto it=distances.cbegin();it!=distances.cend();++it){
    //cout<< "Per il nodo "<< it-> first << " La distanza è "<< it-> second <<endl;
    if(distances[it->first]>max)
      max=distances[it->first];
  }
  return max;
}
int main(){
  char n_s[]={'A','C'};
  char n_c[]={'A','D'};
  char n_a[]={'B'};
  char n_b[]={'D','E'};
  char n_d[]={'E'};
  char n_e[]={'E'};

  int d_s[]={1,2};
  int d_c[]={4,3};
  int d_a[]={6};
  int d_b[]={1,2};
  int d_d[]={1};

  map<char,vector<char> > graph;
  map<char, vector<int> > distances;
  graph['S']=vector<char>(n_s,n_s+sizeof(n_s)/sizeof(char));
  graph['C']=vector<char>(n_c,n_c+sizeof(n_c)/sizeof(char));
  graph['A']=vector<char>(n_a,n_a+sizeof(n_a)/sizeof(char));
  graph['B']=vector<char>(n_b,n_b+sizeof(n_b)/sizeof(char));
  graph['D']=vector<char>(n_d,n_d+sizeof(n_d)/sizeof(char));
  //graph['E']=vector<char>(n_e,n_e+sizeof(n_e)/sizeof(char));

  distances['S']=vector<int>(d_s,d_s+sizeof(d_s)/sizeof(int));
  distances['C']=vector<int>(d_c,d_c+sizeof(d_c)/sizeof(int));
  distances['A']=vector<int>(d_a,d_a+sizeof(d_a)/sizeof(char));
  distances['B']=vector<int>(d_b,d_b+sizeof(d_b)/sizeof(char));
  distances['D']=vector<int>(d_d,d_d+sizeof(d_d)/sizeof(int));
  cout<< longest_path(graph,distances,'S')<<endl;
  
  //vector<char> sorted; //stamparlo al contrario
  /*
  stack <char> s;
  dfs(graph,s);
  while(!s.empty()){
    cout <<s.top()<<" ";
    s.pop();
  }
  cout<<endl;*/

  return 0;
}
