/* https://www.hackerrank.com/challenges/s10-normal-distribution-2/problem

Mu = 70
sd = 10

Q1.Scored higher than 80 : >80
Q2.Passed the test: >=60
Q3.Failed the test: <60
*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  double mean{};
  double std{};
  std::vector<double> x(2);
  std::cin >> mean >> std >> x[0] >> x[1];

  auto cdf = [&](double x,double Mu, double sd){return 0.5 * (1 + erf((x - Mu) / (sd * sqrt(2))));};

  printf("%.2lf\n", ((1 - cdf(x[0],mean,std)) * 100));
  printf("%.2lf\n", ((1 - cdf(x[1],mean,std)) * 100));
  printf("%.2lf\n", ((cdf(x[1],mean,std)) * 100));
  return 0;
}
