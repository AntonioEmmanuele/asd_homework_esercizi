#include<iostream>
#include<vector>
#include<map>
using namespace std;
#define A_ASCII 97
int char_to_idx(const char to_convert,unsigned int starting_letter){
    return ((int)to_convert<starting_letter||(int)to_convert>122)?-1:(int)to_convert-97; //ritorna la conversione da carattere a numero
}

char idx_to_char(const int to_convert,unsigned int starting_letter){
  return (char)(to_convert+97);
}

int main(){
  /*Rappresentazione con matrice di adiacenza.
    Metto 1 dove ho un link
    a → c
    ↓   ↑
    b ← d

  */
  int m[4][4]={{0,1,1,0},{0,0,0,0},{0,0,0,0},{0,1,1,0}};
  vector<vector<int> > matrix;
  matrix.push_back(vector<int>(m[0],m[0]+sizeof(m[0])/sizeof(int)));
  matrix.push_back(vector<int>(m[1],m[1]+sizeof(m[1])/sizeof(int)));
  matrix.push_back(vector<int>(m[2],m[2]+sizeof(m[2])/sizeof(int)));
  matrix.push_back(vector<int>(m[3],m[3]+sizeof(m[3])/sizeof(int)));
  for(unsigned int i=0;i<matrix.size();i++){
    cout <<" I VICINI PER " << idx_to_char(i,A_ASCII)<< " SONO "<<endl;
    for(unsigned int j=0;j<matrix.size();j++){
      if(m[i][j]!=0){
        cout <<" " << idx_to_char(j,A_ASCII)<< " "<<endl;
      }
    cout<<endl;
    }
  }
  //Andiamo adesso con la rappresentazione a lista di adiacenza.
  vector<vector<char> >adjacency_list(4,vector<char>());
  adjacency_list[char_to_idx('a',A_ASCII)].push_back('b');
  adjacency_list[char_to_idx('a',A_ASCII)].push_back('c');
  adjacency_list[char_to_idx('d',A_ASCII)].push_back('b');
  adjacency_list[char_to_idx('d',A_ASCII)].push_back('c');
  for(unsigned int i=0;i<adjacency_list.size();i++){
    if(adjacency_list[i].size()!=0){
      cout<< "I vicini di "<< idx_to_char(i,A_ASCII)<<" sono "<<endl;
      for(unsigned int j=0;j<adjacency_list[i].size();j++)
        cout<<" "<<adjacency_list[i][j]<<" ";
      cout<<endl;
    }
    else
      cout<<idx_to_char(i,A_ASCII) <<" non ha vicini "<< endl;
  }
  //lista di adiacenza con un hashmap
  map<char,vector<char> > adjacency_list2;
  char n_a[]={'b','c'};
  adjacency_list2['a']=vector<char>(n_a,n_a+sizeof(n_a)/sizeof(char));
  adjacency_list2['b']=vector<char>();
  adjacency_list2['c']=vector<char>();
  adjacency_list2['d']=vector<char>(n_a,n_a+sizeof(n_a)/sizeof(char));
  for(auto it=adjacency_list2.cbegin();it!=adjacency_list2.cend(); ++it){
    cout<< "nodo "<<it-> first<<endl;
    if(it->second.size()==0)
      cout<<" non ha vicini"<<endl;
    else{
      cout <<" ha vicini ";
      for(unsigned int j=0;j<it->second.size();j++)
        cout<< it->second[j]<<" ";
      cout<<endl;
    }
  }
  return 0;
}
