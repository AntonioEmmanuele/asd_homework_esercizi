#include <iostream>
#include<string>
#include<cmath>
#include <vector>
/*
 https://leetcode.com/problems/longest-palindromic-substring/
 */
using namespace std;

//1-Sottoproblemi : substring in partilare definiamo come L[1,n] come la massima sottostringa palindroma contenuta nell'intervallo di 0 n #sub=n^2
//2-indovinare quale è la stringa, per farlo ci sono due possibilità: String[1]=String[n]
//      quindi ho 1+1(iniziale e finale) + ciò  che ho nel mezzo
//      oppure semplicemente sono la massima lunghezza ta L(1,N-1) ed L(2,N)
//      Ad esempio nella parola abba ho per L(2,4)=max(L(2,3),L(3,4))=max((bb),(ba))=(b,b)=2
//      Invece per L(1,4), essendo string[1]=string[4]=1+1+palinndromo nel mezzo(2).
//      #Theta(1)
//3- Ricorrenza: L(i,j)= se string[i]=string[j] 2+L[i+1][j-1](ossia ciò che è nel mezzo)
//                altrimenti max(L[i+1][j], L[i][j-1]) ossia tra parte destra e sinistra.
//4- Sottostruttura ottima, forma dei problemi ad albero secondo dipendenza spiegata in punto 2.
//(Theta(n^2))
void max_palindrome(string k ,unsigned int &row, unsigned int &column){
    vector<vector<unsigned int> >L(k.size(),vector<unsigned int>(k.size(),0));
    unsigned int i,j,c;
    //Dimensione 1
    for( i=0;i<k.size();i++)
        L[i][i]=1;
    unsigned int max_size=1;
    row=0;
    column=0;
    //Dimensione 2
    for(i=0;i<k.size()-1;i++){
        if(k[i]==k[i+1])
            L[i][i+1]=2;
        else
            L[i][i+1]=1;
        //prendi massimo
        if(L[i][i+1]>max_size){
            max_size=L[i][i+1];
            column=i+1;
            row=i;
            cout<<"Here we have"<< column<<" "<<row<<"With max size" <<max_size<<endl;
        }
    }
    
    //Per ogni possibile palindromo di lunghezza 3.
    //Ossia sto prendendo ogni possibile estremo destro
    //Scelto un approccio bottom up ma potrei farlo anche top down
    for(j=2;j<k.size();j++){ //Per ogni dimensione
        for(i=0;i<k.size()-j;i++){
            c=j+i;//devo shiftare anche l'estremo destro
            if(k[i]==k[c])
                L[i][c]=L[i+1][c-1]+2;
            else
                L[i][c]=max(L[i+1][c],L[i][c-1]);
            if(L[i][c]>max_size){
                row=i;
                column=c;
                max_size=L[i][c];
            }
        }
    }
    /*
    for(i=0;i<k.size();i++){
        for(j=0;j<k.size();j++){
            cout<<L[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;*/
}

int main(int argc, const char * argv[]) {
    unsigned int t,m;
    cin>>t;
    unsigned int row=0,column=0;
    while(t>0){
        string k;
        cin>>k;
        max_palindrome(k,row,column);
        for(m=row;m<=column;m++)
            cout<<k[m];
        cout<<endl;
        t--;
    }
    return 0;
}
