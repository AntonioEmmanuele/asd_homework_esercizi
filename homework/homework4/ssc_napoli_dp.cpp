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
void insert(unsigned int gruppo, vector<unsigned int> gradinate){
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
// max_gruppi[gruppi, gradinate,indice_gruppi]
//    if indice_gruppi> len[gruppi] or isEmpty[gradinate]
//      return 0
//    if(!canInsert[gruppi[indice_gruppi],gradinate])
//       to_ret<-max_gruppi[gruppi,gradinate,indice_gruppi+1]
//    else
//      not_ins <- max[gruppi,gradinate,indice_gruppi+1]
//      insert[gruppi[indice_gruppi],gradinate]
//      ins<- gruppi[indice_gruppi]+max_gruppi[gruppi,gradinate, indice_gruppi+1]
//      to_ret<-max(ins,not_ins)
//    return to_ret

//Theta(n*Gradinate*Gradini) n-> numero di gruppi
int max_gruppi(vector<unsigned int> gruppi,vector<unsigned int> gradinate, int indice_gruppi ){
  unsigned int to_ret;
  if(indice_gruppi>=gruppi.size() ||isEmpty(gradinate)) //Se ho finito gli oggetti o ho esaurito la capacit+
    return 0;
  if(!canInsert(gruppi[indice_gruppi],gradinate)) //Se il peso eccede la capacità allora passo al successivo
      to_ret=max_gruppi(gruppi,gradinate,indice_gruppi+1);
  else{
        unsigned int not_ins=max_gruppi(gruppi,gradinate,indice_gruppi+1);
        insert(gruppi[indice_gruppi],gradinate);
        unsigned int ins=gruppi[indice_gruppi]+max_gruppi(gruppi,gradinate,indice_gruppi+1);
        to_ret=max(ins,not_ins);
  }
  return to_ret;
}

int main(){
  int temp[4] = {19,7,8,4};
  int g[3]={10,10,10};
  vector<unsigned int> gradinate(g,g+sizeof(g)/sizeof(int));
  vector<unsigned int> gruppi(temp,temp +sizeof(temp)/sizeof(unsigned int));
  //max_posti=gradinate[0];
  //vector < vector <vec > >  dp(gruppi.size(),vector<vec>(gradinate.size(),vec(gradinate[0],-1)));
  cout<<max_gruppi(gruppi,gradinate,0)<<endl;

  return 0;
}
