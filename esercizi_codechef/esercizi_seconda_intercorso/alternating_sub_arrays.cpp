#include <iostream>
#include <vector>

/*
codechef.com/problems/ALTARAY
*/

using namespace std;
//Time: Theta(n)= n-i sottoproblemi con tempo i=Theta(n-1), se eseguo per i max allora ho 
//1 sottoproblema con tempo theta di n altrimenti è vero il viceversa
void calc_sub_arrays(vector <int> array, vector<unsigned int> &occurrences,unsigned int &idx){
    unsigned int prev=idx-1;
    while(idx>0){
        if(array[idx]>0 && array[prev]<=0 || array[idx]<0 && array[prev]>=0){
            occurrences[prev]+=occurrences[idx];
            prev--;
            idx--;
        }
        else{
            idx--;
            break;
        }
    }
    if(idx>0)
        calc_sub_arrays(array,occurrences,idx);
}

int main() {
    unsigned int tests,array_size,i;
    cin>>tests;
    while(tests>0){
        cin>>array_size;
        vector<int> array(array_size,0);
        for(i=0;i<array_size;i++)
            cin>>array[i];
       vector<unsigned int > alternating_sub_arrays(array_size,1);
       i=array_size-1;
       calc_sub_arrays(array,alternating_sub_arrays,i);
       for(i=0;i<array_size;i++)
            cout<<alternating_sub_arrays[i]<< " ";
        cout<<endl;
        tests--;
    }
	return 0;
}
