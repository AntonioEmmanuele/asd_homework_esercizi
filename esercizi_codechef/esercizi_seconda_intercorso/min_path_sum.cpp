#include <iostream>
#include<vector>
#include<fstream>
using namespace std;

/*
https://leetcode.com/problems/edit-distance/
*/
unsigned int min_path_sum(vector<vector<unsigned int > > mat,unsigned int current_x,unsigned int current_y){
  unsigned int row_max=mat.size()-1,col_max=mat[0].size()-1;
  //Se sono giunto alla fine allora ritono l'ultimo elemento
  if(current_x==row_max && current_y==col_max)
      return mat[current_x][current_y];
  //Altrimenti ritorno l'elemento corrente più il minimo dei canditati(Possibili scelte)

  //Posso muovermi solo in basso o right ossia a destra.
  if(current_x==row_max ) //Posso muovermi solo di lato in questo caso(ho raggiunto ultima riga)
    return mat[current_x][current_y]+min_path_sum(mat,current_x,current_y+1);
  if(current_y==col_max) //Posso muovermi solo in basso
    return mat[current_x][current_y]+min_path_sum(mat,current_x+1,current_y);
  return mat[current_x][current_y]+min(min_path_sum(mat,current_x+1,current_y),min_path_sum(mat,current_x,current_y+1));

}


int main() {
    ifstream matrici("matrici_min_path_sum.txt");
    unsigned int row,col,i,j;
    if(matrici.is_open()){
        while(matrici>>row){
            matrici>>col;
            vector<vector<unsigned int> > mat(row,vector<unsigned int>(col,0) );
            for(i=0;i<row;i++){
                for(j=0;j<col;j++){
                    matrici>>mat[i][j];
                }
            }
            cout<<min_path_sum(mat,0,0)<<endl;
            /*
            for(i=0;i<row;i++){
                for(j=0;j<col;j++){
                   cout<<mat[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;*/
        }
    }
	return 0;
}
