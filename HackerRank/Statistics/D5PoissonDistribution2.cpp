/* https://www.hackerrank.com/challenges/s10-poisson-distribution-2/problem
Explaination:
Assuming that the time it takes to repair a machine is negligible (meaning that a machine takes an insignificant time to repair and it can be broken multiple times a day),
calculate the cost of repairs if we were to keep the machine running infinately.
E(X) is the expected outcome and X is the poisson probability, also known as variance; 
X = Poisson random variable probability for first machine = 0.88
Y = Poisson random variable probability for second machine = 1.55 
Cost of A:
Ca = 160 + 40X^2
Cost of B:
Cb = 128 + 40Y^2
The calculation requires us to calculate the Expectation of Poisson probability squared; E[X^2] and E[Y^2]
Ca = 160 + 40E[X^2]
Cb = 128 + 40E[Y^2]

The Expectation E[X] = Variance of X; or E[X] = Var[X] = X;
However E[X^2] != X^2 && Var[x]^2;

A formula for calculating E[X^2]:
Var[X] = E[X^2] - (E[X])^2
Rearranged:
E[X^2] = Var[X]+(E[X])^2

Continued:
X = Var(X) = 0.88
The expected outcome for Var(X) = E(X) means 88% of the time on any given day the machine will break down
The expected outcome for Var(X)^2 = E(X^2) means that 165% of the time on any given day the machine will break down
You are trying to find the probability if the probability was to be more likely squared
EG: You are 0.5 likely to win the lottery. If my luck was improved by squared exponent, id have an Expected outcome of 0.75
X^2 < X - as all probabilities are <1 - therefore squaring the variance and taking it as the expected outcome only lowers the expected outcome  
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() 
{
    double i1{},i2{};
    std::cin>>i1>>i2;
    i1 = 160 + (40*(i1+(i1*i1)));
    i2 = 128 + (40*(i2+(i2*i2)));
    printf("%.3lf\n%.3lf",i1,i2);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
