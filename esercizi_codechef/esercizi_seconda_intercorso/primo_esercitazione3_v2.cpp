#include<iostream>
#include<vector>
#include<climits>
#define INF INT_MAX
using namespace std;


/*
Traccia:
Bisogna configurare una macchina per tagliare a pezzi delle travi di legno.
Icosti variano in base alla lunghezza dellatrave da tagliare.
Si assume che la macchina faccia solo un taglio alla volta.
È facile notare che selezioni diverse nell'ordine di taglio possono portare a costi diversi.
Ad esempio, si consideri una trave di 10metri che deve essere tagliataa distanza 2, 4 e 7
metri da un'estremità. Ci sono diverse scelte. Si può tagliare prima a 2, poi a 4, poi a 7.
Questo porta ad un costodi 10 + 8 + 6 = 24 perché la prima traveera di 10 metri, la seconda,
risultante dal primo taglio, di 8 e l'ultima, risultante dal secondo taglio,di 6.
Un’altrascelta potrebbe essere tagliare a 4, poi a 2, poi a 7. Questo porterebbe a un costo di
10 + 4 + 6 = 20, che è migliore.Si progetti un algoritmo per determinare il costo minimo
per tagliare una trave.
*/
/* IN:
    LUNGHEZZA trave
    NUMERO tagli
    TAGLI
    se lunghezza=0 termina
    10
    4
    4 5 7 8
    30
    3
    2 20 25
    100
    3
    25 50 75
    0

OUT:
    22
    60
    200
*/

//1- Sottoproblemi: Substring del vettore dei tagli
//2- Guess: L'indice che minimizza il tempo medio degli assi.
//3-Equazione: DP[i,j]=min k {DP[i,k]+DP[k+1,j]+costoAttuale}
//4-Il numeor di sottoproblemi dovrebbe essere Theta(n)*Theta(n)tempo=theta(n^2)
//Theta(n^3)
unsigned int costo_ottimo(vector<bool> tagli,unsigned int i, unsigned int j,unsigned int dimensione_trave){
  unsigned int costo=0,k=i,costo_minimo=INF;
  /*if(i<j)
  unsigned int min_cost=dimensione_trave+costo_ottimo(tagli,tagli[k],i,i+1)+costo_ottimo(tagli,dimensione,i,k)
  */

  for(k=i;k<j;k++){
    if(tagli[k]){
        costo=dimensione_trave+costo_ottimo(tagli,i,k,k-i+1)+costo_ottimo(tagli,k+1,j,j-(k+1));
        if(costo<costo_minimo)
            costo_minimo=costo;
    }
  }
  // Se non è mai stato aggiornato significa che non ho mai avuto un problema del genere
  if(costo_minimo==INF)
    costo_minimo=0;
  return costo_minimo;
}

int main(){
  unsigned int dimensione_trave,numero_tagli,i,helper;
  cin>>dimensione_trave;
  while(dimensione_trave!=0){
    cin>>numero_tagli;
    vector<bool> tagli(dimensione_trave,false);
    for(i=0;i<numero_tagli;i++){
      cin>>helper;
      tagli[helper-1]=true;
    }
    /*
    for(i=0;i<dimensione_trave;i++){
      if(tagli[i])
        cout<<"Taglio ad"<<i+1<<endl;
    }*/
    cout<<costo_ottimo(tagli,0,dimensione_trave,dimensione_trave)<<endl;
    tagli.clear();
    cin>> dimensione_trave;
  }
  return 0;
}
