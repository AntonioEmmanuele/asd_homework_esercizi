#include<iostream>
#include<vector>
#include <algorithm>
#include<fstream>
#include <cmath>
using namespace std;
/*
  PROBLEMA.
    Siano  dati  diversi  segmenti  con  coordinate,  lungo  l’asse  x, pari
    a [Li,  Ri]. Si  determini la  quantità minimadi segmenti che occorrono per coprire completamente il segmento
    con coordinate [0,M].

  INPUT
     La prima riga è il numero di casi di test, seguita da una riga vuota.Ciascun caso di test nell'inputi
     nizia con un numero intero M(1 ≤ M ≤ 5000), seguito dalle coppie "Li Ri"(|Li |, |Ri | ≤ 50000, i ≤ 100000),
     ciascunasu una riga separata. Ciascun caso di test termina con la coppia “0 0”.
     Ogni caso di test case è separato dal successivo da una riga vuota.

  OUTPUT
    Per ogni caso di test, il programma stampi nella prima riga di output il numero minimo di segmenti che possono
    coprire il segmento [0,M]. Nelle righe seguenti, il programma stampi le coordinate dei segmentiscelti, ordinate per
    la loro estremità sinistra (Li). La coppia '0 0' non deve essere stampata. Se [0,M] non può essere coperto da nessun
    insieme disegmenti, il programma stampi"0" (senza virgolette).Si stampiuna riga vuota tra gli output per due casi di test
    consecutivi.
    Sample Input
    2
    -1 0
    -5 -3
    2 5
    0 0

    1
    -1 0
    0 1
    0 0

    Sample Output
    0

    1
    01
 */
//Theta(nlogn)
int min_segmenti(vector<pair<int,int> > segmenti, int m ,vector<pair<int,int>>& couples){
  int to_ret=0;
  auto cmp=[](pair<int,int> s1,pair<int,int> s2){
    if(s2.first>s1.second) // -1 0
      return true;
    else if(s2.first>=s1.first && s2.first<s1.second) //0 1 0 1
      return s2.second>= s1.second;
    else
      return false;
  };
  sort(segmenti.begin(),segmenti.end(),cmp); //nlogn

  /*for(unsigned int i=0;i<segmenti.size();i++)
    cout<< segmenti[i].first << " "<<segmenti[i].second<<endl;*/

  //Bisogna come prima cosa ordinare i segmenti
  int min=INT_MAX;
  unsigned int min_idx;
  int actual;
  for(unsigned int i=0;i<segmenti.size();i++){  //Trova il segmento più vicino a quello di sinistra,scelta greedy
    actual=abs(segmenti[i].first-0);
    if(actual<min){
      min=actual;
      min_idx=i;
    }
  }
  couples.push_back(segmenti[min_idx]);
  //cout<<"Il minimo trovato è"<<segmenti[min_idx].first<< " "<<segmenti[min_idx].second<<endl;
  //Una volta che abbiamo trovato l'indice più vicino
  if(segmenti[min_idx].second>=m) //Se lo copro completamente
    return 1;
  //Altrimenti prendi il minimo numero di min_segmenti
  else{
    unsigned int count=0,star=min_idx;
    while(segmenti[star].second<m){
      count++;
      if(segmenti[star+1].first==segmenti[star].second){
        star++;
        couples.push_back(segmenti[star+1]);
      }
      else //se non sono adiacenti è inutile che procedo
        break;
    }
    if(count !=1)
      return count;
  }
  return to_ret;
}
int main(){

  ifstream my_file("esercitazione4_in.txt");
  if(my_file.is_open()){
    //cout<<"Aperto"<<endl;
    unsigned int tests;
    my_file>>tests;
    int m;
    pair<int,int> h;
    while(tests>0){
      my_file>>m;
      vector<pair<int,int> > segmenti;
      bool check=false;
      while(!check){
        my_file>>h.first;
        my_file>>h.second;
        segmenti.push_back(h);
        if(h.first==0&&h.second==0)
          check=true;
      }
      /*
      cout<<m<<endl;
      for(unsigned int i=0;i<segmenti.size();i++)
        cout<<segmenti[i].first<< " "<<segmenti[i].second<<endl;*/
      vector<pair<int,int > > coppie;
      cout<< min_segmenti(segmenti,m,coppie)<<endl;
      h.first=0;
      h.second=0;
      for(unsigned int i=0;i<coppie.size();i++){
        if(coppie[i]!=h)
          cout<<coppie[i].first<< " "<<coppie[i].second<<endl;
      }
      cout<<endl;
      tests--;
    }
    //cout<< min_segmenti(segmenti,m)<<endl;
  }
  return 0;
}
