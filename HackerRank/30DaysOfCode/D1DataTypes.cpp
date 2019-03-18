//Sample Input
//12
//4.0
//is the best place to learn and practice coding!

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

int main() 
{
    int i = 4;
    double d = 4.0;
    std::string s = "HackerRank ";


    int x{};
    double y{};
    std::string st{};

    
    std::cin>>st; 
    std::cin.ignore();
    x = stoi(st);

    std::cin>>st; 
    std::cin.ignore();
    y = stod(st);

    std::getline(std::cin,st);

    std::cout<<i+x<<"\n";

    std::cout << std::fixed<<std::setprecision(1) << (d + y) << "\n";

    std::cout<<s+st<<"\n"; 

    return 0;
}