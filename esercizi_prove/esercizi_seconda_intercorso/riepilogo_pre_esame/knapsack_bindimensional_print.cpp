#include<iostream>
#include<vector>
#include<climits>
using namespace std;
//O(numeroOggetti*capacità)
int zaino(vector<int> valori,vector<int> peso,int cap, int n,vector<vector<int> > &dp ){

    if(n>=valori.size() ||cap==0){ //Se ho finito gli oggetti o ho esaurito la capacitù
        if(cap==0&& n<valori.size())
            dp[n][cap-1]=0;
        return 0;
    }
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
    int p[]={1,2,3}; //peso degli oggetti
    vector<int> peso(p,p+sizeof(p)/sizeof(int));
    int cap=5;
    int n=3;
    vector<vector<int> > dp ( valori.size(),vector<int> (cap,-1));
    //cout<<"Valore 0 0"<<dp[0][49]<<endl;
    int actual= zaino(valori,peso,cap,0,dp);
    cout<<actual<<endl;
    int min=INT_MAX;
    int col=cap-1;
    for(unsigned int i=0;i<dp.size();i++){
        for(unsigned int j=0;j<dp[0].size();j++){
            cout<<dp[i][j]<<" ";
            if(dp[i][j]<min && dp[i][j]>=0 )
               min=dp[i][j];
            
        }
        cout<<endl;
        if(min==actual-v[i]){
            actual=min;
            cout<<v[i]<<endl;
        }

    }


  return 0;
}
