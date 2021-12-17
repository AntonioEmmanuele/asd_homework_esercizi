#include <iostream>
#include <vector>
#include<map>
using namespace std;
#define WHITE 0
#define GRAY 1
#define BLACK 2
/*
  https://leetcode.com/problems/course-schedule/
*/
/*
  IN:
  2
  1
  1
  0
  2
  1
  0
  0
  1
  OUT
  true
  false
*/
//Controlla se ci  sono back edge per il nodo sorgente
//O(E)
bool topological_order_check(map<int,vector<int>> graph, map<int,unsigned int> &colors,int source){
  colors[source]=GRAY; //Inizializzalo a grigio
  bool check=true; //potrei incappare in un errore nella parte ricorsiva
  for(unsigned int i=0;i<graph[source].size();i++){
    //cout<<" Il colore per l'arco che va da "<< source << " ad "<< graph[source][i]<< " è "<< colors[graph[source][i]]<<endl;
    if(colors[graph[source][i]]==WHITE)
     check=topological_order_check(graph,colors,graph[source][i]);
    else if(colors[graph[source][i]]==GRAY) //Se ho un back edge
      return false;
  }
  colors[source]=BLACK;
  return check;
}
/*
E' bene notare che l'algoritmo si configura come il controllo dell'ordine topologico.
Se vige l'ordine topologico allora è possibile far andare tutto
*/
//Per controllare l'ordine topologico è necessario andare ad effettuare una visita in profondità.
//Se mentre la si sta effettuando si incontra un back edge, ossia da un nodo bianco cerco di andare ad un nodo
//grigio allora ritorno false.
//O(V+E)

bool check_order(vector<vector<int>> prerequisites){
  unsigned int idx;
  map<int,vector<int>> graph;
  map<int,unsigned int>colors;
  bool check =true;
  //Costruisci il grafo
  //Instanzia gli elementi
  for(idx=0;idx<prerequisites.size();idx++ )
    graph[prerequisites[idx][1]]=vector<int>();
  //metti i requisiti nella lista di adiacenza.
  for(idx=0;idx<prerequisites.size();idx++ )
    graph[prerequisites[idx][1]].push_back(prerequisites[idx][0]);
   /*for(auto it=graph.cbegin();it!=graph.cend();++it){
       cout<< "i requisiti per il corso  "<<it-> first<< " sono ";
       for(unsigned int i=0;i<it->second.size();i++)
        cout<< it->second[i]<<" ";
       cout<<endl;
   }*/
  //Adesso inizia l'algoritmo, coloro tutti i nodi di bianco
  for(auto it=graph.cbegin();it!=graph.cend();++it)
    colors[it->first]=WHITE;
  //Supponendo
  for(auto it=graph.cbegin();it!=graph.cend();++it){
    if(colors[it->first]==WHITE && check)
      check=topological_order_check(graph,colors,it->first);
  }
  return check;
}

int main(){
  unsigned int tests,num_prerequisites;
  cin>> tests;
  while(tests>0){
    cin>> num_prerequisites;
    vector<vector<int> > prerequisites(num_prerequisites,vector<int>(2,0));
    for(unsigned int i=0;i<num_prerequisites;i++){
      cin >>prerequisites[i][0];
      cin >>prerequisites[i][1];
    }
    if(check_order(prerequisites))
        cout<< "Ok"<<endl;
    else
        cout<<"Not ok"<<endl;
    tests--;
  }

}
