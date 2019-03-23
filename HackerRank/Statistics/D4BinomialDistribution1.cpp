//Exlpaination of the following binomial distribution question  
//b(x,n,p)

//Q1:
//x=[3,4,5,6]
//p=1.09/(1.09+1)
//b(x,6,p) = P(X=3)...P(X=6) = 0.696

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

int main() {
  double i1, i2;
  std::cin >> i1 >> i2;

  int x, n;
  double p, q;
  x = 3;
  n = 6;
  p = i1 / (i1 + i2); 
  q = 1 - p;

  double answ = 0;
  for (int i = x; i <= n; i++) {
    double c = factorial(n) / ((factorial(i) * factorial(n - i)));
    double answ1 = c * std::pow(p, i) * std::pow(q, n - i);
    answ += answ1;
  }
  int answi = std::round(answ * 1000);
  answ = (double)answi / 1000;

  printf("%.3lf",answ);
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  return 0;
}
