#include<iostream>
#include<string>
/*
https://leetcode.com/problems/longest-palindromic-substring/
*/
using namespace std;
static unsigned int current_max=0;
//Theta(n)
bool is_palindrome(string k, unsigned int start ,unsigned int end){
    if(start==end)
        return true;
    if(start>end)
        return false;
    int idx=0;
    for(idx=start;idx<=end;idx++)
        if(k[idx]!=k[end-idx+start])
            return false;
    return true;
    
}
//1-Sottoproblemi sono i suffissi (O(n))
//2-Guess:Trovare se il max palindromo nel sottoproblema coincide con il massimo totale
//  Theta(n^2)-> per ogni indice O(n), devo vedere se è palindromo (O(n))
//  for(indice attuale a fine)
//3-Lunghezza_massima= max (palindrome[indice_attuale, fine],palindrome[indice_attuale+1,fine])
//
//4-Ogni problema dipende solo dal successivo. O(n^3)
//5- ho già la soluzione alla fine
void max_palindrome(string k, unsigned int &i,unsigned int &j,unsigned int initial){
    //Calcola i palindromi
    if(initial<=k.size()-1){
        unsigned int idx=0;
        unsigned int len=0;
        for(idx=initial;idx<k.size();idx++){
            if(is_palindrome(k,initial,idx)){
                len=idx-initial+1;
                if(len>current_max){
                    current_max=len;
                    i=initial;
                    j=idx;
                }
            }

        }
        //Richiamalo sul successivo suffisso
        max_palindrome(k,i,j,initial+1);
    }
    else{
        return;
    }
}
int main(){
    unsigned int tests;
    cin>>tests;
    string k;
    unsigned int i=0,j=0,initial=0,idx=0;
    while(tests>0){
        cin>>k;
        max_palindrome(k,i,j,initial);
        for(idx=i;idx<=j;idx++){
            cout<<k[idx];
        }
        cout<<endl;
        current_max=0;
        i=0;
        j=0;
        tests--;
    }
    
}
