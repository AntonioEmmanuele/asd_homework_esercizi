#include<iostream>
#include<vector>
#include<map>
#include <queue>
using namespace std;
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define DBG 0
//O(V+E)
void bfs(map<char,vector<char> > graph, char source,
  map<char,char>&predecessors,map<char,unsigned int > &distances,char starting_letter,char ending_letter){
  map<char,unsigned int> colors; //Vettore dei colori
  char u; //Appoggio per il grafo
  unsigned int j;
  queue<char> gray_queue; //coda che contiene tutti i nodi grigi
  //Nessun nodo è stato visitato ancora.
  for(char it=starting_letter;it<=ending_letter;it++) //O(V)
    colors[it]=WHITE;
  //Iniziamo con il visitare il primo
  colors[source]=GRAY;
  gray_queue.push(source); //La coda deve sempre contenere i nodi grigi
  distances[source]=0; //Distanza della sorgente a se stessa è 0
  predecessors[source]=' '; // non ha predecessori
  //O(V+E)
  while(!gray_queue.empty()){ //finchè la coda contiene nodi grigi
    u=gray_queue.front(); //prendi il primo elemento
    gray_queue.pop(); //Rimuovilo
    //gray_queue.
    for (j=0;j<graph[u].size();j++){
      if(colors[graph[u][j]]==WHITE){ // se è inesplorato
        colors[graph[u][j]]=GRAY;
        predecessors[graph[u][j]]=u; // Lo visito partendo da u
        distances[graph[u][j]]=distances[u]+1;//è per forza di cose la distanza del precedente da s +1
        gray_queue.push(graph[u][j]);
      }
    }
    colors[u]=BLACK; //Finito l'esplorazione
#if DBG
    cout<<"Sono al nodo"<< u<<endl;
#endif
  }
}
//Stampo uno shortest path da s a v.
//Ho shortest path possono essere multipli a seconda del nodo sorgente e della destinazione
//ovviamente sono molti gli shortest path.
//O(height(BFT))-> dipende dall'altezza dell'albero che costruiamo.
void print_path(map<char,char> predecessors ,char s,char v){
  if (s==v)
    cout<<s<<endl;
  else if(predecessors[v]==' ')
    cout<< "No path exist"<<endl;
  else{
    print_path(predecessors,s,predecessors[v]); // Vai a ritroso
    cout<< v << endl;
  }
}
int main(){

  map<char ,vector<char> > graph;
  char n_r[]={'s','v'};
  char n_v[]={'r'};
  char n_s[]={'r','w'};
  char n_w[]={'s','t','x'};
  char n_t[]={'w','u','x'};
  char n_u[]={'t','y','x'};
  char n_x[]={'t','u','y'};
  char n_y[]={'u','x'};
  graph['r']=vector<char>(n_r,n_r+sizeof(n_r)/sizeof(char));
  graph['v']=vector<char>(n_v,n_v+sizeof(n_v)/sizeof(char));
  graph['s']=vector<char>(n_s,n_s+sizeof(n_s)/sizeof(char));
  graph['w']=vector<char>(n_w,n_w+sizeof(n_w)/sizeof(char));
  graph['t']=vector<char>(n_t,n_t+sizeof(n_t)/sizeof(char));
  graph['u']=vector<char>(n_u,n_u+sizeof(n_u)/sizeof(char));
  graph['x']=vector<char>(n_x,n_x+sizeof(n_x)/sizeof(char));
  graph['y']=vector<char>(n_y,n_y+sizeof(n_y)/sizeof(char));
  /*for(auto it=graph.cbegin();it!=graph.cend(); ++it){
    cout<< "nodo "<<it-> first<<endl;
    if(it->second.size()==0)
      cout<<" non ha vicini"<<endl;
    else{
      cout <<" ha vicini ";
      for(unsigned int j=0;j<it->second.size();j++)
        cout<< it->second[j]<<" ";
      cout<<endl;
    }
  }*/
  vector <char> ordered_nodes;
  for(auto it=graph.cbegin();it!=graph.cend(); ++it)
    ordered_nodes.push_back(it->first);
  sort(ordered_nodes.begin(),ordered_nodes.end()); //Li ordino per un fatto mio , non è necessario.-
  vector<pair<char,char> >pred;
  map<char,char> predecessors;
  map<char, unsigned int> distances;
  bfs(graph,'s',predecessors,distances,'r','y');
  /*cout<< "Le distanze sono"<<endl;
  for(auto i=distances.cbegin();i!=distances.cend();++i){
    cout<<"Distanza di "<< i-> first <<" dal nodo "<< " s "<< " è "<< i-> second<<endl;
  }*/
  for(unsigned int i=0;i<ordered_nodes.size();i++)
    cout<<" Il predecessore di "<<ordered_nodes[i]<<" è"<< predecessors[ordered_nodes[i]]<< " la distanza "<< distances[ordered_nodes[i]]<<endl;
  print_path(predecessors,'s','y');
  return 0;
}
