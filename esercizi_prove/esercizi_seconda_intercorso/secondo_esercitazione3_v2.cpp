#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
#define INF INT_MAX
vector<unsigned int > actual_seq;
static unsigned int  test[6]={0,1,2,3,3,4};
vector<unsigned int> choices(test, test+sizeof(test)/sizeof(unsigned int));
//Numero sottoproblemi : M ->numero colonne
//Guessing O(n) -> Numero righe
//O(m*n)
unsigned int costo_minimo(vector<vector<unsigned int> > matrix,vector <unsigned int>& sequence,unsigned int row, unsigned int col){
  unsigned int min_cost=INF,costo,i,j;
  if(col<matrix[0].size()){
    //Generazione della mossa
    int prec,succ;
    vector<unsigned int> tentativi;
    if(row==0&&col==0){
      for(unsigned int i=0;i<matrix.size();i++)
        tentativi.push_back(i);
    }
    else{
      tentativi.push_back(row);
      succ=(int)row+1;
      prec=(int)row-1;
      if(prec<0)
        prec=matrix.size()-1;
      if(succ>matrix.size()-1)
        succ=0;
      tentativi.push_back(prec);
      tentativi.push_back(succ);
      //cout<< "for row "<< row << "prec and succ"<< prec << succ<< endl;
    }

    for(i=0;i<tentativi.size();i++){
      costo=matrix[tentativi[i]][col]+costo_minimo(matrix,sequence,tentativi[i],col+1);
      if(costo<=min_cost){
        if(costo<min_cost){
          min_cost=costo;
          sequence[col]=tentativi[i];
        }
        else if(costo==min_cost){
          if(sequence[col]>tentativi[i])
            sequence[col]=tentativi[i];
        }
        //Quando siamo arrivati alla fine copialo
        if(col==0)
          actual_seq=sequence;
      }
    }
    return min_cost;
  }
  else{
    return 0;
  }
}
int main(){
  ifstream file("matrici_2_3.txt");
  unsigned int row, col,i,j,costo;
  if(file.is_open()){
    while(file>>row){
        file>>col;
        vector<vector<unsigned int> > matrix(row,vector<unsigned int>(col,0));
        vector<unsigned int> sequence(col,0);
        for(i=0;i<row;i++)
          for(j=0;j<col;j++)
            file>>matrix[i][j];
        costo=costo_minimo(matrix,sequence,0,0);
        cout<<"Len "<<actual_seq.size()<<endl;
        for(i=0;i<actual_seq.size();i++){
            cout<<actual_seq[i]+1<<" ";
        }
        cout<<endl<<costo<<endl;
        actual_seq.clear();
    }
  }
  return 0;
}
