#include <iostream>
#include<vector>
#include<fstream>
static unsigned int actual_size=0,largest_size=0,starting_row,ending_row=INT_MAX,starting_col,ending_col;
static unsigned int starting_row_def,ending_row_def,starting_col_def,ending_col_def;
using namespace std;
//O(n^3)
unsigned int maximal_rectangle(vector < vector <unsigned int> > rec,unsigned int r,unsigned int c){
  //cout<<"called for"<< r << " "<< c<< endl;
  //Se sono giunto alla fine
  if(r==rec.size()  && c==0)
    return (ending_col_def-starting_col_def+1)*(ending_row_def-starting_row_def+1); //base* altezza
  //se non sono giunto alla fine
  else
  {

    if(rec[r][c]==1)
    {
      //Se stiamo ricominciando, ossia il precedente era 0
      if(actual_size==0)
      {
        starting_row=r;
        starting_col=c;
        ending_col=starting_col;
        actual_size=1;
        //Trova lunghezza primo
        ending_row=r;
        unsigned int i=r+1;
        while(i<rec.size() && rec[i][c]==1){
          ending_row=i,
          i++;
        }
      }
      //Altrimenti se il precedente non era zero devo aggiornare solo l'ending column
      else
      {
        actual_size+=1;
        ending_col=c;
        //Devo adesso trovare la lunghezza massima del rettangolo, ricorda che è sempre la più piccola quindi la vado sempre
        //ad aggiornare
        //ie   1 1 1
        //     1 1 0
        //ending row deve essere 1
        unsigned int minimum_ending=r;
        unsigned int i=r+1;
        while(i<rec.size() && rec[i][c]==1){
          minimum_ending=i,
          i++;
        }
        if(minimum_ending<ending_row)
          ending_row=minimum_ending;
      }
      //Aggiornamento del largest
      if(actual_size>largest_size)
      {
          largest_size=actual_size;
          starting_row_def=starting_row;
          ending_row_def=ending_row;
          starting_col_def=starting_col;
          ending_col_def=ending_col;
      }
    }
    else
    {
      actual_size=0;
    }

    //avanzo
    if(c<rec[0].size()-1)
      return maximal_rectangle(rec,r,c+1); //nnon sono arrivato all'ultima colonna
    else{ //sono arrivato all'ultima colonna
      actual_size=0;
      return maximal_rectangle(rec,r+1,0);
    }
  }
}

int main(){
  ifstream mat("matrix_max_rec.txt");
  unsigned int row, col,i,j;
  if(mat.is_open()){
    while(mat>>row){
      mat>>col;
      vector< vector <unsigned int > > rec(row,vector< unsigned int > (col,0));
      for(i=0;i<row;i++)
        for(j=0;j<col;j++)
          mat>>rec[i][j];
      cout<<maximal_rectangle(rec,0,0)<<endl;
      actual_size=0;
      largest_size=0;
    }
  }
  else
    cout<<"Not opened"<<endl;
  return 0;
}
