#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
static vector<bool> helper;

/*
https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&category=114&page=show_problem&problem=565
*/
//DP[i,spazio_nastro]=min (DP[i+1,spazio_nastro-tapse[i]],DP[i+1,spazio_nastro])
unsigned int minimizza_spazio(unsigned int spazio_nastro, vector<vector<int > > &dp, vector<unsigned int> tapes,unsigned int i,
  vector<bool>&posizioni){

    //cout<<"Chiamato per "<<i<<endl;
    if(spazio_nastro==0 || i>=tapes.size()){ //Se ho finito lo spazio o sono giunto alla fine
      if(spazio_nastro==0 && i<tapes.size())
        dp[i][spazio_nastro]=spazio_nastro;
      return spazio_nastro;
    }
    if(dp[i][spazio_nastro-1]!=-1){ //Se ho già risolto
    //  cout<<"Resolved"<<endl;
      return dp[i][spazio_nastro-1];
    }

    if(tapes[i]>spazio_nastro) {//Se lo eccedo
    //  posizioni[i]=false;
      dp[i][spazio_nastro-1]=minimizza_spazio(spazio_nastro,dp,tapes,i+1,posizioni);
    }
    else{

      unsigned int inserted=  minimizza_spazio(spazio_nastro-tapes[i],dp,tapes,i+1,posizioni);
      unsigned int not_inserted=  minimizza_spazio(spazio_nastro,dp,tapes,i+1,posizioni);
      dp[i][spazio_nastro-1]=min(
        inserted, //inserisco traccia
        not_inserted //non la inserisco
      );

      }

    return dp[i][spazio_nastro-1];
}
int main(){
  ifstream file("cd_tapes.txt");
  if(file.is_open()){
  unsigned int spazio_nastro,num_tapes,i;

  //cout<<dp[0][spazio_nastro-1]<<endl;
  //cout<<spazio_nastro-minimizza_spazio(spazio_nastro,dp,tapes,0)<<endl;

  while(file>>spazio_nastro){
    file>>num_tapes;
    vector< unsigned int> tapes(num_tapes,0);
    vector< bool> posizioni(num_tapes,false);
    for(i=0;i<num_tapes;i++)
      file>>tapes[i];
    vector<vector<int > > dp (num_tapes,vector<int>(spazio_nastro,-1));

    /*
    cout<< " spazio_nastro "<< spazio_nastro << " num_tapes "<< num_tapes<< " Tapes "<<endl;*/
    unsigned int spazio_occupato=minimizza_spazio(spazio_nastro,dp,tapes,0,posizioni);

    int capacit_attuale=spazio_nastro-1;

    for(unsigned int i=1;i<dp.size();i++){
      for(unsigned int j=0;j<dp[0].size();j++){
        if(dp[i][j]==spazio_occupato){
          if(j==capacit_attuale-tapes[i-1]){
            cout<<tapes[i-1]<< "  ";
            capacit_attuale=j;
          }
        }
      }


    }
    if(capacit_attuale+1-tapes[dp.size()-1]==spazio_occupato)
      cout<<tapes[dp.size()-1];

    cout<<" sums: "<<spazio_nastro-spazio_occupato<<endl;

    }
  }
  return 0;
}
