#include<iostream>
#include<vector>

using namespace std;
//O(n+m ) m è il numero di aggiunte, siccome a noi è al più due ed m=O(n) allora 
//abbiamo O(n)
static void rescale(vector<char> &string,vector<char> to_insert){
    unsigned int new_size=string.size()+to_insert.size(),
                    i,j,start_inserting=string.size()/2;
    char vector[new_size];
    //n/2
    for( i=0;i<start_inserting;i++){
        vector[i]=string[i];
        vector[new_size-1-i]=string[string.size()-1-i];
    }
    //Inserisci ultimo carattere se dispari
    if(new_size%2!=0){
        vector[i]=string[i];
        i+1;
    }
    //Inserisci caratteri mancanti
    //n+m
    for(j=0;j<to_insert.size();j++)
        vector[i+j]=to_insert[j];
        
    //ricopia il tutto
    for(i=0;i<new_size;i++){
        
        if(i<string.size()){
            //Cambia gli elementi soltanto
            string[i]=vector[i];
        }
        //altrimenti inserisci proprio unn nuovo vettore
        else
            string.push_back(vector[i]);
    }
}
//Posso avere al più Theta(n/2 ) sottoproblemi all'incirca
//Theta(n/2)*Theta(n)=Theta(n^2) più 
void find_palindrome(vector<char> &string,unsigned int &num_of_palindromes,char& current_char){
    vector<char> to_insert;
    current_char++;
    // Se è uguale ad uno aggiungo una lettera e diminuisco i palindromi di 1
    if(num_of_palindromes==1){
        to_insert.push_back(current_char);
        num_of_palindromes--;
    }
    else if (num_of_palindromes==2){ // se è pari a due aggiungo due caratteri diversi e diminuisco i palindromi di 2
        to_insert.push_back(current_char);
        current_char++;
        to_insert.push_back(current_char);
        num_of_palindromes-=2;
    }
    else{ //Altrimenti aggiungo due lettere uguali ed aumento i palindromi di 3
        to_insert.push_back(current_char);
        to_insert.push_back(current_char);
        num_of_palindromes-=3;
    }
    rescale(string,to_insert);
    if(num_of_palindromes>0)
        find_palindrome(string,num_of_palindromes,current_char);
}
int main(){
    unsigned int num_of_tests,num_of_palindromes,idx;
    char initial_letter='a'-1;
    vector<char>string;
    /*char a1[]="aaaa";
    char a2[]="bb";
    
    vector<char> string(a1,a1+(sizeof(a1)-1)/sizeof(char));
    vector<char>string2(a2,a2+(sizeof(a2)-1)/sizeof(char));
    //cout<<string.size()<< string2.size();
        rescale(string,string2);
     for(idx=0;idx<string.size();idx++)
        cout<<string[idx];
    cout<<endl;
    */
    cin>>num_of_tests;

    while(num_of_tests>0){
        cin>>num_of_palindromes;
        find_palindrome(string,num_of_palindromes,initial_letter);
        for(idx=0;idx<string.size();idx++){
            cout<<string[idx];
        }
        string.clear();
        cout<<endl;
        num_of_tests--;
    }
    
}