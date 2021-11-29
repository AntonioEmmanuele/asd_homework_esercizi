#include<iostream>
#include<vector>
using namespace std;

//Theta(1)
int calc_earning(vector<int> v, unsigned int idx){
  unsigned int left_earing;
  unsigned int right_earing;

  if((int)idx-(int)1<0)
    left_earing=1;
  else
    left_earing=v[idx-1];
  if(idx+1>=v.size())
    right_earing=1;
  else
    right_earing=v[idx+1];

  return right_earing*v[idx]*left_earing;

}
//theta(n^2)
//Ricorrenfa : for i <-1 to N DP[i:j]=max k(DP[i:k-1 U k+1 :j ])
int bursting_ballons(vector<int> v){
  if(v.size()==1) //Il guadagno di 0 è l'elemento stesso
    return v[0];
    //altrimenti
    int max,actual,idx;
    for(unsigned int i=0;i<v.size();i++){ //Scorri tutto l'array e trova l'indice che mi massimizza il guadagno
      vector<int> attempt(v.begin(),v.end());
      attempt.erase(attempt.begin()+i);
      actual=calc_earning(v,i)+bursting_ballons(attempt);
      if(actual>max){
        idx=i;
        max=actual;
      }
    }
    return max;
}

int main(){

  int h[2]={1,5};
  vector<int> v(h,h+sizeof(h)/sizeof(int));
  cout<<bursting_ballons(v)<<endl;
  int h2[4]={3,1,5,8};
  vector<int> v2(h2,h2+sizeof(h2)/sizeof(int));
  cout<<bursting_ballons(v2)<<endl;
  return 0;
}
