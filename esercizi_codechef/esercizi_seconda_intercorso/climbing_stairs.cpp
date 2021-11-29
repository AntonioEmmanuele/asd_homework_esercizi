#include <iostream>
using namespace std;
//1-Sottoproblema : come percorrere gli scalini[:i]
//2-guess:nulla
//3- Scalini[i]=1+scalini[i-1]; for i in range[n,1]
//4- i-> i+1 ecc. non ho cicli
//5- non devo fa nulla
unsigned int num_of_ways(unsigned int n){
    //percorrere uno scalino ci vuole un modo, farne 2 ce ne vuole 3
    unsigned int actual_value=0;
    for(unsigned int i=0;i<n;i++){
        if(i==0)
            actual_value=1;
        else
            actual_value+=1;
    }
    return actual_value;
}
int main() {
	unsigned int test_cases,n;
	cin>>test_cases;
	while(test_cases>0){
	    cin>>n;
	    cout<<num_of_ways(n)<<endl;
	    test_cases--;
	}
	return 0;
}
