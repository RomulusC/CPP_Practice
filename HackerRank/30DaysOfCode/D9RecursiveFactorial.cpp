#include <iostream>

// Complete the factorial function below.
int factorial(int n) 
{    
    if(n<=1) return 1;
    else
    {
        return n * factorial(n-1);
    }
}

int main()
{
    int n;
    std::cin >> n;   

    int result = factorial(n);

    std::cout<<result;

    return 0;
}
