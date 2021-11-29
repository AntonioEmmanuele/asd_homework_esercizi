#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
//E' una soluzione se il numero di colone è pari alla dimensione della sequenza
bool is_a_solution(vector<vector<unsigned int> > matrix,vector<unsigned int>sequence){
    return sequence.size()==matrix[0].size();
}

//Calcola il costo
void process_solution(vector<vector<unsigned int> > matrix, vector<unsigned int>&sequence,vector<unsigned int>&last_sequence,unsigned int &cost){
      unsigned int actual_cost=0,i;
      bool check=false;
      //calc cost
      for( i=0;i<last_sequence.size();i++)
        actual_cost+=matrix[last_sequence[i]][i];
      if(cost==0 || cost>actual_cost){
        cost=actual_cost;
        sequence=last_sequence;
      }
      else if(cost==actual_cost){
        //trova quella lessicograficamente + piccola
        i=0;
        while(!check && i<last_sequence.size()){
          if(last_sequence[i]<sequence[i])
            check=true;
          else
            i++;
        }
        if(check){
          for( i=0;i<last_sequence.size();i++)
            sequence[i]=last_sequence[i];
        }
      }
}

//se è la prima colonna sono tutti i candidati, altrimenti i 3
vector<unsigned int> construct_candidates(vector<vector<unsigned int> > matrix,vector<unsigned int> last_sequence){
  vector<unsigned int>candidates;
  if(last_sequence.size()==0){
    for(unsigned int i=0;i<matrix.size();i++)
      candidates.push_back(i);
  }
  else{
    unsigned int last_row=last_sequence[last_sequence.size()-1];
    unsigned int last_col=last_sequence.size()-1;
    int prec=(int)last_row-1,succ=(int)last_row+1;
    candidates.push_back(last_row);
    if(prec<0)
      prec=matrix.size()-1;
    if(succ>matrix.size()-1)
      succ=0;
    candidates.push_back((unsigned int)prec);
    candidates.push_back((unsigned int)succ);
  }
  return candidates;
}

void  backtrack(vector<vector<unsigned int> > matrix, vector<unsigned int>&sequence,vector<unsigned int>&last_sequence,unsigned int &cost){
  unsigned int i;
  vector<unsigned int> candidates;
  vector<unsigned int> actual_solution;
  if(is_a_solution(matrix,last_sequence)){ //se è una soluzione
    process_solution(matrix,sequence,last_sequence,cost);
  }
  else{
    candidates=construct_candidates(matrix,last_sequence);
  /*  for(i=0;i<candidates.size();i++)
      cout<<candidates[i]<<" Allo step "<<last_sequence.size()<<endl;*/

    for(i=0;i<candidates.size();i++){
      //Make move
      last_sequence.push_back(candidates[i]);
      backtrack(matrix,sequence,last_sequence,cost);
      //unmake move
      last_sequence.pop_back();
    }
  }
}


int main(){

  ifstream my_file("matrici_2_3.txt");
  unsigned int row, col,row_idx,col_idx,cost;

  if(my_file.is_open()){
    while (my_file>>row ){
        my_file>>col;
        cost=0;
        //cout<<"First matrix"<<endl;
        //cout<< row<< " " <<col<< endl;
        vector<unsigned int> sequence,last_sequence;
        vector<vector<unsigned int> >matrix(row,vector<unsigned int>(col,0));

        for(row_idx=0;row_idx<row;row_idx++)
          for(col_idx=0;col_idx<col;col_idx++)
            my_file>>matrix[row_idx][col_idx];
        backtrack(matrix,sequence,last_sequence,cost);
        for(row_idx=0;row_idx<sequence.size();row_idx++)
          cout<<sequence[row_idx]+1<<" ";
        cout<<endl;
        cout<<cost<<endl;
    }
  }
  return 0;
}
