#include <iostream>
#include<vector>
#include<cmath>
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
    TABLI
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
void costo_ottimo(vector<unsigned int> tagli, unsigned int i, unsigned int j,
    unsigned int dimensione_asse,unsigned int& costo){
        // Non devo più tagliare
        if(i==j){
            return;
        }
        //Altrimenti
        unsigned int idx,min_idx=i;
        //Inizializzalo con la dimensione dell'asse
        costo+=dimensione_asse;
        unsigned int differenze[j-i];
        float media=0;
        //Trova differenze e media
        //n
        for(idx=i;idx<j;idx++){
            differenze[idx]=dimensione_asse-tagli[idx];
            media+=differenze[idx];
        }
        media=media/(j-i);
        //Trova chi minimizza ed infine riesegui
        //n
        for(idx=i+1;idx<j;idx++){
            if(abs(media-tagli[idx])<abs(media-tagli[min_idx]))
                min_idx=idx;
        }
        //Riesegui algo prima per primo sottoproblema e poi per seconndo
        //Per la parte di sinistra allora avrò una dimensione pari al numero del taglio
        costo_ottimo(tagli,i,min_idx,tagli[min_idx],costo);
        //riscala gli ultimi
        for(idx=min_idx+1;idx<tagli.size();idx++)
            tagli[idx]-=tagli[min_idx];
            
        costo_ottimo(tagli,min_idx+1,j,dimensione_asse-tagli[min_idx],costo);
    }
int main() {
	unsigned int dimensione_asse,numero_tagli,i;
	unsigned int costo;
	vector<unsigned int> tagli;
	cin>>dimensione_asse;
	while(dimensione_asse!=0){
	    tagli.clear();
	    costo=0;
	    cin>>numero_tagli;
	    for(i=0;i<numero_tagli;i++){
	        tagli.push_back(0);
	        cin>>tagli[i];
	    }
	    costo_ottimo(tagli,0,tagli.size(),dimensione_asse,costo);
	    cout<<costo<<endl;
	    cin>>dimensione_asse;
	}
	
	return 0;
}