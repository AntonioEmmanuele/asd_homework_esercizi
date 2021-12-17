#include<iostream>
#include<cmath>
#include<cfloat>
#include <fstream>
#define EPS FLT_EPSILON
/*
https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1282
*/
using namespace std;
static int p,q,r,s,t,u;
static float f(float x){
  return p*exp(-1*x)+q*sin(x)+r*cos(x)+s*tan(x)+t*pow(x,2)+u;
}

//T(m)=T(m/2)+Theta(1)
//m-> numero di campioni in intervallo
//Theta(log(m/2))
float solve(float(*f)(float),float a,float b,float eps,bool& flag){
  float c=(a+b)/2;
  if(f(a)*f(b)>0){  //Se non è risolubile, ossia se non sono vere le ipotesi del teorema degli zeri
    flag=false;
    return -1;
  }
  if ((b-a)<=eps || f(c)==0){ //Se l'ho risolto o sono arrivato all'eps
      flag=true;
      return c;
  }
  else {
    //Devo continuare, nell'iterazione successiva mi devo assicurare che abbiano segno discorde.
    if((f(a)<0 && f(c)<0 )||( f(a)>= 0 && f(c)>=0)) //se hanno lo stesso segno allora procedi con l'altro intervallo
      return solve(f,c,b,eps,flag);
    else
      return solve(f,a,c,eps,flag);
  }
}

int main(){
  ifstream myfile("solve_It_in.txt");
  if(myfile.is_open()){
    bool flag=false;
    float sol;
    while(myfile>>p){
      myfile>>q;
      myfile>>r;
      myfile>>s;
      myfile>>t;
      myfile>>u;
      //cout<< p<< " "<<q<< " "<<r<< " "<<s<< " "<<t<< " "<<u<< " "<<endl;
      sol=solve(f,0,1,EPS,flag);
      if(flag)
        cout<<"Solution :"<< sol<<endl;
      else
        cout<<"No solution"<< endl;
    }
  }
  return 0;
}
