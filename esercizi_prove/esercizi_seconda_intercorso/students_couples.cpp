#include <iostream>
#include<string>
using namespace std;
/*
    There are N students standing in a row and numbered 1 through N from left to right.
    You are given a string S with length N, where for each valid i, the i-th character of S is 'x' 
    if the i-th student is a girl or 'y'
    if this student is a boy. Students standing next to each other in the row are friends.

    The students are asked to form pairs for a dance competition. 
    Each pair must consist of a boy and a girl. Two students can only form a pair if they are friends.
    Each student can only be part of at most one pair. What is the maximum number of pairs that can
    be formed?
    */
    /*
    in
    The first line of the input contains a single integer T denoting the number of test cases.
    The description of T test cases follows.
    The first and only line of each test case contains a single string S.
    Sample in
    3
    xy
    xyxxy
    yy
    out
    For each test case, print a single line containing one integer ― 
    the maximum number of pairs.
    Sample out
    1
    2
    0
*/
    
//Bottom Up
//Theta(n)
unsigned int find_couples(string students){
    unsigned int count=0,stud_len=students.length();
    unsigned int next;
    for(unsigned int idx=0;idx<stud_len;idx++){
        next=idx+1;
        if(next< stud_len){
            if((students[idx]=='x' &&students[next]=='y')|| (students[idx]=='y' &&students[next])=='x')
            count++;
        }
    }
    return count;
}
int main() {
	unsigned int tests,len,i;
	string k;
	cin>>tests;
	while(tests>0){
	    cin>>k;
	    cout<<find_couples(k)<<endl;
	    tests--;
	}
	return 0;
}
