#include <iostream>
#include<vector>
#include<cmath>
using namespace std;
/*
https://www.codechef.com/problems/FROGV
*/
//2-Scelta: Scegliere chi raggiunntere. Theta(n)
//1-Il sottoproblema è compiere unna scelta " Per le rimanenti rane" (ossia quelle escludendo la rana originale) Theta(n)
//3-Equazione = Raggiungibile(i,v)=min j{(distance(j,v)+Raggiungibile(j,v)}
//4- La scelta delle successive rane da raggiure non necessita della scelta pendente, abbiamo un ordine topologico.
// Tempo theta(n)*theta(n)=theta(n^2)
bool is_frog_reachable(vector<unsigned int> frogs, unsigned int frog1,unsigned int frog2,unsigned int max_distance){
    //Trovo la più vicina alla frog da raggiungere
    
    //idx inizia da 0 perchè devo vedere tutte le rane, anche quelle che vengono prima di me
    unsigned int len=frogs.size(),rescaled_frog1=frog1-1,rescaled_frog2=frog2-1,idx=0;
    unsigned int max_idx; //Indice della rana più vicina
    vector<unsigned int> reachable;
    bool found=false;
    while(!found && idx<len){
        if(abs((float)frogs[idx]-(float)frogs[rescaled_frog1])<=max_distance &&idx != rescaled_frog1){
            if(idx==rescaled_frog2)
                found=true;
            else
                reachable.push_back(idx);
        }
        idx++;
    }
    if(found)
        return true;
    else if(! found){
        //Se non l'ho trovato allora devo determinare il massimo tra quelli che posso raggiungere
        //se il massimo è più piccolo di me significa che mi sto allontanando, il problema non è risolvibile.
        //altrimenti mi avvicino
        /*  Non necessario dal momento che prendiamo il valore assoluto della differenza*/
        /*if(reachable.size()==0){
            cout<<"For frog"<< frogs[rescaled_frog1]<<endl;
            return false;
        }*/
        
        max_idx=reachable[0];
        for(idx=1;idx<reachable.size();idx++)
            if(frogs[reachable[idx]]>frogs[max_idx])
                max_idx=reachable[idx];
        //Se mi allontano ritorna false
        if(frogs[max_idx]<=frogs[rescaled_frog1]){
            return false;
        }
        //Altrimenti provo a raggiungerlo dalla nuova rana
        else
            return is_frog_reachable(frogs,max_idx+1,frog2,max_distance);
    }
}
int main() {
    unsigned int frogs_len,max_distance,num_of_pairs,i;
    cin>> frogs_len;
    cin>>max_distance;
    cin>>num_of_pairs;
    vector<unsigned int>frogs(frogs_len,0);
    vector<unsigned int> pairs(num_of_pairs*2,0);
    for( i=0;i<frogs_len;i++)
        cin>>frogs[i];
    for(i=0;i<num_of_pairs*2;i++)
        cin>>pairs[i];
    for (i=0;i<num_of_pairs*2;i+=2){
        //cout<<""<<i<<endl;
        //cout << pairs[i]<< "  "<<pairs[i+1]<< endl;
        if(is_frog_reachable(frogs,pairs[i],pairs[i+1],max_distance))
            cout<<"yes"<<endl;
        else
            cout<<"no"<<endl;
    }
    
	return 0;
}
