#include<iostream>
#include<string>
#include<vector>
using namespace std;
unsigned int mn(unsigned int a, unsigned int b, unsigned int c ){
  if(a>b)
    return (b>c)?c:b;
  else
    return (a>c)?c:a;
}
unsigned int edit_distance(vector<vector< int> > &dp,string s1, unsigned int i, string s2,unsigned int j ){
  if(i>=s1.size() || j>=s2.size())
    return 0;
  if(dp[i][j]!=-1)
    return dp[i][j];
  if(s1[i]==s2[j])//Se sono uguali aumenta.
    dp[i][j]=edit_distance(dp,s1,i+1,s2,j+1);
  else
    dp[i][j]=1+mn(
      edit_distance(dp,s1,i+1,s2,j+1), //Cambiali
      edit_distance(dp,s1,i+1,s2,j), //Rimuovi i
      edit_distance(dp,s1,i,s2,j+1) //Inserisci j
    );
  return dp[i][j];
}
int main(){
  //Minimo numero di mosse con cui rendere due lettere uguali
  string s1="geek";
  string s2="gessek";
  vector<vector<int> >dp(s1.size(),vector<int> (s2.size(),-1));
  cout<<edit_distance(dp,s1,0,s2,0)<<endl;
  string s3="sunday";
  string s4="saturday";
  vector<vector<int> >dp1(s3.size(),vector<int> (s4.size(),-1));
  cout<<edit_distance(dp1,s3,0,s4,0)<<endl;
  return 0;
}
