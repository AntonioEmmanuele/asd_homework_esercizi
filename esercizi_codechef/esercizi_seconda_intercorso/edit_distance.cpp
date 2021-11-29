#include <iostream>
#include<string>
using namespace std;
/*
 https://leetcode.com/problems/edit-distance/
 */
 */
//O(1)
unsigned int minimum (unsigned int a,unsigned int b, unsigned int c){
    if(a>b){
        return b>=c ?c : b;
    }
    else {
        return a>=c ?c : a;
    }
}
//1-Sottoproblemi : to_match[:j] matching[:i] Theta(n^2)
//2-Guess: Quello che per ogni j mi porta ad unna cancellazione di i,inserimento di j, rimozione.
//3- min_ops[i,j]=1+min(min_ops[i,j-1], // inserito
//       min_ops [i-1,j], //rimosso
//       min_ops[i+1,j+1] //Ho inserito
//4- Theata(n^2). Ogni problema dipende sempre dal successivo.
unsigned int min_ops(string to_match,string matching,unsigned int j, unsigned int i){
    //Se ho finito la stringa allora devo solo inserire i caratteri mancandi di to_match
    if(i==0)
        return j;
    //Se to_match non ha più caratteri devo rimuovere i rimanenti da matching
    if(j==0)
        return i;
    if(to_match[j-1]==matching[i-1])
        return min_ops(to_match, matching,j-1,i-1);
    //operazione corrente+ minimo tra le scelte
    return  1+minimum(min_ops(to_match, matching, j,i-1), //Rimosso
                      min_ops(to_match, matching,j-1,i), //inserito
                      min_ops(to_match,matching,j-1,i-1)); //replarement
  
}

int main(int argc, const char * argv[]) {
    unsigned int num_of_tests;
    cin>>num_of_tests;
    string to_match,matching;
    while(num_of_tests>0){
        cin>>to_match;
        cin>>matching;
        cout<<min_ops(to_match,matching,to_match.size(),matching.size())<<endl;
        num_of_tests--;
    }
    return 0;
}
