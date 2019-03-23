/* https://www.hackerrank.com/challenges/s10-the-central-limit-theorem-1/problem

Mu = 70
sd = 10

*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() 
{    
    double weight{};
    double mean{};
    double std{};
    double n{};
    std::cin>>weight>>n>>mean>>std;
    mean = mean *n;
    std = std *sqrt(n);
    
    
    auto cdf = [&](double x,double Mu, double sd){return 0.5 * (1 + erf((x - Mu) / (sd * sqrt(2))));};
    
    printf("%.2lf",cdf(weight,mean,std));
    return 0;
}
