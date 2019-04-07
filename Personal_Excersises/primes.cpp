#include <iostream>
#include <vector>
#include <cmath>
//Calculate the sum of all primes up to 2 million
int main()
{
   size_t answ=0;
   const size_t n = 2000000;
   std::vector<bool> vec(n+1,true);
   vec[0]=false;
   vec[1]=false;
  
   for(size_t i =2;i<=std::floor(std::sqrt(n));i++)
   {       
       if(vec[i]==true)
       {           
           int m = 0;
           for(size_t j=std::pow(i,2);j<=n;j=std::pow(i,2)+(m*i))
           {
               vec[j]=false;
               m++;
           }
       }
   }
   ///////////////////////////////////////////////////////////////////////////
   for(size_t i =0;i<vec.size();i++)
   {
       if(vec[i]==true)
       {
         answ +=i;         
       }      
   }  

   std::cout<<answ<<"\n";

    return 0;
}