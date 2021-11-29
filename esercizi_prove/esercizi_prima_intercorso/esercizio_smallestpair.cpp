#include <iostream>
#include<vector>
#include<algorithm>
#include <iterator>
using namespace std;
/*
    You are given a sequence a1, a2, ..., aN. Find the smallest possible value of ai + aj, where 1 ≤ i < j ≤ N.
    Input:
    1
    4
    5 1 3 4
    Output
    4
    
 */
/*
    should find  statistic of order 1 and 2, just return the minimum
*/
static unsigned int find_min(vector<unsigned int> v, int to_avoid){
   unsigned int k=0;
   unsigned int minimum;
   while(v[k]==to_avoid) //W.c. N
        k++;
    minimum=v[k];
    for(unsigned int i=k+1;i<v.size();i++)
        if(v[i]>minimum &&v[i]!=to_avoid)
            minimum=v[i];
    return minimum;
}

//n log n  +n =(n(logn+1))=O(nlogn)
//Better solution using statistics.
int find_smallest_sum_nlogn(vector<unsigned int> an){
   //nlogn
    sort(an.begin(),an.end());
    if (an.size()>2) //if it has at least 2 elements
        return an[0]+an[1];
    return an[0];
}

//n+n=2n => O(n)
int find_smallest_sum_n(vector<unsigned int> an){
    unsigned int firstMinimum=find_min(an,-1);
    if(an.size()>2)
       return firstMinimum+find_min(an,firstMinimum);
    return firstMinimum;
}

int main() {
	unsigned int tests,N;
	cin>>tests;
	while(tests){
	    cin>>N;
	    vector<unsigned int>an(N,0);
	    for(auto&k:an)
	        cin>>k;
	    cout<<find_smallest_sum_nlogn(an)<<endl;
	    tests--;
	}
	
	return 0;
}
