#include<iostream>
#include<vector>
using namespace std;
/*
  canInsert[gruppo,gradinate]
    for i <- 1..len[gradinate]
         if gruppo<=gradinate[i]
            return true
    return false
*/
//O(len(gradinate))
bool canInsert (unsigned int gruppo, vector<unsigned int> gradinate) {
	for (unsigned int i=0;i<gradinate.size();i++) {
		if (gruppo <= gradinate[i])
			return true; //Lo possiamo inserire
	}
	return false;
}

/*

insert[gruppo,gradinate]
  for i <- 1..len[gradinate]
       if gruppo<=gradinate[i]
          gradinate[i]<- gradinate[i]-gruppo
          return

*/
//O(len(gradinate))
void insert(unsigned int gruppo, vector<unsigned int>& gradinate){
  //vector< unsigned int> to_ret(gradinate.begin(),gradinate.end()
	for(unsigned int i=0;i<gradinate.size();i++){
    if(gruppo<=gradinate[i]){
      gradinate[i]-=gruppo;
      return;
    }
  }
}

/*
  canInsert[gruppo,gradinate]
    for i <- 1..len[gradinate]
         if gradinate[i]!=0
            return false
    return true
*/
//O(len(gradinate))
bool isEmpty(vector<unsigned int > gradinate){
  for (unsigned int i=0;i<gradinate.size();i++) {
    if ( gradinate[i]!=0)
      return false; //Lo possiamo inserire
  }
  return true;
}

//DP[i,stato_gradinate]= DP[i+1,stato_gradinate] (qualora gruppi[i] non possa essere inserito)
//DP[i,stato_gradinate]=max(gruppi[i]+DP[i+1,insert[stato_gradinate]],DP[i+1,stato_gradinate])

//NB : Sto massimizzanndo le persone da fare entrare, per questo sommo gruppi[indice_gruppi],altrimenti sommerei 1
// max_gruppi[gruppi, gradinate,dp,indice_gruppi,j]
//    if indice_gruppi> len[gruppi] or isEmpty[gradinate]
//      return 0
//    if dp[indice_gruppi][j]!=-1 //problema già risolto
//        return dp[indice_gruppi][j]
//    if !canInsert[gruppi[indice_gruppi],gradinate]
//      dp[indice_gruppi][j]<-max_gruppi[gruppi,gradinate,indice_gruppi+1,j]
//    else
//      not_ins <- max[gruppi,gradinate,indice_gruppi+1,j]
//      clone[helper,gradinate]
//      insert[gruppi[indice_gruppi],helper]
//      ins<- gruppi[indice_gruppi]+max_gruppi[gruppi,helper, indice_gruppi+1,j-gruppi[indice_gruppi]]
//      dp[indice_gruppi][j]<-max(ins,not_ins)
//    return dp[indice_gruppi][j]

//O(n*Gradinate*Gradini) n-> numero di gruppi
int max_gruppi(vector<unsigned int> gruppi,vector<unsigned int> &gradinate,
 								vector <vector <int> > &dp,int indice_gruppi, unsigned int j){ //j indica la gradinata ed z la capacità residua della gradinata

	//cout<<"Called for j "<< j<< "  z "<< z<< endl;
  if(indice_gruppi>=gruppi.size() ||isEmpty(gradinate)) //Se ho finito gli oggetti o ho esaurito la capacit+
    return 0;
  if(dp[indice_gruppi][j-1]!=-1) //Se il problema è già stato risolto
    return dp[indice_gruppi][j-1];
  if(!canInsert(gruppi[indice_gruppi],gradinate)) //Se il peso eccede la capacità allora passo al successivo
      dp[indice_gruppi][j-1]=max_gruppi(gruppi,gradinate,dp,indice_gruppi+1,j);
      //to_ret=max_gruppi(gruppi,gradinate,indice_gruppi+1,dp,j,z);
  else{
			//	unsigned int new_j,new_z;
        unsigned int not_ins=max_gruppi(gruppi,gradinate,dp,indice_gruppi+1,j);
        vector< unsigned int >helper(gradinate.begin(),gradinate.end() ); //Bisogno di un vettore di appoggio
        insert(gruppi[indice_gruppi],helper); //Quando chiamo questa funzione sono certo che posso inserire.
        unsigned int ins=gruppi[indice_gruppi]+max_gruppi(gruppi,helper,dp,indice_gruppi+1,j-gruppi[indice_gruppi]);
        dp[indice_gruppi][j-1]=max(ins,not_ins);

  }
  return dp[indice_gruppi][j-1];
}

int main(){

  int temp[5] = {5,7,8,4,10}; //27
  int g[3]={10,10,10};
  vector<unsigned int> gradinate(g,g+sizeof(g)/sizeof(int));
  vector<unsigned int> gruppi(temp,temp +sizeof(temp)/sizeof(unsigned int));
  vector< vector <int > > dp(gruppi.size(),vector< int > (gradinate.size()*gradinate[0],-1));
  cout<<max_gruppi(gruppi,gradinate,dp,0,gradinate[0]*gradinate.size())<<endl;
  //DP resistuisce 29, greedy 9+(8+2)+(7+2)=28
	int temp2[13] = {7,8,9,2,2,2,2,2,2,2,2,2,2}; //Inserisce
	int g2[3]={10,10,10};
	vector<unsigned int> gradinate2(g2,g2+sizeof(g2)/sizeof(int));
	vector<unsigned int> gruppi2(temp2,temp2 +sizeof(temp2)/sizeof(unsigned int));

  vector< vector <int > > dp2(gruppi2.size(),vector< int > (gradinate2.size()*gradinate2[0],-1));
  cout<<max_gruppi(gruppi2,gradinate2,dp2,0,gradinate2[0]*gradinate2.size())<<endl;

  vector< unsigned int> gruppi3(28,1); //Risultato 28
  int g3[3]={10,10,10};
  vector<unsigned int> gradinate3(g3,g3+sizeof(g3)/sizeof(int));
  vector< vector <int > > dp3(gruppi3.size(),vector< int > (gradinate3.size()*gradinate3[0],-1));
  cout<<max_gruppi(gruppi3,gradinate3,dp3,0,gradinate3[0]*gradinate3.size())<<endl;

  return 0;
}
