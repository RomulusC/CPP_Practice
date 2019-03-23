/* https://www.hackerrank.com/challenges/s10-poisson-distribution-1/problem
Poisson Distribution = P(k,lmda) = (lmda^K * e^(-lmda)) / K!

A random variable, , follows Poisson distribution with mean of 2.5. Find the probability with which the random variable X is equal to 5.
P(5,2.5) = 0.067
 
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
auto Factorial(const int &_i) {
  if (_i == 0)
    return 1;
  int answ = _i;
  for (int i = _i - 1; i > 0; i--) {
    answ *= i;
  }
  return answ;
}
int main() 
{
    double e = 2.71828;
    double lmda{},K{};
    std::cin>>lmda>>K;
    
    double answ = ((std::pow(lmda,K))*std::pow(e,-lmda))/Factorial(K);
    std::cout<<answ;
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
