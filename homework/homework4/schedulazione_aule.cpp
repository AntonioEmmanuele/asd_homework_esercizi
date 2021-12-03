#include<iostream>
#include<vector>
using namespace std;

//Suppongo aule ordinate per tempi di fine crescenti
//la scelta greedy coincide con l'andare ad allocare un'aula se il minimo tempo di fine dei jobs già allocati
//è minore del tempo di inizio della nuova attività, se non è vero allora l'attività si sovrappone in toto a tutte
// e bisogna andare ad usare una nuova aula.
//nel caso in cui il job abbia un tempo di inizio maggiore o uguale del minimo tempo di fine bisogna  capire dove andare
//ad inserirlo.
//per farlo bisogna, similmente all'esempio dello scheduling in aula, andare a prenndere l'aula che mi fa ottenere il minimo scarto
//ossia l'aula che mi minimizza le distanze min i (fj-si) i => aule già inserite.
//Algoritmo:
//Si fa notare che si usa un vettore per rappresenntare le aule allocate, essendo per ipotesi le aule innserite in input
//con tempi di fine crescenti allora il primo elemento del vettore conterrà sempre il minimo tempo di fine

//  min_aule[jobs,numero_jobs]
//    aule[1]<-INF
//    for i<-1..numero_jobs
//    if(aule[1]>jobs[i][1]) //Se si sovrappone a tutti inseriscilo.
//        push[aule,jobs[i][2]]
//    else
//      scarto<-INF
//      slot_aula<- 1
//      for  j<-1..i
//        if jobs[i][1]-aule[j]<scarto
//            scarto<-jobs[i][1]-aule[j]
//            slot_aula<- j
//      aule[slot_aula]<-jobs[i][2]
//    return len[aule]
//
//Complessità :O(n^2)
unsigned int min_aule(unsigned int jobs[][2],const unsigned int num_jobs){
  unsigned int i,j,scarto,scarto_attuale,slot;
  vector <unsigned int > aule;

  for(i=0;i<num_jobs;i++){
    //Nel primo caso si dovrebbe notare che, essendo attuale tempo di finne infinito si  ha
    //min (s0-inf)=-inf.
    //Esce negativo, quindi devo inserire una nuova aula.
    if(i==0){
        aule.push_back(jobs[0][1]);
    }
    else{
        //se il minimo tempo di fine è maggiore del tempo di inizio del nuovo job allora devo andare ad occupare
        //una nuova aula perchè mi sovrappongo con tutti
        if(aule[0]>jobs[i][0]){
          //Inserisco il tempo di fine
          aule.push_back(jobs[i][1]);
        }
        else{
          //trova lo slot che minimizza lo scarto tra si ed fj
          scarto_attuale=jobs[i][0]-aule[0];
          scarto=scarto_attuale;
          slot=0;
          for(j=1;j<i;j++){
              scarto_attuale=jobs[i][0]-aule[j];
              if(scarto_attuale<scarto){
                scarto=scarto_attuale;
                slot=j;
              }
          }
          //Inserisci il tempo di fine
          aule[j]=jobs[i][1];
        }
    }
  }
  return (unsigned int)aule.size();
}

int main(){
  const unsigned int num_jobs=4;
  //2
  unsigned int jobs[4][2]={{1,4},{2,5},{6,7},{7,8}};
  //3
  unsigned int jobs2[4][2]={{1,4},{2,5},{3,7},{7,8}};
  cout<< min_aule(jobs,num_jobs)<<endl;
  cout<< min_aule(jobs2,num_jobs)<<endl;
  return 0;
}
