#include<iostream>
#include<vector>

using namespace std;
int max_prod(vector <int> vec){
    int curr_max=vec[0];
    int max_prod=curr_max;
    unsigned int i;
    for(i=1;i<vec.size();i++){
      curr_max*=vec[i];
      curr_max=max(vec[i],curr_max);
      max_prod=max(curr_max,max_prod);
    }
    return max_prod;
}

int main(){
  int h[4]={2,3,-2,4};
  vector <int> vec(h,h+sizeof(h)/sizeof(int));
  cout<<max_prod(vec)<<endl;
  int h2[3]={-2,0,-1};
  vector <int> vec2(h2,h2+sizeof(h2)/sizeof(int));
  cout<<max_prod(vec2)<<endl;
  return 0;
}
