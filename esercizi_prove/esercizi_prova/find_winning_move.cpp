#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
/*
https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1052
*/

#define DBG_SOL 0
//O(n^2), n=4 :)
bool is_a_solution(vector<vector<char > >board ){
#if DBG_SOL
  cout<<"Input "<< endl;
  for(unsigned int i=0;i<4;i++){
    for(unsigned int j=0;j<4;j++){
      cout<<board[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
#endif
  bool check=true;
  int i=1,j=2;
  //controlla la diagonale principale
  while(i<4 && check){  //O()
    if(board[i][i]!=board[i-1][i-1])
      check=false;
    i++;
  }
  if(check){
#if DBG_SOL
    cout<< " Sulla diagonale principale"<<endl;
#endif
    return true;
  }
  //Controlla la diagonale secondaria.
  i=1;
  check=true;
  while(i<4&&j>=0&&check){
    if(board[i][j]!=board[i-1][j+1])
      check=false;
    i++;
    j--;
  }
  if(check){
#if DBG_SOL
    cout<<"Sulla diagonale secondaria"<<endl;
#endif
    return true;
  }
  //controlla ogni riga
  for( i=0;i<4;i++){
    j=1;
    while(board[i][j]==board[i][j-1] && j<4)
      j++;
    if(j==4){
#if DBG_SOL
      cout<<"In riga "<<i<< endl;
#endif
      return true;
    }

  }
  //controlla ogni colonna
  for( j=0;j<4;j++){
    i=1;
    while(board[i][j]==board[i-1][j] && i<4)
      i++;
    if(i==4){
#if DBG_SOL
      cout<<"In colonna "<<j<< endl;
#endif
      return true;
    }
  }
#if DBG_SOL
  cout<<"Non è soluzione"<<endl;
#endif
  return false;
}

bool solve(vector< vector<char > > board, char in,char winner, char loser,pair<int,int> &winning_pos){
//  cout<<"Called"<<endl;
  if(is_a_solution(board)){ //O(n^2)
    if(in==loser) //Ultima mossa  è stata del winner, ritorno true.
      return true;
    else
      return false;
  }
  else{
    //Devo assicurarmi per il loser che per ogni sua mossa perda, in maniera tale che il winner abbia una vittoria forzata
    if(in==loser){
      //cout<<"Sono il perdente"<<endl;
      int i=0,j=0;
      bool check=true;
      //O(n^2)
      while(i<4 && check){
        while(j<4 &&  check){
            if(board[i][j]=='.'){
              board[i][j]=in;
              check=solve(board,winner,winner,loser,winning_pos); //come diventa true mi fermo
              board[i][j]='.';
            }
            j++;
          }
          j=0;
          i++;
      }
      return check;
    }

    else if(in==winner){
      int i=0,j=0;
      bool check=true;
      //O(n^2)
      while(i<4 && check){
        while(j<4 && check){
          if(board[i][j]=='.'){
            board[i][j]=in;
            check=solve(board,loser,winner,loser,winning_pos); //come diventa true mi fermo, significa che posso avere una vittoria forzata
            if(!check)
              //cout<<"Per la coppia "<< i <<" "<<j<< "non posso vincere"<<!check<<endl;
            board[i][j]='.';                                  //e non esplorare altro.
          }
          j++;
        }
        if(check)
          j=0;
        i++;
      }
      winning_pos.first=i-1;
      winning_pos.second=j-1;
      return !check;
    }
    ///cout<<"In here"<<endl;
    return false;
  }
}
int main(){
  ifstream myfile("find_winning_move_in.txt");
  if(myfile.is_open()){
    bool check;
    char start;
    vector< vector<char> >board(4,vector<char>(4));
    myfile>>start;
    while(start!='$'){
      for(unsigned int i=0;i<4;i++){
        for(unsigned int j=0;j<4;j++){
          myfile>>board[i][j];
        }
      }
      pair< int,int  > forced_win;
      bool s=solve(board,'x','x','o',forced_win);
      if(!s)
        cout<<"#####"<<endl;
      else
        cout<<"("<<forced_win.first<<","<<forced_win.second<<")"<<endl;
      myfile>>start;
    }
  }
  return 0;
}
