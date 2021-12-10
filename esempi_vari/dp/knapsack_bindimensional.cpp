#include<iostream>
#include<vector>
using namespace std;
//O(numeroOggetti*capacità)
int zaino(vector<int> valori,vector<int> peso,int cap, int n,vector<vector<int> > &dp ){

  if(n>=valori.size() ||cap==0) //Se ho finito gli oggetti o ho esaurito la capacitù
    return 0;
  if(dp[n][cap-1]!=-1) //L'ho già risolto
    return dp[n][cap-1];
  if(peso[n]>cap) //Se il peso eccede la capacità allora passo al successivo
      dp[n][cap-1]=zaino(valori,peso,cap,n+1,dp);
  else
    dp[n][cap-1]=max(valori[n]+zaino(valori,peso,cap-peso[n],n+1,dp), //Massimo tra l'aggiunta
                  zaino(valori, peso, cap,n+1,dp) //ed il non aggiungerlo
              );
  return dp[n][cap-1];
}

int main(){
  int v[]={60,100,120}; //Valore degli oggetti
  vector<int> valori(v,v+sizeof(v)/sizeof(int));
  int p[]={10,20,30}; //peso degli oggetti
  vector<int> peso(p,p+sizeof(p)/sizeof(int));
  int cap=50;
  int n=3;
  vector<vector<int> > dp ( valori.size(),vector<int> (cap,-1));
  cout<<"Valore 0 0"<<dp[0][49]<<endl;
  cout<<zaino(valori,peso,cap,0,dp)<<endl;

  return 0;
}
