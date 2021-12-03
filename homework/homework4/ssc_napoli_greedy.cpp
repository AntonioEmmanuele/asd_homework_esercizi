#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<int> vec;
typedef vector<vector<int> > matrix;

matrix multiple_knapsack_greedy (vec& groups, int gradini, int gradinate,int&biglietti_venduti);
int max (vec groups, int posti_disponibili);

int main()
{
    int temp[4] = {5,7,3,8};
    vec groups (temp, temp+sizeof(temp)/sizeof(int));
    int biglietti_venduti;
    matrix mat = multiple_knapsack_greedy(groups, 10, 3,biglietti_venduti);

    for (int i=0; i<3; i++) {
        for (int j=0; j<10; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout<< endl;
    cout<< "Il numero di biglietti_venduti è "<< biglietti_venduti<<endl;
    int temp2[13] = {7,8,9,2,2,2,2,2,2,2,2,2,2}; //Inserisce
    vector< int> gruppi(temp2,temp2 +sizeof(temp2)/sizeof( int));
    /*
    for(unsigned int i=0;i<gruppi.size();i++)
      cout<<gruppi [i ]<<" ";
    cout<< endl;
    cout<< "Per la prima iterazione il massimo è "<< gruppi[max(gruppi,10)]<<endl;*/
    matrix mat2 = multiple_knapsack_greedy(gruppi, 10, 3,biglietti_venduti);


    for (int i=0; i<3; i++) {
        for (int j=0; j<10; j++)
            cout << mat2[i][j] << " ";
        cout << endl;
    }
    cout<<endl<<"Il numero di biglietti_venduti è "<< biglietti_venduti<<endl;
    /*
    cout<< gruppi.size()<<endl;
    for(unsigned int i=0;i<gruppi.size();i++)
      cout<<gruppi [i ]<<" ";*/

    return 0;
}

/*
 * 1) Trovare il max (groups) per capire il primo gruppo che entra nell'attuale riga (gradinata)
 * 2) Far entrare il gruppo e rimuoverlo dal vettore groups
 * 3) STOP = la dimensione di groups è 0 oppure non ci sono più gradinate disponibili
*/

//Algoritmo
//  multiple_knapsack_greedy[gruppi, gradini, gradinate]
//    biglietti_venduti<-0
//    counter_gradinata<-0
//    posti_disponibili<-gradini
//    while len[gruppi]!=0 //finchè ci sono gruppi
//      maximum_people_idx<-max[gruppi,posti_disponibili] //trova il massimo numero di persone che possono entrare nella gradinata, per questo prende i posti
//      if maximum_people_idx<0 //Se nessun gruppo può entrare nell'attuale gradinata
//          counter_gradinata<-counter_gradinata+1
//          if counter_gradinata==gradinate //se si sono riempite tutte le gradinate
//            break
//          else
//            posti_disponibili<-gradini // ripristina i posti
//      else //se il gruppo può entrare
//        biglietti_venduti<-biglietti_venduti+gruppi[maximum_people_idx] //incrementa il numero di biglietti_venduti
//        posti_disponibili<-posti_disponibili-gruppi[maximum_people_idx] //aggiorna i posti disponibili
//        erase[gruppi,maximum_people_idx] //rimuovi l'elemento
//    return biglietti_venduti
//O(groups.size()^2)
matrix multiple_knapsack_greedy (vec &groups, int gradini, int gradinate,int& biglietti_venduti) {
    matrix mat(gradinate, vec (gradini,0));

    int counter_gradinata = 0;
    bool flag = false;
    biglietti_venduti=0;

    int maximum_people = 0;
    int posti_disponibili = gradini;
    //O(groups(size))
    while (groups.size() != 0 && !flag) { //Il flag al più mi fa finire prima e non dopo O(groups.size())
        maximum_people = max(groups, posti_disponibili); //O(groups.size())

        if (maximum_people < 0) {
            //cout<< "Non si trova un gruppo da inserire con capacità " << posti_disponibili<< " in gradinata "<< counter_gradinata<<endl;
            counter_gradinata++;
            if (counter_gradinata == gradinate) { //Contando da 0, abbiamo già raggiunto la gradinata finale
                flag = true;
            }
            else {
                posti_disponibili = gradini;
            }
        }
        else {
            //  cout<<" gruppo da inserire "<< groups[maximum_people]<< " con attuali posti "<< posti_disponibili<< " per gradinata"<<counter_gradinata<<endl;
            //For non utile all'algoritmo

            for (int j=gradini-posti_disponibili; j < gradini-posti_disponibili+groups[maximum_people]; j++) //O(1)
                mat[counter_gradinata][j] = groups[maximum_people];

            biglietti_venduti+=groups[maximum_people];
            posti_disponibili -= groups[maximum_people];
            groups.erase(groups.begin() + maximum_people);
        }
    }

    return mat;
}
/*
    max[gruppi, posti_disponibili]
      maximum<- -1
      idx<- -1
      for i <- 1.. len[gruppi]
        if gruppi[i]>maximum and gruppi[i]< posti_disponibili //se è massimo ed entra nella gradinata
          maximum<- gruppi[i]
          idx <-i
      return i
*/
//O(gruppi.size())
int max (vec groups, int posti_disponibili) {
    if (groups.size() == 0)
        return -1;

    int maximum = -1;
    int index = -2;
    for (int i=0; i<(int)groups.size(); i++) {
        if (maximum < groups[i] && groups[i] <= posti_disponibili) {
            maximum = groups[i];
            index = i;
        }
    }

    return index;
}
