#include<iostream>
#include<map>
#include <vector>
#include<climits>
#include <queue>
using namespace std;
#define INF INT_MAX
//SI CONSIGLIA DI COMPILARE IN STANDARD C++ 14
//Theta(V)
void initialize_single_source(map<char,vector<char> > graph, map<char,int> &d,char source){
  for(auto it=graph.cbegin();it!=graph.cend();++it){
    //Inizializzazione delle distanze
    d[it->first]=INF;
    //Inizializzazione del vettore dei parent pointers.

  }
  d[source]=0;
}

//Invece di prendermi il nome del secondo nodo v, mi prendo la posizione nell'array degli archi adiacenti ad u.
//w è la funzione di costo
//Theta(1)
void relax(char u,char v1, unsigned int v, map<char,int>&d,map<char,vector<int> > w,map<char,char> &predecessors){
  int new_cost=w[u][v]+d[u];
  if(d[v1]>new_cost){ //Se mi conviene rilassare
    //rilassa
    d[v1]=new_cost;
    //Aggiorna predecessore.
    predecessors[v1]=u;
  }
}

//Theta(VlogV+E)
map<char,int> dijkstra(map<char,vector<char> > graph,  map< char,vector<int> > w , map<char,char> &predecessors,char source){
  map<char,int> d;
  unsigned int i;
  //Inizializza i nodi.
  initialize_single_source(graph,d,source);

  //Ora bisogna creare la coda a priorità
  //Nella coda vanno immessi i nomi ed il metodo di confronto è basato sulle distanze
  //In sostanza una lamba function come in rust è una estensione del function trait.
  //una lambda function può catturare(ossia prendere dallo scope attuale):
  //una costante [x]
  //un riderimento [&x]
  //tutte le variabili nello scope per riferimento [&]
  //un valore [=]
  //Qui sono costretto a passargli il riferimento in quando l'operatore [] con è usabile con i const map(potrei usarlo,
  //per inserire un nuovo oggetto nell'hashmap  )
  //Stabilico il criterio di comparazione, ossia che v deve essere più piccolo di u, sto andando a fare un min heap
  auto cmp= [&d](char u,char v){  return d[v]<=d[u];};
  //dichiaro la coda
  //Il template vuole il tipo di elemennti, il reale contenitore che la coda vuole, il tipo della funzione di comparazione
  priority_queue<char, vector<char>,decltype(cmp)> q(cmp);
  //Theta(V)
  for(auto it=graph.cbegin();it!=graph.cend();++it)
    q.push(it->first);


  //Theta(V*logV), esecuzione del while con extract min
  //+Theta(E) tempo complessivo per rilassare i vicini
  //Theta(VlogV+E)
  while(!q.empty()){ //finchè ho elementi per cui non ho eseguito l'algoritmo
  //  const char& min=q.top(); //sarebbe extract min, ossia la scelta greedy

    //Ora aggiona per ogni vertice vicino
    //q.top sarebbe il nodo per cui chiamo algo
    for(i=0;i<graph[q.top()].size();i++)
      relax(q.top(),graph[q.top()][i],i,d,w,predecessors); //rilassalo

    q.pop();
  }
  //Piccolo appunto, le code di c++ trattano l'underlying container come un heap.
  return d;
}

int main(){
  map<char, vector<char> > graph;
  map <char, vector<int>> w;
  char n_a[]={'B','C'};
  int c_a[]={10,3};
  char n_b[]={'D','C'};
  int c_b[]={2,1};
  char n_c[]={'B','D','E'};
  int c_c[]={4,8,2};
  char n_d[]={'E'};
  int c_d[]={7};
  char n_e[]={'D'};
  int c_e[]={9};
  graph['A']=vector<char>(n_a,n_a+sizeof(n_a)/sizeof(char));
  w['A']=vector<int>(c_a,c_a+sizeof(c_a)/sizeof(int));
  graph['B']=vector<char>(n_b,n_b+sizeof(n_b)/sizeof(char));
  w['B']=vector<int>(c_b,c_a+sizeof(c_b)/sizeof(int));
  graph['C']=vector<char>(n_c,n_c+sizeof(n_c)/sizeof(char));
  w['C']=vector<int>(c_c,c_c+sizeof(c_c)/sizeof(int));
  graph['D']=vector<char>(n_d,n_d+sizeof(n_d)/sizeof(char));
  w['D']=vector<int>(c_d,c_d+sizeof(c_d)/sizeof(int));
  graph['E']=vector<char>(n_e,n_e+sizeof(n_e)/sizeof(char));
  w['E']=vector<int>(c_e,c_e+sizeof(c_e)/sizeof(int));
  //Distanze sono in ordine:  0 - 7 - 3 - 9 - 5

  map<char,char> predecessors;
  map<char,int> d=dijkstra(graph,w,predecessors,'A');
  for(auto it=d.cbegin();it!=d.cend();++it)
    cout<< "Per il nodo "<< it->first << " la minima distanza da A è "<< it-> second<<endl;
  for(char k='B';k<='E';k++)
    cout<< "Il predecessore di "<< k << " è " << predecessors[k]<<endl;
  return 0;
}
