#include <iostream>
#include<vector>
#include<cmath>
using namespace std;
/*
https://leetcode.com/problems/remove-boxes/
*/
//DP[i,j]=max k,n (DP(i:k U n :j)+(n-k)*(n-k))
//O(n^2), forse n^3 ma si può fare annche senza array di appoggio, più scocciante

unsigned int max_boxes(vector<unsigned int> boxes){
  //cout<<"Chiamato con size"<<boxes.size()<<endl;
  unsigned int i=0,count=0,starting=0,ending=0;
  int to_ret=-1;
  /*
  if(boxes.size()==0)
    return 0;*/
  while(i<boxes.size()){
    starting=i;
    bool check=false;
    while (i+1<boxes.size() &&! check  ){ //prendi il vettore rimosso
      if(boxes[i]==boxes[i+1])
          i+=1;
      else
        check=true;
    }
    ending=i;
    //cout<< "Starting"<< starting<< " ending "<<ending<<endl;
    vector<unsigned int>attempt(boxes.begin(),boxes.end());
    if(ending!=starting)
      attempt.erase(attempt.begin()+starting,attempt.begin()+ending+1);
    else
      attempt.erase(attempt.begin()+starting);
    //if(starting!=ending)
/*
      for(unsigned int j=0;j<attempt.size();j++)
        cout<<attempt[j]<<" ";
    cout<<endl;
*/
    count=pow((ending-starting+1),2)+max_boxes(attempt);
  //  cout<<"Profitto"<<pow((ending-starting+1),2)<<endl;
    if((int)count>to_ret)
      to_ret=(int)count;
    i++;
  }
  if(i==0)
    return 0;
  return (unsigned int) to_ret;
}

int main(){

  unsigned int h[]={1,3,2,2,2,3,4,3,1};
  vector<unsigned int>v(h,h+sizeof(h)/sizeof(unsigned int));
  cout<<max_boxes(v)<<endl;
  unsigned int h1[]={1,1,1};
  vector<unsigned int>v1(h1,h1+sizeof(h1)/sizeof(unsigned int));
  cout<<max_boxes(v1)<<endl;
  unsigned int h2[]={1};
  vector<unsigned int>v2(h2,h2+sizeof(h2)/sizeof(unsigned int));
  cout<<max_boxes(v2)<<endl;
  return 0;
}
