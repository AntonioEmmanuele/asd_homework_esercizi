#include<iostream>
#include<vector>
#include<climits>
using namespace std;
/*
INPUT
30
3
2 20 25
10
4
4 5 7 8
100
3
25 50 75
10
3
2 4 7
0
OUT
60
22
200
20
*/
#define INF INT_MAX
//dp[i,j]=min k (dimensione_trave+dp[i,k-1]+dp[k+1,j])
unsigned int min_cost(vector<vector<int > > &dp, unsigned int i, unsigned int j,vector<bool>cuts,unsigned int dimensione_trave){ //nella versione precedente mi portavo appresso la dimensione, qui no.
  if(dp[i][j]!=-1)
    return dp[i][j];
  unsigned int cost=0;
  dp[i][j]=INF;
  for(unsigned int k=i;k<=j;k++){
    if(cuts[k]){
      cost=(dimensione_trave)+min_cost(dp,i,k-1,cuts,k-i+1)+min_cost(dp,k+1,j,cuts,j-k);
      if(cost<dp[i][j])
        dp[i][j]=cost;
    }
  }
  if(dp[i][j]==INF)
    dp[i][j]=0;
  //cout<<dp[i][j]<<" Per indici " <<i <<" "<<j <<endl;
  //if(i==0&&j==cuts.size()) //Alla fine aggiungo 1
  //  dp[i][j]+=1;
  return dp[i][j];
}

int main(){
  unsigned int len;
  cin>>len;
  unsigned int helper,num_cuts;
  while(len!=0){
    vector<bool> cuts(len,false);
    cin>>num_cuts;
    for(unsigned int i=0;i<num_cuts;i++){
      cin>>helper;
      cuts[helper-1]=true;
    }
    vector<vector<int> > dp(len,vector<int>(len,-1));
    cout<<min_cost(dp,0,len-1,cuts,len)<<endl;
    cin>>len;
  }
  return 0;
}
