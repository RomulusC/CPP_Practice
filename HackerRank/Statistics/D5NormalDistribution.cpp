/* https://www.hackerrank.com/challenges/s10-normal-distribution-1/problem
The integral with limits 0->X from a standard deviation function gives the area of probability of an outcome.

Normal Distribution function f(X) = e^(-x^2)
Cant integrate this.

We use the Cumulative distribution function
Which uses the "error function" <cmath> has this function as erf

Mu = 20;
sd = 2;

Find probability if 0<X<19.5;
Find Probability if 20<X<22;

i1 = 20   = Mu(mean,median,mode: all same value)
i2 = 2    = standard deviation
i3 = 19.5 = find area between 0-19.5
i4 = 20   = x1
i5 = 22   = x2 : find area between x1,x2 
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() 
{    
    double mean{};
    double std{};
    std::vector<double> x(3);
    std::cin>>mean>>std>>x[0]>>x[1]>>x[2];
    
    auto cdf = [&](double x){return 0.5 * (1 + erf((x - mean) / (std * sqrt(2))));};
    
    printf("%.3lf\n",cdf(x[0]));
    printf("%.3lf\n",(abs(cdf(x[1])-cdf(x[2]))));   
    return 0;
}
