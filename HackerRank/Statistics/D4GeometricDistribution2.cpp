/* https://www.hackerrank.com/challenges/s10-geometric-distribution-2/problem
Explaination of the following Geometric Distribution
g(n,p)

n=[5,4,3,2,1] p=1/3, q = 1-p

g(n,0.33) = q^(n-1) * p = 0.066;

Probability that the 1st defect is found during the first 5 inspections = 0.868
*/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

int main() {
  int i1{}, i2{}, n;
  std::cin >> i1 >> i2 >> n;
  double p = (double)i1 / (double)i2;

    double answ = 0;
    for(int i =n;i>0;i--)
    {
        answ += (std::pow(1 - p, i - 1) * (p));

    }

  

  printf("%.3lf", answ);

  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  return 0;
}
