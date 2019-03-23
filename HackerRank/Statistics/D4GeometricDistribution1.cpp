/* https://www.hackerrank.com/challenges/s10-geometric-distribution-1/problem
Explaination of the following Geometric Distribution
g(n,p)

n=5, p=1/3, q = 1-p

g(5,0.33) = q^(n-1) * p = 0.066;

Probability of first success on the 5th attempt = 0.066
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>



int main() 
{
    int i1{},i2{},n;
    std::cin>>i1>>i2>>n;
    double p = (double)i1/(double)i2;
    
    double answ = (std::pow(1-p,n-1)*(p));
    
    printf("%.3lf",answ);

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
