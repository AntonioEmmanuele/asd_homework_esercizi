#include<iostream>
#include <vector>
#include<climits>
#include<fstream>
using namespace std;
#define NUM_PILES 4
#define BASKET_SIZE 5
/*
  https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1059
*/
//O(k),  è la dimensione del basket
vector<int> check_presence(vector<int> basket,int color,int &num){
  num=0;
  for(unsigned int i=0;i<basket.size();i++){
    if(basket[i]==color){
      num=1;
      basket.erase(basket.begin()+i);
      break;
    }
  }
  if(num==0) //se non è presente inseriscilo
    basket.push_back(color);
  return basket;
}

// m, nnumero di scelte ossia il numero di pile ed n il numero di elementi
//Tk=Tempo per operare sul basket
//(O(m*n^m*Tk))
int num_pairs(  vector< vector< vector< vector< int > > > >&dp, vector< vector <int> >piles,vector<int> basket,vector<unsigned
  int > status
){

  if(dp[status[0]][status[1]][status[2]][status[3]]!=-1)
    return dp[status[0]][status[1]][status[2]][status[3]];

  //Se ho raggiunto la massima dimensione dello zaino
  if(basket.size()==BASKET_SIZE ||
      (status[0]==piles.size() &&status[1]==piles.size() &&status[2]==piles.size() &&status[3]==piles.size())
    ){
    dp[status[0]][status[1]][status[2]][status[3]]=0;
    return dp[status[0]][status[1]][status[2]][status[3]];
  }
  int to_add;
  int actual,max=INT_MIN;
  for(unsigned int i=0;i<status.size();i++){
    if(status[i]<piles.size()){
      vector<int> n=check_presence(basket,piles[status[i]][i],to_add);
      status[i]++;
      actual=to_add+num_pairs(dp,piles,n,status);
      status[i]--;
      if(actual>max)
        max=actual;
      //else
        //cout<<actual<< " "<<max<<endl;
    }
  }
  dp[status[0]][status[1]][status[2]][status[3]]=max;
  return dp[status[0]][status[1]][status[2]][status[3]];
}

int main(){
  ifstream myfile("free_candies_in.txt");
  if(myfile.is_open()){
    unsigned int n;
    myfile>>n;
    while(n!=0){
      vector<vector<int> > piles(n,vector<int>(NUM_PILES));
      for(unsigned int i=0;i<piles.size();i++){
        for(unsigned int j=0;j<piles[0].size();j++)
          myfile>> piles[i][j];
      }
      vector< vector< vector< vector< int > > > >dp(n+1,vector<vector<vector<int> > >(n+1,vector<vector<int> >(n+1,vector<int>(n+1,-1))));
      vector<unsigned int>status (4,0);
      vector<int> basket;
      cout<<endl;
      cout<<num_pairs(dp, piles,basket,status)<<endl;
      myfile>>n;
    }
  }
  return 0;
}
