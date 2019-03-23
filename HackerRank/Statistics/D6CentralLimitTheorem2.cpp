/* https://www.hackerrank.com/challenges/s10-the-central-limit-theorem-2/problem

Mu' = n*Mu;
sd' = sqrt(n)*sd;


Mu = 2.4
sd = 2
n=100
x=250

*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() 
{
    double x1 = 250;
    double n  = 100;
    double mean = 2.4*n; //=Mu'
    double sdt = 2*sqrt(n); //Sd'

    auto cdf = [&](double x,double Mu, double sd){return 0.5 * (1 + erf((x - Mu) / (sd * sqrt(2))));};
    printf("%.4lf",cdf(x1,mean,sdt));
    return 0;
}
