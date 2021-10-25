#include <iostream>
#include<vector>
#include<algorithm>
#include <iterator>
using namespace std;
/*
    Snackdown 2019 is coming!
    There are two rounds (round A and round B) after the qualification round. 
    From both of them, teams can qualify to the pre-elimination round. 
    According to the rules, in each of these two rounds,
    teams are sorted in descending order by their score and each team with a score greater or 
    equal to the score of the team at the K=1500-th place advances to the pre-elimination round 
    (this means it is possible to have more than K qualified teams from each round in the case 
    of one or more ties after the K-th place).
    Today, the organizers ask you to count the number of teams which 
    would qualify for the pre-elimination round from round A for a given value of 
    K  (possibly different from 1500). They provided the scores of all teams to you; you should ensure that all teams scoring at least as many points as the K-th team qualify.

    Input
    The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
    The first line of each test case contains two space-separated integers N and K.
    The second line contains N space-separated integers S1,S2,…,SN.
    Output
    For each test case, print a single line containing one integer — the number of qualified teams.
    
    Example Input
    2
    5 1
    3 5 2 4 5
    6 4
    6 5 4 3 2 1
    Example Output
    2
    4

*/

//n log n  +n =(n(logn+1))=O(nlogn)
//Better solution using statistics.
int execute_with_sorting(vector<unsigned int> score, int K){
    unsigned int count=0;
    unsigned int i=1;
    unsigned int score_size=score.size();
    int position=K-1;
    if(position>score_size-1)
        return -1;
    //Sort the array in descending order
    //n log n
    sort(score.begin(),score.end(),greater<int>());

    //Possible improvement: Number of element is given by (K-1)+1+num of repeated elements
    //i.e. in the first array we have: num of repeated(5)+K= 1+1
    for(unsigned int  i=0;i<score.size();i++) //n
        if(score[i]>=score[K-1]){
            count++;
    }
    return count;

}

int main() {
	unsigned int tests,N,K;
	cin>>tests;
	while(tests){
	    cin>>N;
	    cin>>K;
	    vector<unsigned int>score(N,0);
	    for(auto&k:score)
	        cin>>k;
	    cout<<execute_with_sorting(score,K)<<endl;
	    tests--;
	}
	
	return 0;
}
