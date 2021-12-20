#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;

static float min_len=INT_MAX;
static vector<vector<bool> > links;

static float calc_distance(unsigned int x1, unsigned int x2,unsigned int y1, unsigned int y2){
  return (float)sqrt(pow((float)((float)x2-(float)x1),2)+pow((float)((float)y2-(float)y1),2));
}
//Theta(n)
bool is_aSolution(vector<bool> available,vector<unsigned int>&solutions){
  unsigned int  count=0;
  for (unsigned int i =0;i<available.size();i++){
      if(available[i]){
        count++;
        solutions.push_back(i);
      }
  }
  return count==2;
}

void process_solution(vector<vector<unsigned int > > computers, vector <vector <bool > > matrix){
  float actual=0;
  for(unsigned int i=0;i<matrix.size();i++)
    for(unsigned int j=0;j<matrix[0].size();j++)
      if(matrix[i][j])
        actual+=calc_distance(computers[i][0],computers[j][0],computers[i][1],computers[j][1])+16.0;
  if(min_len>actual){ //Se è minimo allora aggiorna la soluzione globale
      min_len=actual;
      links=vector<vector< bool > > (matrix);
  }
}
//O(n^3)
void backtrack(vector<vector<unsigned int> > computers,  int idx,vector <bool> available,
  vector<vector<bool> > link_matrix){
//cout<<"Sono chiamato per"<< idx<<endl;
  vector<unsigned int> solutions;
  if (is_aSolution(available, solutions)){ //Se è una soluzione allora vado a processarla.
    //Altrimenti la matrice dopo non insegue bene la soluzione
    if(solutions[0]==idx)
        link_matrix[idx][solutions[1]]=true; //Aggiorna la matrice dei link
    else
        link_matrix[solutions[1]][solutions[0]]=true;

    process_solution(computers,link_matrix);
  }
  if(idx!=-1) //Se non sono al primo passo allora vado a settare l'elemento a non disponibile
    available[idx]=false;

  //Non ho bisogno di eseguire la procedura construct candidates in quanto i candidati sono gli stessi pc
  //Procediamo con una ricerca in profondità.
  for(unsigned int i=0;i<computers.size();i++){ //Andiamo a controllare i candidati
      if(i!=idx && available[i]){ //Se non sono l'indice e sono disponibile allora
        link_matrix[idx][i]=true;
        backtrack(computers,i,available,link_matrix);
        link_matrix[idx][i]=false;
      }
  }

}

int main(){
    unsigned int num_of_computers;
    cin>> num_of_computers;
    while(num_of_computers!=0){
    vector<vector<unsigned int> > computers(num_of_computers,vector<unsigned int> (2,0));
    for(unsigned int i=0;i<num_of_computers;i++){
      cin>> computers[i][0];
      cin>> computers[i][1];
    }
    vector<bool> available(num_of_computers,true);
    vector<vector<bool> >link_matrix(num_of_computers,vector<bool> (num_of_computers,false));
    backtrack(computers,0,available,link_matrix);
    unsigned int counter=0,i=0,j=0;
    bool condition=true;
    /*for(unsigned int i=0;i<links.size();i++){
        for(unsigned int j=0;j<links.size();j++){
            if(links[i][j])
                cout<< i <<" "<< j<<endl;
        }
    }*/
    while ( counter <num_of_computers){
        while(j<num_of_computers &&condition){
            if(links[i][j]){
                cout<< "Costo tra ("<< computers[i][0] <<" , "<<computers[i][1]<< ") , (" <<
                        computers[j][0]<<" , "<< computers[j][1]<< ") "<<calc_distance(computers[i][0],
                        computers[j][0],computers[i][1],computers[j][1])+16<<endl;
                condition=false;
                i=j;
            }
            j++;
        }
        j=0;
        condition=true;
        counter++;
    }
    cout<<min_len<<endl;
    min_len=INT_MAX;
    cin>>num_of_computers;
  }
  return 0;
}
