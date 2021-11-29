#include <iostream>
#include<vector>
#include <climits>
using namespace std;
#define INF INT_MAX
unsigned int num_jumps(vector<unsigned int> vec,unsigned int pos){
  //Se sono arrivato alla fine termina
  if(pos>=vec.size()-1)
    return 0;
  if(vec[pos]==0)
    return INF;
  unsigned int min=INF,j,actual_jumps;
  //Per ogni possibile salto
  for(j=1;j<=vec[pos];j++){
    //Calcola i salti che ci vogliono se faccio tot salto
    actual_jumps=num_jumps(vec,pos+j);
    //Trova il minimo
    if(actual_jumps<min)
      min=actual_jumps;
  }

  //ritorna il salto attuale + minimo
  return 1+min;
}
int main(){

  unsigned int array[]={2,3,1,1,4};
  //vector<unsigned int> arr(array,sizeof());
  vector<unsigned int> arr(array,array+ sizeof(array)/sizeof(unsigned int));
  cout<<num_jumps(arr,0)<<endl;
  unsigned int array2[]={2,3,1,1,4};
  //vector<unsigned int> arr(array,sizeof());
  vector<unsigned int> arr2(array,array+ sizeof(array)/sizeof(unsigned int));
  cout<<num_jumps(arr2,0)<<endl;
  return 0;
}
