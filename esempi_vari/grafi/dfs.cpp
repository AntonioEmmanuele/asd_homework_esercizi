#include<iostream>
#include<map>
#include <vector>
using namespace std;
#define WHITE 0
#define GRAY 1
#define BLACK 2
/*
  DFS porta alla seguente classificazione degli archi, che dipende  da dove iniziamo la ricerca.
  Abbiamo i :
  tree edge-> (u,v) , v è scoperto tramite u. (Grigio-> bianco)
  back edge-> (u,v) v è però un antenato di u, quindi sto percorrendo un ciclo (grigio-> grigio)
  forward edge-> (u,v) ma u è già unn antenato di v, (grigio ->nero con f[v]>d[u],ossia che non abbiamo finito di esplorare albero)
  cross edge->  arco tra due alberi diversi(cross)(grigio->nero con f[v]<d[u], ossia che abbiamo iniziato ad esplorare u in un altro albero )
  Tempi di inizio e fine hanno una struttura a parentesi.
*/
/Partendo da un nodo u esegui una visita in profondità
//O(E)
void dfs_visit(map<char,vector<char> > graph, map<char,unsigned int>& colors,char u,
  unsigned int &time,map<char,unsigned int> &d, map<char,unsigned int>&f,map<char,char>& predecessors){
  colors[u]=GRAY; //Lo sto iniziando ad esplorare
  time=time+1; //incremento il time stamp
  d[u]=time; //Il tempo in cui ho raggiunto il nodo la prima volta.
  for(unsigned int i=0;i<graph[u].size();i++){ //Per ogni nodo adiacente
    if(colors[graph[u][i]]==WHITE){ //Se non è stato esplorato, cosa che può succedere
      predecessors[graph[u][i]]=u; //imposta il predecessore.
      dfs_visit(graph, colors,graph[u][i],time,d,f,predecessors);//Richiama la procedura sul primo nodo
    }
  }
  colors[u]=BLACK; //ho terminato l'esplorazione
  time++;
  f[u]=time; //Inserisci il tempo di fine dopo aver aggiornato il contatore.
}

//ordered  dipende dal fatto che sto usando una rappresentazioen con un hashmap per usare le lettere
//Se avessi usato vettori classici non sarebbe stato necessario
//O(V+E)
void dfs(map<char,vector<char> > graph, map<char,unsigned int> &d, map<char ,unsigned int>& f, map<char,char>&predecessors,
vector<char> ordered){
  unsigned int time=0;//Inizializza il contatore a zero
  map<char,unsigned int> colors; //colori
  /*
  for(auto it =graph.cbegin();it!=graph.cend();++it){ //Inizializza i colori a bianco
    colors[it->first]=WHITE;
  }

  //Inizia la visita
  //O(V+E)
  for(auto it =graph.cbegin();it!=graph.cend();++it){ //Inizializza i colori a bianco
    if(colors[it->first]==WHITE) //Posso avere più alberi, ossia punti in cui ricomincio la visita
      dfs_visit(graph,colors,it->first,time,d,f,predecessors);
  }*/
  for(unsigned int idx=0;idx<ordered.size();idx++)
    colors[ordered[idx]]=WHITE;
  //O(V+E)
  for(unsigned int idx=0;idx<ordered.size();idx++){ //Inizializza i colori a bianco
    if(colors[ordered[idx]]==WHITE) //Posso avere più alberi, ossia punti in cui ricomincio la visita
      dfs_visit(graph,colors,ordered[idx],time,d,f,predecessors);
    }
  //cout<< "Alla fine il tempo è "<< time<<endl;
}


int main(){
  //Esempio slides 18, 25
  char n_u[]={'v','x'};
  char n_x[]={'v'};
  char n_v[]={'y'};
  char n_y[]={'x'};
  char n_w[]={'y','z'};
  char n_z[]={'z'};
  map < char, vector< char> > graph;
  graph['u']=vector<char>(n_u,n_u+sizeof(n_u)/sizeof(char));
  graph['x']=vector<char>(n_x,n_x+sizeof(n_x)/sizeof(char));
  graph['v']=vector<char>(n_v,n_v+sizeof(n_v)/sizeof(char));
  graph['y']=vector<char>(n_y,n_y+sizeof(n_y)/sizeof(char));
  graph['w']=vector<char>(n_w,n_w+sizeof(n_w)/sizeof(char));
  graph['z']=vector<char>(n_z,n_z+sizeof(n_z)/sizeof(char));
  map<char,unsigned int> d;
  map<char,unsigned int > f;
  map<char,char > p;
  //Genera il vettore ordinato
  vector<char> ordered;
  for(auto it=graph.cbegin();it!=graph.cend();++it)
    ordered.push_back(it->first);
    sort(ordered.begin(),ordered.end());
  dfs(graph,d,f,p,ordered);
  for(unsigned int idx=0;idx<ordered.size();idx++){
    cout<<" Per nodo "<< ordered[idx]<< " ho tempi di inizio "<< d[ordered[idx]]<< " e di fine "<< f[ordered[idx]];
    cout << " Inoltre il suo predecessore è "<< p[ordered[idx]]<< endl;
  }
  return 0;
}
