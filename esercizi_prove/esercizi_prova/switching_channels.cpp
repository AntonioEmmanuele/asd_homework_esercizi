#include <iostream>
#include <vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<climits>
using namespace std;
/*
https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=170
*/
//O(n!*n*m), va bene fintanto che posso fare così
void algo(vector < int> p, vector<pair<int, int> >s,int &out_error, int&out_value,vector<int> &out_permutation){

  auto crt=[](pair<unsigned int, unsigned int>  s,pair<unsigned int, unsigned int>  s1){return s.second<s1.second;};
  sort(s.begin(),s.end(),crt); //mlogm
  sort(p.begin(),p.end());
  vector <int >cumulative_sums(p.size(),0);
  int actual_error,error,value;
  out_value=INT_MIN;
  out_error=INT_MAX;

  do{

    error=0;
    value=0;
    actual_error=0;
    //calcola i tempi di fine
    cumulative_sums[0]=p[0];
    for(unsigned int i=1;i<cumulative_sums.size();i++) //O(n)
        cumulative_sums[i]=p[i]+cumulative_sums[i-1];

    //per tutti gli elementi di s vado a controllare i valori e la fine
    //trova il più vicino
    for(unsigned int j=0;j<s.size();j++){
      actual_error=INT_MAX;
      for(unsigned int i=0;i<p.size();i++)
        if(abs((float)cumulative_sums[i]-(float)s[j].second)<actual_error)
          actual_error=abs((float)cumulative_sums[i]-(float)s[j].second);

      if(actual_error==0)
        value+=s[j].first;
      error+=actual_error; //Gli aggiungo l'errore
    }

    //controlla ed aggiorna
    if(value>out_value){
      out_value=value;
      out_error=error;
      out_permutation=vector<int>(p);
    }
    else if(value==out_value){
      if(error<out_error){
        out_error=error;
        out_permutation=vector<int>(p);
      }
    }
  }while(next_permutation(p.begin(),p.begin()+p.size())) ;//n!
}
int main(){
  ifstream my_file("switching_channels_input.txt");
  int error, value;
  if(my_file.is_open()){
    unsigned int p_size, s_size;
    while(my_file>>p_size){ //NELL?INPUT HO SCAMBIATO 0 CON EOF
        vector< int> p(p_size,0);
        pair< int,  int> h;
        for(unsigned int i=0;i<p.size();i++)
          my_file>>p[i];
        my_file>>s_size;
        vector<pair< int,  int> > s;
        for(unsigned int i=0;i<s_size;i++){
          my_file>>h.first;
          my_file>>h.second;
          s.push_back(h);
        }
        vector<int> out;
        algo(p,s,error,value,out);
          for(unsigned int i=0;i<out.size();i++)
          cout<<out[i]<< " ";
          cout<<endl;
        //backtrack(p,s,0,vector<bool> (p_size,true),vector<unsigned int> (),0,0,0);
        cout<< "Errore è"<<error<<endl;
        cout<< "value is"<< value<<endl;
        //actual_value=INT_MIN;

    }
  }
  return 0;
}
