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
static unsigned int partition(vector<int>&a,unsigned int start,unsigned int end){
    int i=-1;
    //put elements ,<= a[n] to left
    for(int j=0;j<end-1;j++){
        if(a[j]<=a[end-1]){
            i++;
            swap(a[i],a[j]);
        }
    }
    //correct idx for last is i+1
    //cout <<"i is "<<i<<a[end-1]<<endl;
    swap(a[i+1],a[end-1]);
    return i+1;
}

unsigned int  randomized_partition(vector<int> &a,unsigned int start,unsigned int end){
    unsigned int random_idx=rand()%(end-start)+start;
    //cout<<"Random number"<<random_idx<<endl;
    swap(a[random_idx],a[end-1]);
    return partition(a,start,end);
}

// returns the order statistic i
int select(vector<int> a,unsigned int start,unsigned int end,int i){
    if(start==end)
        return a[start];
    unsigned int q=randomized_partition(a,start,end);
    unsigned int k=q-start+1;
    if(k==i)
        return a[q];
    else if(k>i)
        return select(a,start,q-1,i);
    else
        return select(a,q+1,end,i-k);
}
//O(nlogn)
int find_idx(vector<int> a, unsigned int i,int R,int M){
    //1
    unsigned int helper=0;
    unsigned int j=0;
    vector<int> helper_vec;
    int element;
    //O(n)
    for(auto k:a)
        if(k%M==R)
            helper_vec.push_back(k);
            
    if(helper_vec.size()<i)
        return -1;
    else{
        //n
        element=select(helper_vec,0,helper_vec.size(),i);
        //find the element position in the original array
        for(unsigned int k=0;k<a.size();k++)
            if(a[k]==element)
                return k+1;
    }
        
    return -1;
}

int main() {
    srand(time(NULL));
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
	//cout<<select(an,0,an.size(),8)<<endl;
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
