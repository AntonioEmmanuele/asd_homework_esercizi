#include <iostream>
#include<vector>
using namespace std;
/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
*/
//O(n^2)
int max_profict(vector< int> costs,int bought,unsigned int idx,unsigned int transaction_number){
    if(idx>=costs.size() || transaction_number==2) //Se sono arrivato alla fine o ho esaurito il numero di transazioni
      return 0;
    // se bought <0 allora non ho comprato niente, la scelta coincide tra il comprare ed il non comprare.
    if(bought<0){
      //Non compro nulla
      return max(max_profict(costs,costs[idx],idx+1,transaction_number),max_profict(costs,-1,idx+1,transaction_number));
    }
    //Se bought>=0 allora ho comprato, devo scegliere se vendere adesso  oppure ritornare dopo
    else{
      //La prima scelta consiste nel vendere ora, quindi devo calcolare il profitto e procedere un unn bought negativo
      //Oppure tenere attiva l'attuale transazione e procedere
      return max((costs[idx]-bought)+max_profict(costs,-1,idx+1,transaction_number+1),max_profict(costs,bought,idx+1,transaction_number));
    }
}

int main(){
  int h[6]={3,3,5,0,0,3};
  int h2[5]={1,2,3,4,5};
  int h3[5]={7,6,4,3,1};
  int h4[1]={1};
  vector<int> v(h,h+sizeof(h)/sizeof(int));
  vector<int> v2(h2,h2+sizeof(h2)/sizeof(int));
  vector<int> v3(h3,h3+sizeof(h3)/sizeof(int));
  vector<int> v4(h4,h4+sizeof(h4)/sizeof(int));
  cout<< max_profict(v,-1,0,0)<<endl;
  cout<< max_profict(v2,-1,0,0)<<endl;
  cout<< max_profict(v3,-1,0,0)<<endl;
  cout<< max_profict(v4,-1,0,0)<<endl;
  return 0;
}
