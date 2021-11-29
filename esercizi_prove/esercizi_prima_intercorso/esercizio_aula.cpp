#include <iostream>
#include <vector>
#include<algorithm>
#include <iterator>
using namespace std;
/*
    Chef has a sequence A1,A2,…,AN
    This sequence has exactly 2N
    subsequences. Chef considers a subsequence of A
    interesting if its size is exactly K
    and the sum of all its elements is minimum possible, i.e. there is no subsequence with size K
    which has a smaller sum.
    Help Chef find the number of interesting subsequences of the sequence of A.
*/

static unsigned int factorial(unsigned int n) 
{
    if (n == 0)
       return 1;
    return n * factorial(n - 1);
}

/*
    INPUT
    4
    2 4
    4 3 2 1
    2 7
    6 5 2 3 2 2 1
    3 7
    6 3 2 3 2 2 1
    3 7
    6 4 4 3 3 2 1
    
    OUTPUT
    1
    3
    3
    2
*/
//n log n+O(n)
uint32_t find_minimum_subsequence(vector<int> vec,uint32_t k){
    // declare the num of sequences, costant 1
    uint32_t count_Z=0;
    uint32_t count_Y=0;
    vector<int>::iterator iterator =vec.begin()+k;
    //randomized quicksort, Theta(nlogn) expected value,n^2 worst
    sort(vec.begin(),vec.end());
    for (vector<int>::iterator it=vec.begin();it!=iterator;++it)
          if(*it==vec[k-1])
             count_Y++;
    //cout<<count_Y<<endl;
    //trova le occorrenze dell'ultimo elemento nel vettore
    while(iterator!=vec.end()){
      if(*iterator==vec[k-1]){
          count_Z++;
          iterator++;
      }
      else 
        break;
    }
    //return 0;
    count_Z=count_Z+count_Y;
    return factorial(count_Z)/(factorial(count_Y)*factorial(count_Z-count_Y));
}
#define N 1
#define K 0
int main() {
    
    uint32_t num_of_tests=0;
    vector<uint32_t> second_line(2,0); 

    cin>> num_of_tests;
    uint32_t seq_num;
    while(num_of_tests>0){
        
        //Take N and K
        for(auto &s : second_line)
            cin>>s;

        //Take the vector
        
        vector<int> to_test(second_line[N],0);
        
        for(auto &m:to_test)
            cin >> m;
        
        seq_num=find_minimum_subsequence(to_test,second_line[K]);
        
        cout<<seq_num<<endl;
        num_of_tests--;
    }
	return 0;
}
