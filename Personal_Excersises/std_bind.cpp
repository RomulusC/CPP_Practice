#include <iostream>
#include <functional>

void Print(const int& i,const int& j)
{
    std::cout<<i<<"\n"<<j<<"\n";
}


int main()
{
    const auto f = std::bind(&Print,  std::placeholders::_1, std::placeholders::_2);

    f(123,345);

    return 0;
}