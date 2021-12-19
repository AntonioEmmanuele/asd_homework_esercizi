#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
using namespace std;
/*
  https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1071
*/
int solve(vector<vector <int> >& dp,vector <pair< int,int > > vals_weights,unsigned int idx,unsigned int idx_cap ,
  vector  <unsigned int> cap,vector<bool> available){

  //cout<<"Chiamato per oggetto"<<idx<<" con capacità" << idx_cap<<endl;

  if(idx>=dp.size() || idx_cap==0){ //Se ho finito gli oggetti o le capacità.
    if(idx_cap==0 && idx<vals_weights.size())
        dp[idx][idx_cap-1]=0;
    return 0;
  }


  if(dp[idx][idx_cap-1]!=-1){
    return dp[idx][idx_cap-1];
  }

  vector<int> candidates;
  for(unsigned int i=0;i<cap.size();i++)
    if(cap[i]>=vals_weights[idx].second&&available[i])
      candidates.push_back(i);

  if(candidates.size()==0){
    dp[idx][idx_cap-1]= solve(dp,vals_weights,idx+1,idx_cap,cap,available); //se non posso inserirlo passa al successivo
  }

  else{
    //Per ogni candidato decidiamo le possibili quantità di oggetti da portare
    vector<unsigned int> quantity(candidates.size(),0);
    for(unsigned int i=0;i<quantity.size();i++){
      quantity[i]= cap[candidates[i]]/vals_weights[idx].second;
      //cout<<"Per capacità"<< cap[candidates[i]]<< "Posso portare di peso "<<vals_weights[idx].second<<" una quantità di "<< quantity[i]<<endl;
    }

    int m=INT_MIN;
    int ins,not_ins,actual;
    for(unsigned int i=0;i<candidates.size();i++){

        cap[candidates[i]]-=quantity[i]*vals_weights[idx].second;
        available[candidates[i]]=false;
        ins=quantity[i]*vals_weights[idx].first+
                solve(dp,vals_weights,idx+1,idx_cap-quantity[i]*vals_weights[idx].second,cap,available);
        cap[candidates[i]]+=quantity[i]*vals_weights[idx].second;
        available[candidates[i]]=true;
        not_ins=  solve(dp,vals_weights,idx+1,idx_cap,cap,available);
        actual=max(ins,not_ins);
        if(actual>m)
          m=actual;

      }

      dp[idx][idx_cap-1]=m;
    }
    return dp[idx][idx_cap-1];
}

int main(){
  ifstream my_file("super_sale_in.txt");
  if(my_file.is_open()){
    unsigned int num_tests;
    my_file>>num_tests;
    while(num_tests>0){
      unsigned int num_oggetti,num_persone;
      pair<int,int> h;
      my_file>>num_oggetti;
      vector<pair<int,int> > valori_pesi;
      for(unsigned int i=0;i<num_oggetti;i++){
        my_file>>h.first; //valori
        my_file>>h.second;//pesi
        valori_pesi.push_back(h);
      }
      my_file>>num_persone;
      vector<unsigned int > cap(num_persone,0);
      unsigned int total=0;
      for(unsigned int i=0;i<num_persone;i++){
        my_file>>cap[i];
        total+=cap[i];
      }
      vector<vector< int> > dp(num_oggetti,vector<int>(total,-1));
      vector<bool> available(num_persone,true);
      cout<<solve(dp,valori_pesi,0,total,cap,available)<<endl;
      num_tests--;
    }
  }
  return 0;
}
