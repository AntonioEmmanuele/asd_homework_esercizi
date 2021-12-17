#include<iostream>
#include<vector>
#include<climits>
#include <fstream>
using namespace std;
/*
https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1226
*/
//1-Numero sottoproblemi: ogni elemento della matrice
//2- Guessing :4
//3: DP[i][j]
int algo(vector<vector <int> > matrix , vector< vector<int> >& dp, int x,int y){
  /*if(x==0 && y==0){
    dp[x][y]=0;
    return dp[x][y];
  }*/
  if(dp[x][y]!=-1)
    return dp[x][y];
  else{
  //  cout<< "called for "<< matrix[x][y]<< endl;
    pair<int,int> moves[4];
    //UP
    moves[0].first=x-1;
    moves[0].second=y;
    //DOWN
    moves[1].first=x+1;
    moves[1].second=y;
    //RIGHT
    moves[2].first=x;
    moves[2].second=y+1;
    //LEFT
    moves[3].first=x;
    moves[3].second=y-1;
    int actual;
    bool entered=false;
    //int max=-1;
    for(unsigned int i=0;i<4;i++){
      if(moves[i].first>=0 &&moves[i].second>=0 && moves[i].first<matrix.size() &&moves[i].second<matrix[0].size()){
      //  cout<<moves[i].first<< " "<<moves[i].second<<endl;
        if(matrix[moves[i].first][moves[i].second]<matrix[x][y]){
        //  cout<< "In here for "<< matrix[moves[i].first][moves[i].second]<< endl;
          entered=true;
          actual=algo(matrix,dp,moves[i].first,moves[i].second)+1;
          if(actual>dp[x][y])
            dp[x][y]=actual;
        }
      }
    }
    if(!entered)
      dp[x][y]=1;
    return dp[x][y];
  }
}

//O(n^4)
int solve(vector<vector <int> > matrix , vector< vector<int> >& dp){
  int max=INT_MIN;
  for(unsigned int i=0;i<matrix.size();i++){
    for(unsigned int j=0;j<matrix[0].size();j++){
        //cout<< " Trovato percorso " << algo(matrix,dp, i,j)<<endl;
        algo(matrix,dp,i,j);
        if(dp[i][j]>max)
          max=dp[i][j];
    }
  }
  return max;
}
//unsigned int solve(vector<vector< int> >matrix, vector<int> dp)
int main(){
  ifstream myfile("longest_run_snowboard_input.txt");
  if(myfile.is_open()){
    unsigned int num_tests,row,col;
    string name;
    myfile>>num_tests;
    //cout<<num_tests<< endl;
    while(num_tests>0){
      myfile>>name;
      myfile>>row;
      myfile>>col;
      vector<vector <int> > area(row,vector<int> (col,0));
      vector<vector <int> > dp(row,vector<int> (col,-1));
      for(unsigned int i=0;i<row;i++)
        for(unsigned int j=0;j<col;j++)
          myfile>>area[i][j];
    /*  cout<< "Name"<< name<<endl;
      cout <<"Circuit"<< endl;
      for(unsigned int i=0;i<row;i++){
        for(unsigned int j=0;j<col;j++)
          cout<<area[i][j]<<" ";
        cout<<endl;
      }
      cout<<endl;*/
      //cout<<algo(area,dp,0,2)<< endl;
      //cout<< algo(area, dp,2,2)<<endl;
      cout<< name << " : "<< solve(area,dp)<<endl;
      num_tests--;
    }
  }
  return 0;
}
