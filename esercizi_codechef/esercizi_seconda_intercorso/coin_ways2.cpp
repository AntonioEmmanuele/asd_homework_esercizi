#include<iostream>
#include<climits>
using namespace std;
//Trova il minimo numero di monete per fare il cambio
#define NUM_COINS 5
static int coins[NUM_COINS]={50,25,10,5,1};
//Theta(n^2)
int minimum_number(int num, int count){
  if(num<1) //Se sono giunto alla fine.
    return count;
  int to_ret=INT_MAX,actual;
  for(unsigned int i=0;i<NUM_COINS;i++){ //prova a rimuovere ogni moneta possibile
    if(coins[i]<=num){
      actual=minimum_number(num-coins[i],count+1);
      if(to_ret>actual)
        to_ret=actual;
    }
  }
  return to_ret;
}

int main(){
  cout<<minimum_number(11,0)<<endl; //2
  cout<<minimum_number(16,0)<<endl; //3
  cout<<minimum_number(26,0)<<endl; //2
  return 0;
}
