//
//  main.cpp
//  sudoku_backtracking
//
//  Created by Antonio Emmanuele on 08/11/2021.
//  Copyright © 2021 Antonio. All rights reserved.
//

#include <iostream>
#include <vector>
#define SIZE 9
#define UNASSIGNED 0
#define DBG 1
#define DBG1 0
using namespace std;

//Checks if an element is in row
static bool is_in_row(const vector<vector<unsigned int> >matrix,const unsigned int num,const unsigned int row){
    unsigned int i;
    for(i=0;i<SIZE;i++){
        if (matrix[row][i]==num)
            return true;
    }
    return false;
}

//Checks if an element is in column
static bool is_in_column(const vector<vector<unsigned int> >matrix,const unsigned int num,const unsigned int col){
    unsigned int i;
    for(i=0;i<SIZE;i++){
        if (matrix[i][col]==num)
            return true;
    }
    return false;
}

//Checks if an element is in matrix
static bool is_in_matrix( const vector<vector<unsigned int> >matrix,const unsigned int row,const  unsigned int col,const unsigned int num ){
    
    unsigned int i,j;
    unsigned int size=3;
    unsigned int row_with_offset=row-row%size;
    unsigned int col_with_offset=col-col%size;
    for(i=row_with_offset;i<size+row_with_offset;i++){
        for(j=col_with_offset;j<size+col_with_offset;j++){
            // cout<<matrix[i][j]<< " ";
            if(matrix[i][j]==num)
                return true;
        }
       // cout <<endl;
    }
    return false;
}

/* Performs backtracking*/
bool backtrack(vector<vector<unsigned int> >& ,unsigned int &, unsigned int &);
/* check if the input matrix is a solution*/
bool is_a_solution(vector<vector<unsigned int> >,unsigned int& ,unsigned int& );
/* find the next candidate*/
void construct_candidates(const vector<vector<unsigned int> > ,const unsigned int , const unsigned int  ,vector<unsigned int>&);
/*
  RESULT:
    3 1 6 5 7 8 4 9 2
    5 2 9 1 3 4 7 6 8
    4 8 7 6 2 9 5 3 1
    2 6 3 4 1 5 9 8 7
    9 7 4 8 6 3 1 2 5
    8 5 1 7 9 2 6 4 3
    1 3 8 9 4 7 2 5 6
    6 9 2 3 5 1 8 7 4
    7 4 5 2 8 6 3 1 9 
 */
int main(int argc, const char * argv[]) {
    unsigned int m[SIZE][SIZE]={
        { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
        { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
        { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
        { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
        { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
        { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
        { 0, 0, 5, 2, 0, 6, 3, 0, 0 }
    };

    vector<vector<unsigned int> > matrix;
    for(unsigned int i=0;i<SIZE;i++){
        vector<unsigned int>a(m[i],m[i]+sizeof(m[i])/sizeof(m[i][0]));
        matrix.push_back(a);
    }
    for(unsigned int i=0;i<SIZE;i++){
        for(unsigned int j=0;j<SIZE;j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    unsigned int row=0;
    unsigned int col=0;
    
    if(backtrack(matrix,row,col)){
        for(unsigned int i=0;i<SIZE;i++){
            for(unsigned int j=0;j<SIZE;j++)
                cout<<matrix[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
    else
        cout<< "No solution for the problem"<<endl;
   
    return 0;
}

//Check if a matrix is a solution by checking if it is not empty
//Assigns the first empty slot to row and col
bool is_a_solution(vector<vector<unsigned int> >solution,unsigned int& row,unsigned int& col){
    
    for(unsigned int i=0;i<SIZE;i++){
        for(unsigned int j=0;j<SIZE;j++){
            if(solution[i][j]==UNASSIGNED){
                row=i;
                col=j;
                return false;
            }
        }
    }
    return true;
}

//Construct new candidates to be the next inserted element in the matrix
void construct_candidates(const vector<vector<unsigned int> > matrix,const unsigned int row, const unsigned int col ,vector<unsigned int>&candidates){
    
    unsigned int counter;
    for(counter=1;counter<=SIZE;counter++ ){
        if (
                !   is_in_row(matrix,  counter,  row)   &&
                !   is_in_column(matrix,  counter,  col)&&
                !   is_in_matrix(matrix,row,col,counter)
            )
            candidates.push_back(counter);
    }
    

#if DBG
    cout<< " row  "<< row << " col "<< col<<   endl;
     for(unsigned int i=0;i<SIZE;i++){
               for(unsigned int j=0;j<SIZE;j++)
                   cout<<matrix[i][j]<<" ";
               cout<<endl;
    }
    cout<<endl;
    cout << " Candidates "<< endl;
    for(unsigned int i=0;i<candidates.size();i++){
        cout<< candidates[i]<< endl;
    }
    cout << endl;
    
#endif
        
}

//Row and col are like the k-attempt
bool backtrack(vector<vector<unsigned int> > &matrix,unsigned int& row ,unsigned int &col ){
    vector <unsigned int > candidates;
    unsigned int counter;
    //If we found the solution return
    if (is_a_solution(matrix,row,col)){
        //Like process_solution
        return true;
    }
    unsigned int prev_row=row,prev_col=col;
    
    //if not find new candidates
    construct_candidates(matrix, row, col,candidates);
    
    //for each candidate try (depth first)
    for(counter=0;counter<candidates.size();counter++){
        
        matrix[row][col]=candidates[counter];
        if(backtrack(matrix,row,col))
            return true; //like finished
        //if returns means not a good candidate
        //Resetting all the status
        row=prev_row;
        col=prev_col;
        matrix[row][col]=UNASSIGNED;
        
    }
#if DBG1
    cout<<"No solution for"<<row<< "  "<< col<< endl;
#endif
    return false;
}
                         


