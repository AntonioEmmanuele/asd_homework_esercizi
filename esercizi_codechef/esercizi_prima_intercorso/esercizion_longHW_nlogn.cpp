#include <iostream>
#include<vector>
#include <algorithm>
#include<iterator>
#include <map>
using namespace std;

/*
INPUT
8 5 4
1 5 7 3 9 11 0 4
1 1
2 1
3 1
1 3
5 3
*/
/*
OUTPUT
1
2
5
4
-1

*/
//O(nlogn)
int find_idx(vector<int> a, unsigned int i,int R,int M){
    //1
    unsigned int helper=0;
    unsigned int j=0;
   
    //generate a map with array elements as keys and positions as values
    //n
    map<int,unsigned int>k;
    for(unsigned int idx=0;idx<a.size();idx++)
        k[a[idx]]=idx;
    //nlogn
    sort(a.begin(),a.end());
    
    //O(n)
    while(j<a.size() && helper<i){
        if(a[j]%M==R) //1
            helper++; //1
        j++;
    }
    //array are 0 indexed, so +1
    if(helper==i)
        return (k.find(a[j-1])->second+1);
        
    
    return -1;
}

int main() {
	// your code goes here
	unsigned int N;
	unsigned int Q;
	unsigned int M;
	unsigned int i;
	unsigned int R;
	cin>>N;
	vector<int> an(N,0);
	cin>>Q;
	cin>>M;
	//cout<<N <<"  "<<Q<< "   "<< M<< endl;
	for(auto &k:an)
	    cin>>k;
/*	for(auto &k:an)
	    cout<<k;*/
	while(Q>0){
	    cin>>i;
	    cin>>R;
        cout<< find_idx(an,i,R,M)<<endl; 
	    Q--;
	}
	return 0;
}
