/* https://leetcode.com/problems/maximum-subarray/ */
#include <iostream>
#include<vector>
using namespace std;
//1- sottoproblemi sono i suffissi array[i:] Theta(n)
//2-Guess consiste nell'indovinare per ognni indice se fare la somma o usarlo come punto di partenza
//  per una nuova sequenza Theta(1)
// 3-max_sum=maxi(a[i],massimo_corrente+a[i])
//4- Theta(n)-> siccome il problema in i dipende sempre solo da i+1 non ho cicli
int maximum_sum(vector<int> array){
    int massimo_corrente=array[0];
    int massimo_da_ritornare=array[0];
    unsigned int idx;
    for(idx=1;idx<array.size();idx++){
        //Immaginiamo di avere [-2 1], allora parto da -2 e noto che -2+1 =-1 , 1 è più grande 
        //quindi l'attuale sequenza maggiore è proprio 1
        massimo_corrente=max(array[idx],massimo_corrente+array[idx]);
        //Ad esempio [-2 7 -8 1 2 ]
        //il massimo da ritornare quando arrivo ad 1 è 7(il massimo corrente è 1 in quanto noto che è maggiore 
        //della somma -8+7+1)
        //la sequenza 1, 2 mi da 3 ma non è comunque da aggiornare
        massimo_da_ritornare=max(massimo_da_ritornare,massimo_corrente);
    }
    return massimo_da_ritornare;
}
int main() {
    unsigned int size_of_array,idx;
    cin>>size_of_array;
    vector<int>array(size_of_array,0);
    for(idx=0;idx<size_of_array;idx++)
        cin>>array[idx];
    cout<<maximum_sum(array)<<endl;
	return 0;
}
