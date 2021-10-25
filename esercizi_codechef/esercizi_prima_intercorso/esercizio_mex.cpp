#include <iostream>
#include<vector>
#include <algorithm>
#include<iterator>

using namespace std;
//nlogn+n
unsigned int find_mex( vector<unsigned int>array){
    //nlogn
    sort(array.begin(),array.end());
    //n
    for(int i=0;i<array.size();i++)
        if(i!=array[i])
            return i;
    return array.back()+1;
}
//(k+1)nlogn
unsigned int execute_algo(vector<unsigned int> array, unsigned int K){
    //k*nlogn
    while(K>0){
        array.push_back(find_mex(array));
        K--;
    }
    //nlogn
    return find_mex(array);
}
/*
    INPUT
    4
    3 0
    1 0 2
    3 1
    1 0 2
    4 3
    2 5 4 9
    2 0
    3 4
    OUTPUT
    3
    4
    6
    0
*/



int main() {
	unsigned int tests;
    unsigned int N,K;
    cin>>tests;
    while(tests>0){
        cin>>N;
        cin>>K;
        vector<unsigned int> a(N,0);
        for(auto &k:a)
            cin>>k;
       // cout<<find_mex(a)<<endl;
        cout<<execute_algo(a,K)<<endl;
        tests--;
    }
	return 0;
}
