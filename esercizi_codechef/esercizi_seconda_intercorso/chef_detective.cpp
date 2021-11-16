#include <iostream>
#include <map>
using namespace std;
/*
    https://www.codechef.com/problems/CHEFDETE
*/
int main() {
	unsigned int num_of_criminals,k;
	cin>>num_of_criminals;
	map<unsigned int,unsigned int> refers;
	//Inizializza a 0 il numero di riferimenti
    for(unsigned int i=1;i<=num_of_criminals;i++)
        refers[i]=0;
    for(unsigned int i=0;i<num_of_criminals;i++){
        cin>>k;
        if(k!=0)
            refers[k]++;
    }
    
    for(unsigned int i=1;i<=num_of_criminals;i++)
        if(refers[i]==0)
            cout<<i;
	return 0;
}
