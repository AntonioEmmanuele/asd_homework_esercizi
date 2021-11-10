#include <iostream>
#include <vector>
#include <map>
//#include<vector>
using namespace std;
//O(L)
unsigned int num_of_seq(map<unsigned int,unsigned int>colors_and_list,vector<unsigned int> list){
    unsigned int counter=1;
   // cout <<" LA lista è"<<endl;
/*    for(unsigned int i=0;i<list.size();i++)
        cout<<list[i]<<" ";*/
    for(unsigned int i=0;i<list.size()-1;i++){
        //Se non sono nella stessa lista incrementa il contatore
        if(colors_and_list[list[i]]!=colors_and_list[list[i+1]])
            counter++;
    }
   // cout<< endl;
    return counter;
}
/*
    Durante uno scontro con il Joker, gli occhi di Batman perdono la capacità di distinguere tra alcune coppie  di  colori.
    Ogni  colore  ha  un  ID  intero,  da  1  a  N.  Ci  sono  M  liste;  ogni  colore  appartiene esattamente a una  lista.  Batman  può  distinguere  i
    colori  appartenenti  a  liste diversi, ma non può distinguere i colori appartenenti allo stesso elenco. Data una sequenza di L colori, trova il numero di
    “segmenti” distinti che Batman è in grado di vedere, a causa della sua disabilità, ossia il numero di sequenze che riesca a distinguere:
    due posizioni nella sequenza  appartengano  allo  stesso  segmento  se  sono  adiacenti  e  Batman  non  è  in  grado  di distinguere i colori di tale sequenza.
    
    La prima riga contiene un intero T, che è il numero di casi di test.
    Quindi seguono i casi di test. La prima  riga  contiene  tre  interi  N, M  e  L,
    rispettivamente  il numero di  colori,  il  numero  di  liste  e  la lunghezza della
    sequenza.
    Ciascuna delle successive M righe descrive una lista; la riga inizia con un intero
    Ki, che è la lunghezza dell'i-esima lista, seguita dai Kiinteri:
    Ai1,Ai2,...,AiKi–ossia gli ID dei colori dell'i-esima lista. La riga successiva
    contiene L interi, S1,S2,...,SL, che sono gli ID deicolori della sequenza sottoposta
    a Batman.
 
    INPUT:
        3
        2 2 2
        1 2
        1 1
        2 1
        2 2 4
        1 1
        1 2
        1 2 2 1
        3 2 3
        2 1 3
        1 2
        1 3 1
 
    Per ogni caso di test, stamparein un'unica riga la risposta al problema(numero di
    “segmenti” distinti che Batman è in grado di vedere).
 
    OUTPUT:
        2
        3
        1
 */
int main() {
    unsigned int num_of_tests,N,M,L,list_idx,color,list_len;
    cin>>num_of_tests;
    while(num_of_tests>0){
        //Mi scoccio di svuotarla ogni volta :) 
        map<unsigned int,unsigned int> colors_list;
        cin>>N;
        cin>>M;
        cin>>L;
        list_idx=0;
        //Finchè ci sono liste
        while(list_idx<M){
            cin>>list_len;
            //cout<< "Lista di lunghezza" <<list_len<<endl;
            //O(N)
            while(list_len>0){
                cin>>color;
                colors_list[color]=list_idx;
                list_len--;
            }
            list_idx++;
        }
       // cout<<L;
        //prendi la sequenza
        vector<unsigned int>S(L,0);
        for (unsigned int i =0;i<L;i++)
            cin>>S[i];
        cout<<num_of_seq(colors_list,S)<<endl;
        num_of_tests--;
    }
	return 0;
}
