#include<iostream>
#include<vector>
using namespace std;

long long gcd(long long n1,long long n2)                         // calculating gcd using eucledian's formula
{
    if(n2==0)
     return n1;
    return gcd(n2,n1%n2);
}
long long lcm(long long n1,long long n2)
{                                              //caculating lcm using the formula: lcm x gcd = n1 x n2
  long long gc,lc;
  gc=gcd(n1,n2);
  lc=n1*n2/gc;
  return lc;
}
int main()
{
  long long x,cd,i,p,r,n;
  long long cnt,flag;                                  // we use this to count the max checks, we can keep it as much as we want
  vector<long long> pr,rem;
  cin>>n;                                     // number of inputs 
  for(i=0;i<n;i++) 
  { cin>>p>>r; 
    pr.push_back(p); 
    rem.push_back(r); 
  }
  x=rem[0];                                   // let us say the first number will be the starting and 
  cd= pr[0];                               // the first remainder will be the common difference like we saw in the example
  for(i=1;i<n;i++)
  {   cnt=0;
      flag=0;
      while(cnt<100000)                      // Here we have taken a max value for 10^5 because we are dealing with large numbers
      {
          if(x%pr[i]==rem[i])                // condition for finding the next start value
           {  flag=1;
              break;
           }
          x=x+cd;
      }
      if(flag==0)                           // This means that no number until cnt range has matched the condition.
       {
           cout<<"No solution.";            // Hence no solution is possible
           return 0;
       }
      cd=lcm(pr[i],cd);                      // updating the cd
  }
  cout<<x<<" "<<cd;
  return 0;
}