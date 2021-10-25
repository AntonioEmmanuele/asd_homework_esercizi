#include <iostream>
#include <vector>
#include<algorithm>
#include<iterator>
#include<math.h>

using namespace std;
/*
    Chefina has two sequences A1,A2,…,AN and B1,B2,…,BN.
    She views two sequences with length N as identical if, after they are sorted in non-decreasing order,
    the i-th element of one sequence is equal to the i-th element of the other sequence for each i (1≤i≤N).
    To impress Chefina, Chef wants to make the sequences identical. 
    He may perform the following operation zero or more times: choose two integers i and j (1≤i,j≤N) 
    and swap Ai with Bj. The cost of each such operation is min(Ai,Bj).
    You have to find the minimum total cost with which Chef can make the two sequences identical.
*/
//n^2
int findMinPrice( vector<int>a,  vector<int> b){
    //1
    int min_price=0;
    //Vector of different elements
    //1
    vector<int> different_a;
    vector<int> different_b;
    unsigned int occurrences_a,occurrences_b,idx,j,j1;
    //2nlogn
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
  
    //O(n)   
    for(int i=0;i<a.size();i++) {
        if(a[i]!=b[i] ){ // find the index of different elements
            different_a.push_back(a[i]);  
            different_b.push_back(b[i]);
        }
    }  
    
    //already equal
    //O(1)
    if(different_a.size()==0)
        min_price=0;
    else{
        //Now count the occurrences for each different element
        idx=0;
        //O(n) =n^2
        while(idx<different_a.size()){ 
            occurrences_a=1;
            occurrences_b=1;
            for(int j=idx+1;j<different_a.size();j++){ //n volte
                //cout<<"j is "<< j<<endl;  
                if(different_a[j]==different_a[j-1])
                    occurrences_a++;
                if(different_b[j]==different_b[j-1])
                    occurrences_b++;
            }
            //cout<< "occurrences a " <<occurrences_a<<"occurrences b"<<occurrences_b<<endl;
            if(occurrences_a%2==0 && occurrences_b %2==0&& occurrences_b==occurrences_a){
                min_price+=min(different_a[idx],different_b[idx])*occurrences_a/2;
                idx+=occurrences_a;
            }
            else{
                min_price=-1;
                break;
            }
        }
    }
    return min_price;
}
/*
INPUT
3
1
1
2
2
1 2
2 1
2
1 1
2 2
OUTPUT
-1
0
1
*/
int main() {
    unsigned int num_tests;
    unsigned int vector_size;
    cin>>num_tests;
    while(num_tests>0){
        cin>>vector_size;
        vector<int> a(vector_size,0);
        vector<int> b(vector_size,0);
        for(auto &k:a)
            cin>>k;
        for(auto &k:b)
            cin>>k;
        cout<<findMinPrice(a,b)<<endl;
        num_tests--;    
    }
	return 0;
}
