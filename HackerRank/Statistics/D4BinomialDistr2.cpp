//Exlpaination of the following binomial distribution question 
//b(x,n,p)

//Q1:
//x=[0,1,2]
//b(x,10,0.12) = P(X=0), P(X=1), P(X=2) = 0.891

//Q2:
//x=[2..10];
//b(x,10,0.12) = P(X=2)...P(X=10) = 0.342
//in the code I calculated 1-(P(X=0)+P(X=1))= 0.342

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

auto factorial(const int &_i) {
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
    double i1{},i2{};
    std::cin>>i1>>i2;

    double p = i1/100;
    unsigned int n = i2;
    double answ{};
    for(unsigned int x =0;x<3;x++)
    {
        answ+= (factorial(10)/(factorial(x)*factorial(n-x)))*std::pow(p,x)*std::pow(1-p,n-x); //binomial distribution formula
    }
    printf("%.3lf\n",answ);
    answ = 0;
    for(unsigned int x =0;x<2;x++)
    {
        answ+= (factorial(10)/(factorial(x)*factorial(n-x)))*std::pow(p,x)*std::pow(1-p,n-x); //binomial distribution formula
    }
    answ = 1-answ;
    printf("%.3lf\n",answ);

  return 0;
}
