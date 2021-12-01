#include<iostream>
#include<vector>
#include<climits>
using namespace std;

unsigned int mn(unsigned int a, unsigned int b, unsigned int c ){
  if(a>b)
    return (b>c)?c:b;
  else
    return (a>c)?c:a;
}
//Exercise taken from: https://www.geeksforgeeks.org/min-cost-path-dp-6/?ref=lbp
/*
Given a cost matrix cost[][] and a position (m, n)
in cost[][], write a function that returns cost of minimum cost path to reach (m, n)
from (0, 0). Each cell of the matrix represents a cost to traverse through that cell.
The total cost of a path to reach (m, n) is the sum of all the costs on that path
 (including both source and destination).
  You can only traverse down, right and diagonally lower cells from a given cell, i.e.,
  from a given cell (i, j), cells (i+1, j), (i, j+1), and (i+1, j+1) can be traversed. You may assume
  that all costs are positive integers.
  */
//DP[i,j]=cost[i,j]+min(DP[i-1][j]+DP[i][j-1]+DP[i-1][j-1])
unsigned int min_cost_path(vector< vector<unsigned int> > costs,
                          vector< vector<int> > dp,unsigned int i,unsigned int j){
  if(i==0 && j== 0){ //Sono giunto a destinazione
    dp[0][0]=costs[0][0];
    return costs[i][j]; //Ritorna il costo di 0 0
  }
  if(dp[i][j]!=-1) //Ho già risolto il problema
    return dp[i][j];

  int next_x=(int)i-1;
  int next_y=(int)j-1;

  if(next_x>=0 && next_y>=0) // Se entrambi sono minori
    dp[i][j]= mn(
        min_cost_path(costs,dp,i,next_y), //mi muovo lungo y
        min_cost_path(costs,dp,next_x,j), //mi muovo lungo x
        min_cost_path(costs,dp,next_x,next_y))//mi muovo diagonalmente
        +costs[i][j];

  else if( next_x<0 &&next_y<0) //Infinito
      return INT_MAX;

  else if( next_x>=0  && next_y<0)
    dp[i][j]=  min_cost_path(costs,dp,next_x,j)+costs[i][j]; //mi muovo lungo x

  else if( next_x<0  && next_y>=0)
      dp[i][j]=  min_cost_path(costs,dp,i,next_y)+costs[i][j]; //mi muovo lungo y

  //cout<<"For i "<< i <<"  j "<< j <<" cost "<<dp[i][j]<<endl;
  return dp[i][j];

}
int main(){
  unsigned int h[]={1,2,3};
  unsigned int h1[]={4,8,2};
  unsigned int h2[]={1,5,3};
  vector <vector<unsigned int> >costs;
  costs.push_back(vector<unsigned int> (h,h+sizeof(h)/sizeof(unsigned int)));
  costs.push_back(vector<unsigned int> (h1,h1+sizeof(h1)/sizeof(unsigned int)));
  costs.push_back(vector<unsigned int> (h2,h2+sizeof(h2)/sizeof(unsigned int)));
  /*for(unsigned int i=0;i<costs.size();i++){
    for(unsigned int j=0;j<costs[0].size();j++)
      cout<<costs[i][j]<<" ";
    cout<<endl;
  }
  cout<<endl;*/
  vector<vector<int> > dp(costs.size(),vector<int>(costs[0].size(),-1)); //mi aspetto 8
  cout<<min_cost_path(costs,dp,2,2)<<endl;
  return 0;
}
