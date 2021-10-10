//
//  inversioni.c
//
//
//  Created by Antonio Emmanuele on 10/10/2021.
//

#include <stdio.h>
#include "stdlib.h"
#include"string.h"
typedef  int array_type;


/*
    fai il merge calcolando le inversioni
 */
void merge(array_type *array_input,unsigned int starting,unsigned int middle_point,unsigned int end, int*inversioni){

    /*************************************************
        Assumendo gli array inizino da 1:
        n numero di elementi
        starting <-0
        end<-n

        size_left <-middle_point-starting+1           c1    1
        size_right<- end-middle_point                 c2    1
        L[size_left+1],L[size_right+1]                c3    1
        for i ← 1 to size_left                        c4    size_left+1
            L[i] ←array_input[i+starting]             c5    size_left
        for j ← 1 to size_right                       c6    size_right+1
            R[j]<-array_input[i+middle_point+1]       c7    size_right
        L[size_left+1] ← R[size_right+1] ← ∞          c8    1
        i←j←1                                         c9    1
        for k ← starting to end                       c10   end-starting+1 =n+1
          if L[i]>R[j]                                c11   n
              array_input[k]<-R[j]                    c12   tj
              inversioni<- (size_left-i)+1            c13   tj
              j<-j+1                                  c14   tj
          else                                        c15   n
            array_input[k]<-L[i]                      c16   ti
            i<-i+1                                    c17   ti

      abbiamo:
      n1<-size_left
      n2<-size_right

      n>=n1,n2
      nel peggiore dei casi tj è pari ad n-1 ed (vincolando ti ad 1 ) e viceversa.

      f(n)= c1+c2+c3+(n1+1)c4+n1c5 +(n2+1)c6+n2*c7+ c8+c9+(n+1)c9+n(c11+c15)+c16+c17+ (n-1)(c12+c13+c14)

      Essendo questo il w.c. (tj=n-1 ed ti=1) ho che il tempo è Theta(n)  (idem per ti=n-1 ed tj =1)


     **********************************************/


    //+1 perchè dobbiamo considerare elemento 0
    unsigned int size_left=middle_point-starting+1;          // costo=c1 volte 1
    unsigned int size_right=end-middle_point;               // costo c2  volte 1
    unsigned int i=0;                                       // costo c3 volte 1
    unsigned int j=0;                                       //costo c4 volte 1
    unsigned int k=starting;                                //costo c5 volte 1
    array_type left[size_left];                             //costo c6 volte 1
    array_type right[size_right];                           //costo c7 volte 1

    //copia i due sottoarray.
    //printf("La dimensione è %u \n ,i bytes \n ",size_left,size_left*sizeof(array_type));
    memcpy(left,&array_input[starting],size_left*sizeof(array_type));
    memcpy(right,&array_input[middle_point+1],size_right*sizeof(array_type));
    unsigned int temp=0;
    //Finchè uno dei due array non si esaurisce
    while (i<size_left && j<size_right){
        //Vanno ordinati sennò algo non funziona
        if(left[i]<=right[j]){
            array_input[k]=left[i];
            i++;
        }
        else{
            array_input[k]=right[j];
            //Se left> right aggiorna le inversioni
            //SICCOME LEFT E' MAGGIORE DI RIGHT ALLORA SONO SICURO CHE I RIMANENTI ELEMENTI SONO MAGGIORI DI RIGHT.
            //QUINDI VADO AD INCREMENTARE LE INVERSIONI DEL NUMERO DI ELEMENTI RIMANENTI OSSIA size_left-i
            *inversioni=(*inversioni)+(size_left-i);
            j++;
        }
        //Va sempre incrementato
        k++;
    }

    //nel caso in cui il destro si esaurisca per primo
    while(i<size_left ){
        array_input[k]=left[i];
        i++;
        k++;
    }

    //Nel caso in cui il sinistro si sia esaurito per primo
    while(j<size_right ){
          array_input[k]=right[j];
          j++;
          k++;
      }
}

/**

 */
void merge_sort_inversion(array_type*array_input,unsigned  int starting,unsigned int end, int* inversioni){

      /*****************

        D()  tempo per dividerli(O(1))
        C() tempo per ricombinarli (Theta(n))
        Theta(n)+O(1)=Theta(n)
        T(n)=b*T(n/a)+D(n)+C(n)

        bT(n/a)+Theta(n)= 2*T(n/2)+n

        n^(log2(2))=n.
        Ricadiamo nel secondo caso del M.T.

        n^(log2(2))*log(n)=nlog(n)

      ********************/

    if(end>starting){ // se ho ancora elementi

        unsigned int middle_point=(end+starting)/2;

        //Calcola il numero di inversioni per i due sottoarray
        merge_sort_inversion(array_input,starting,middle_point,inversioni);
        merge_sort_inversion(array_input,middle_point+1,end,inversioni);

        //Fai merge e calcola le inversioni
        merge(array_input,starting,middle_point,end,inversioni);

    }
}


int main(){

    array_type input []={5,4,3,2,1}; //n/2*(n-1)=5/2*4=10 inversioni! (4 3 2 1 0)
    int inversioni=0;
    merge_sort_inversion(input,0,4,&inversioni);
    for(int i=0;i<5;i++)
        printf("%d",input[i]);
    printf("\n");
    printf("Le inversioni sono %d\n ",inversioni);

    array_type input2[]={2,3,8,6,1}; //5 inversioni
    inversioni=0;
    merge_sort_inversion(input2,0,4,&inversioni);
       for(int i=0;i<5;i++)
           printf("%d",input2[i]);
       printf("\n");
       printf("Le inversioni sono %d\n ",inversioni);
    return 0;
}
