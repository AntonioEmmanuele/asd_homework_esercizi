// AUTORI: De Rosa Giuseppe, Emmanuele Antonio
#include "stdio.h"
#include "stdlib.h"
typedef int array_type;

/**
    Trova il massimo di un array unimodale usando la ricerca binaria
*/
int maximum_unimodale(array_type*array,unsigned int start, unsigned int end ){
  /********************************


      maximum_unimodale[array,start,end]

        //Se è rimasto un elemento ritorna elemento stesso
        if end==start
          end
        //controlla se sono rimasti solo due elementi, in tal caso rirona la posizione del massimo
        if end+start == 2
          if array[end]>array[start]
              end
          else
            start
        middle<-(end+start)/2

        //se l'array è contemporanemente l'ultimo della sequenza crescente
        //ed il primo della decrescente
        if(array[middle]>array[middle-1] && array[middle]>array[middle+1])
           middle

        //e' minore del successivo dunque dobbiamo ancora crescere
        if(array[middle]>array[middle-1] && array[middle]<array[middle+1])
            maximum_unimodale[array,middle+1,end]

        //Significa che stiamo nella parte di destra e dobbiamo spostarci a sinistra
        //Siamo ossia nella parte decrescente e dobbiamo spostarci.
        if array[middle-1]>array[middle] && array[middle]>array[middle+1]
            maximum_unimodale[array,left,middle-1]

        ogni foglia ha sempre un solo figlio ed D(n)=C(n)=1
        T(n)=T(n/2)+Theta(1)=T(n/2)+1
        Quindi essendo pow[n,log2[1]]=1 ricadiamo nel secondo caso del M.T.
        T(n)=Theta(n^log2(1)*log(n))=Theta(log(n))
  *********************************/

    //Array di un solo elemento
    if(end==start)
      return end;

    //Array di due elementi
    if((end+start)==2){
        if(array[end]>array[start])
            return end;
        else if(array[start]>array[end])
            return start;
    }

  unsigned int middle=(end+start)/2;

  //Se è il massimo della sequenza crescente  e lo startind dell'altra sequeza
  if(array[middle]>array[middle-1] && array[middle]> array[middle+1])
    return middle;

  //Se sono maggiore del precedente ma minimore del successivo devo ancora crescere
  //Quindi mi sposto nel sottoarray end+1 middle
  if(array[middle]>array[middle-1] && array[middle]< array[middle+1])
    return maximum_unimodale(array,middle+1,end);

  //Mi sposto dualmente a sinistra se l'array è minore del precedente ma maggiore del successivo
  //ossia mi trovo nella sequenza decrescente, devo andare ad incrementare per raggiungere il max.
  if(array[middle]<array[middle-1] && array[middle]> array[middle+1])
    return maximum_unimodale(array,start,middle-1);

  return -1;
}

int main(){
  array_type unimodale[]={1,2,3,2,1};
  int posizione_massimo=maximum_unimodale(unimodale,0,4);
  printf("La posizione %u è quella dove risiede il valore massimo %u \n",posizione_massimo,unimodale[posizione_massimo]);
  array_type unimodale2[]={1,2,3,4,3,2};
  posizione_massimo=maximum_unimodale(unimodale2,0,5);
  printf("La posizione %u è quella dove risiede il valore massimo %u \n",posizione_massimo,unimodale2[posizione_massimo]);
  array_type unimodale3[]={5,6,5,4,3,2,1,0};
  posizione_massimo=maximum_unimodale(unimodale3,0,7);
  printf("La posizione %u è quella dove risiede il valore massimo %u \n",posizione_massimo,unimodale3[posizione_massimo]);
  return 0;
}
