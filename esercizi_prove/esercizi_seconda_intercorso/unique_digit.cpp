#include<iostream>
#include<cmath>
using namespace std;
/*
https://leetcode.com/problems/count-numbers-with-unique-digits/
*/
//O(n)
//Dp[i]=(Dp[i-1]*(11-i)) //possibili scelte sapendo che tot sono state prese
unsigned int unique_digit(int n){
  unsigned int dp[n+1];
  unsigned int sum=0;
  dp[0]=1;
  dp[1]=9;
  for(int i=2;i<n+1;i++)
    dp[i]=dp[i-1]*(11-i);
  for(int i=0;i<n+1;i++)
    sum+=dp[i];
  return sum;
}
int main(){
  cout<<unique_digit(0)<<endl;
  cout<<unique_digit(1)<<endl;
  cout<<unique_digit(2)<<endl;
  cout<<unique_digit(3)<<endl;
  return 0;
}
