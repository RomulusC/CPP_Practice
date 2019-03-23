/* https://www.hackerrank.com/challenges/s10-the-central-limit-theorem-1/problem

A large elevator can transport a maximum of 9800 pounds. Suppose a load of cargo containing 49 boxes must be transported 
via the elevator. The box weight of this type of cargo follows a distribution with a mean of Mu=205 pounds and a standard 
deviation of sd=15 pounds. Based on this information, what is the probability that all 49 boxes can be safely loaded into the 
freight elevator and transported?
-------------------------------------
Inputs:
9800 -max weight
49   -total boxes
205  -Mu weight of boxes
15   -sd of boxes
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
    
    printf("%.4lf",cdf(weight,mean,std));
    return 0;
}
