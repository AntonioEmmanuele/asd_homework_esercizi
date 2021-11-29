#include<iostream>
#include <vector>
using namespace std;
/*
https://leetcode.com/problems/pascals-triangle/
*/
//1-Sottoproblemi: nuova riga
//2-Guess:nulla
//3-row[i]=triangle[i][triangle.size()-1]+triangle[i+1][triangle.size()-1]
//4- ogni riga dipennde dalla precedente come se avessimo un prefisso
//5-non dobbiamo fare nulla
//Theta(n^2)
void pascal_triangle(vector < vector <unsigned int> > &triangle, int num){
  if(triangle.size()==num){
    return;
  }
  else{
      vector<unsigned int > row;
      unsigned int i;
      if(triangle.size()==0){
        row.push_back(1);
      }
      else{
        //Inizializzo il vettore riga con 1 elemento in più rispetto alla precedente.
        //Ad esempio per la seconda riga, avento un 1, allora avrò una riga di dimensione 2
        for( i=0;i<=triangle.size();i++)
          row.push_back(0);
        row[0]=1;
        row[triangle.size()]=1;
        //Dobbiamo calcolare i valori intermedi
        for(i=0;i<triangle.size()-1;i++){
            row[i+1]=triangle[triangle.size()-1][i]+triangle[triangle.size()-1][i+1];
        }
      }
      triangle.push_back(row);
      pascal_triangle(triangle,num);
  }
}

int main(){
  unsigned int tests,num,i,j;
  vector<vector<unsigned int> >triangle;
  cin>>tests;
  while(tests>0){
    cin>>num;
    pascal_triangle(triangle,num);
    for(i=0;i<triangle.size();i++){
      for(j=0;j<triangle[i].size();j++){
        cout<<triangle[i][j]<<" ";
      }
      cout<<endl;
    }
    cout<<endl;
    triangle.clear();
    tests--;
  }
  return 0;
}
