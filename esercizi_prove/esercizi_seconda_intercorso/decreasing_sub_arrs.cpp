#include <iostream>
#include <vector>

using namespace std;
/*
    Given an array A1,A2,...,AN, count the number of subarrays of array A which are non-decreasing.
    A subarray A[i,j], where 1≤i≤j≤N is a sequence of integers Ai,Ai+1,...,Aj.
    
    A subarray A[i,j] is non-decreasing if Ai≤Ai+1≤Ai+2≤...≤Aj. You have to count the total number of such subarrays.

*/
/*
    INPUT:
    4
    3
    1 3 5
    5
    1 2 3 4 5
    4
    1 4 2 3
    1
    5
    OUTPUT:
    6
    15
    4
    1
    */
//1- Sottoproblemi sono sempre i suffissi
//      Theta(n)
//2- Guess è quante sequenze ci sono.
//          Immagina di aver ela sequenza 1 3 5
//          Indice iniziale è 0.
//          Per ogni elemento se è maggiore devi sommare il suo indice - indice finale+1.
//          Vedi empiritamce ad esempio che 1 3 5
//          count =1
//          3>1 1+2(2 è 1-0+1)
//          5>3 3+3(3 è 2-0+1)
//          Come trovo che questo ciclo si spezza allora vado ad aggiornare indice successivo .
//O(n)
unsigned int do_algo(vector<unsigned int>list,unsigned int &idx){
    unsigned int count=1,list_len=list.size(),old_idx=idx;
    //cout<< "Lunghezza lista "<<list_len<<endl;
    idx=idx+1;
    //cout<<"Indice è "<<idx<<endl;
    while(idx<list_len){
        if(list[idx]>list[idx-1]){
            count+=(idx-old_idx)+1;
            idx++;
        }
        else
            break;
    }
    idx++;
    //cout<<"Indice ritornato"<<idx<<endl;
    return count;
}
//Theta(n)
//Algo totale è Theta(n^2
unsigned int decreasing_sub_arrays(vector<unsigned int>list){
    unsigned int idx=0,count=0;
    // N sub problems * N
    while(idx<list.size())//{
        count+= do_algo(list,idx);
        //cout<< "indice in while"<<idx<<endl;
   // }
    return count;
}

int main() {
	unsigned int num_tests=0;
	unsigned int array_dimension,i;
	cin>>num_tests;
	while(num_tests>0){
	    cin>>array_dimension;
	    vector <unsigned int>a(array_dimension,0);
	    for( i=0;i<array_dimension;i++)
	        cin>>a[i];
	    cout<<decreasing_sub_arrays(a)<<endl;
	    num_tests--;
	}
	return 0;
}
