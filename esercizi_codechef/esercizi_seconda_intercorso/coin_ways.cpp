#include<iostream>
/*
 Suppose there are 5 types of coins: 50-cent, 25-cent, 10-cent, 5-cent, and 1-cent. We want to make changes with these coins for a given amount of money.
 For example, if we have 11 cents, then we can make changes with one 10-cent coin and one 1-cent coin, two 5-cent coins and one 1-cent coin, one 5-cent coin and six 1-cent coins, or eleven 1-cent coins. So there are four ways of making changes for 11 cents with the above coins. Note that we count that there is one way of making change for zero cent.
 Write a program to find the total number of different ways of making changes for any amount of money in cents. Your program should be able to handle up to 7489 cents.
 Input
 The input file contains any number of lines, each one consisting of a number for the amount of money in cents.
 Output
 For each input line, output a line containing the number of different ways of making changes with the above 5 types of coins.
 Sample Input
 11 26
 Sample Output
 4 13
 */
using namespace std;
static int coins[5]={50,25,10,5,1};
//DP(n,idx)=DP(n-array[idx],idx)+DP(n,idx+1)
//Theta(n*5)
int num_coins(int n,int idx){
  if(n<=1) //altrimenti
    return 1;
  if(idx>=5) //Se ho sforato con l'indice
    return 0;
  if(coins[idx]>n) //Se sono negativo incrementa l'indice
    return num_coins(n,idx+1);
  return num_coins(n-coins[idx],idx)+num_coins(n,idx+1);
}
int main(){
  cout<<num_coins(11,0)<<endl;
  cout<<num_coins(26,0)<<endl;
  return 0;
}
