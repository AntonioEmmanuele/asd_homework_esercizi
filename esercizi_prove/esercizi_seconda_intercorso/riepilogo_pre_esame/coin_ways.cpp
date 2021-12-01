#include<iostream>
#include <vector>
using namespace std;

unsigned int coin_ways(vector<unsigned int> coins,unsigned int valore,vector<int> &dp){
  if(valore==0){
    dp[valore]=1;
    return dp[valore];
  }
  if(dp[valore-1]!=-1)
    return dp[valore-1];

  unsigned int actual;
  unsigned int min=INT_MAX;
  for(unsigned int i=0;i<coins.size();i++){
    if(coins[i]<valore)
      actual=1+coin_ways(coins,valore-coins[i],dp);
    else if(coins[i]==valore)
      actual=1;
    if(actual<min)
      min=actual;
  }
  dp[valore-1]=min;
  return dp[valore-1];
}

int main(){
  unsigned int coins[5]={1,5,10,25,50};
  unsigned int valore_moneta=25;
  vector< int> dp(valore_moneta,-1);
  vector<unsigned int> c(coins,coins+sizeof(coins)/sizeof(unsigned int));
  cout<<coin_ways(c,valore_moneta,dp);
  return 0;
}
