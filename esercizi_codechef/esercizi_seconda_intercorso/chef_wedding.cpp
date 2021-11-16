#include <iostream>
#include <vector>
#include <map>
/*
https://www.codechef.com/problems/CHEFWED
*/
using namespace std;
//O(n)*O(n-i), dovrebbe essere Theta(n), alla finne ti trovi sempre a ciclare al max su n i=n-1
void calc_ineff(vector<unsigned int> guests,unsigned int& idx,unsigned int& actual_ineff,const unsigned int table_price){
    map<unsigned int,unsigned int> table_occurrences;
    if(actual_ineff==0)
        actual_ineff=table_price;
    unsigned int ineff_hold=actual_ineff,ineff_split=actual_ineff,original=actual_ineff;
    while (idx<guests.size()){
        table_occurrences[guests[idx]]++;
        if (table_occurrences[guests[idx]]<=1) //valore di default //O(1), non ci sono ripetizioni
              idx++;
        else{
            ineff_hold=original+table_occurrences[guests[idx]];
            ineff_split+=2*table_price;
            //Se mi conviene momentaneamente mantenere allora vai solo ad incrementare il valore dell'inefficienza
            if(ineff_hold< ineff_split){
                actual_ineff=ineff_hold;
                idx++;
            }
            else {
                actual_ineff=ineff_split;
                idx++;
                break;
            }
           // idx++;
        }

         
    }
    
    if(idx<guests.size())
        calc_ineff(guests,idx,actual_ineff,table_price);
}
int main() {
    unsigned int tests,guests_num,table_price,i;
    //ineff_hold è l'inefficienza che si ha spezzando il tavolo,mentre inefficienza
    
    cin>>tests;
    while(tests>0){
        cin>>guests_num;
        cin>>table_price;
        unsigned int actual_ineff=0;
        vector<unsigned int> guests(guests_num,0);
        //andiamo con un approccio bottom up
        //Sottoproblemi: numero di persone* tempo sottoproblema O(1)
        //Indovinare ultima persona del tavolo in base lal calcolo
        //delle inefficienze, possibile anche vedere la complessità totale come la somma
        //delle complessità di ogni singolo tavolo che è Theta(n)
        //FUNZIONA PERCHE' OTTIMO LOCALE (soluzione migliore per un tavolo) unito ad altri ottimi
        //DA risultato totale ottimo (sottostruttura ottima del problema)
        for(i=0;i<guests_num;i++)
           cin>>guests[i];
        i=0;
        calc_ineff(guests,i,actual_ineff,table_price);
        cout<< actual_ineff<<endl;
        tests--;
        
    }
    return 0;
}

