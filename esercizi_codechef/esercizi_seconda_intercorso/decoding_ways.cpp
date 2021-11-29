#include<iostream>
#include<cmath>
/*
 https://leetcode.com/problems/decode-ways/
 */
using namespace std;
unsigned int decondig_ways(const unsigned int num){
  //Calcola il numero di num_of_digit
  unsigned int num_of_digit=0,helper=num,num_of_ways=0,i,digit,digit_next;
  while(helper!=0){
    helper/=10;
    num_of_digit++;
  }
  //cout<<"num"<<num_of_digit;
  for(i=0;i<num_of_digit;i++)
  {
    digit=(unsigned int)(num/(pow(10,i)))%10;
    if(digit!=0 )
    {
      //Se è il primo allora inizializza
      if(num_of_ways==0 )
        num_of_ways=1;
      //controlla successivo
      if(i+1<num_of_digit)
      {
        digit_next=(unsigned int)(num/(pow(10,i+1)))%10;
        if(digit_next!=0 ){
          if(digit_next<2)
            num_of_ways+=1;
          else if (digit_next==2){
            if(digit<=6)
              num_of_ways+=1;
          }

        }
      }
    }
  }
  return num_of_ways;
}

int main(){
  unsigned int tests,num;
  cin>>tests;
  while(tests>0){
    cin>>num;
    cout<<decondig_ways(num)<<endl;
    tests--;
  }
  return 0;
}
