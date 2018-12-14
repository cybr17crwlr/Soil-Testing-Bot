#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<string>
//#include <boost/math/common_factor.hpp>
#define ll long long int
#define loop(i,n) for(i=0;i<n;i++)
#define loop1(i,s,e) for(i=s;i<=e;i++)
#define io std::ios::sync_with_stdio(false);cin.tie(NULL);
#define mod 1000000007
#define pb push_back
#define mkp make_pair
#define pii pair<ll,ll>
using namespace std;
#define MAX 100001
#define INF 1000000000000000
int main()
{  char ch;
  cout<<"Enter the input of soil testing"<<endl;
  double n1,p1,k1;         //in lbs/ft2
  cin>>n1>>p1>>k1                                      //Actuall soil testing input
  cout<<"Enter U to put the inputs of crop requirement"<<endl;
  cout<<"Enter X,Y or Z for respective crops"<<endl; 
  cin>>ch;
  

  double n,p,k;       //it is soil npk required for particular in lbs/ft2
  if(ch=='U')cin>>n>>p>>k;
  if(ch=='X')n=,p=,k=;
  if(ch=='Y')n=,p=,k=;     //SOIL N,P,K 
  if(ch=='Z')n=,p=,k=; 
  n-=n1;
  p-=p1;
  k-=k1; 
  if(n<0){
    cout<<"No need of fertiliser as N is in excess amount"<<endl;
    return 0;
  }
//// rounding and the data to 3 decimal places

  n=round(n*1000)/1000;
  p=round(p*1000)/1000;
  k=round(k*1000)/1000;
 
 // cout<<n<<p<<k;

////LCM of three number

  int N,P,K,LCM,a,b,c;  //they are the simplest ratio
   N=n*1000;
   P=p*1000;
   K=k*1000;   
   a=__gcd(N,P);
   b=__gcd(N,K);
   c=__gcd(K,P);
   LCM=min(a,b);
   LCM=min(LCM,c);
  
  // cout<<LCM<<endl;


////Getting the ratios

   N/=LCM;
   P/=LCM;
   K/=LCM;

  //cout<<N<<P<<K;

////  2  best fit
   int num,pos=0;
   cin>>num;
   double an[num],ap[num],ak[num],sum[num],an1,ap1,ak1;
   double least=100000000;
   for (int i = 0; i < num; ++i)
   {
     cin>>an[i]>>ap[i]>>ak[i];
    sum[i]=abs(ap[i]-an[i]*P/N)+abs(ap[i]-an[i]*K/N);    //N is essential element and thus it is fitted 
     if(least>sum[i]){                                   //properly and rest are adjusted.
        least=sum[i];
        pos=i+1;
     }
   }
    cout<<pos<<endl;//showing the no. of the fertiliser to use

  an1=an[pos-1];
  ap1=ap[pos-1];
  ak1=ak[pos-1];
  

//// PART 3  FERTILIZER RATE

  double F;
  F=n*100/an1;
  //cout<<F<<endl;
  
 //cout<<F<<endl;
////4 area
  double l,w,area;
  cin>>l>>w;
  area=l*w/100;  //as fertiliser is per 100 ft2 so /100   

////5 total
  double T;
  T=F*area;
  
cout<<T<<"lbs"<<endl;
////6 TOTAL NO OF CUPS
  double C;
  C=T*2;
  //cout<<C<<endl;
   return 0; 


}