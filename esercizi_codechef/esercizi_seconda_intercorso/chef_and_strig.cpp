#include <iostream>
#include <string>
using namespace std;
/*
https://www.codechef.com/problems/CHRL2
*/
//1- sottoproblemi sono le lettere della parola
//2- guessing : individuare se ricominciare o meno la selezione della parola CHEF
//3- scelta(i)+algo(i+1)=algo(i)
//4- N*Theta(1)=Theta(N) , ha ordine topologico
//theta(n)
int main() {
    string input;
    string to_rec="CHEF";
    unsigned int toRec_idx=0,i,max_move=0;
    cin>>input;
    
    for(i=0;i<input.size();i++){
        if (input[i]==to_rec[toRec_idx]){
            toRec_idx++;
            //Se sono arrivato alla fine.
            //No terminatore
            if(toRec_idx>to_rec.size()-1){
                toRec_idx=0;
                max_move++;
            }
        }
       
    }
    cout<<max_move<<endl;
	return 0;
}
