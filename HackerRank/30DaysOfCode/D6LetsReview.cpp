#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

int main() 
{
    std::string str;
    std::getline(std::cin,str);
    int n = std::stoi(str);
    std::vector<std::string> vec(n);

    for(unsigned int i = 0;i<n;i++)
    {   
        std::getline(std::cin,str);
        vec[i] = str;
    }
    for(unsigned int i =0; i<vec.size();i++)
    {
        std::vector<char> even{};
        std::vector<char> odd{};

        for(unsigned int j = 0; j<vec[i].size();j++)
        {
            if(j%2==0) even.emplace_back(vec[i][j]);            
            else odd.emplace_back(vec[i][j]);            
            
        }
         for(unsigned int j = 0;j<even.size();j++)
        {
            std::cout<<even[j];
        }
        std::cout<<" ";
        for(unsigned int j = 0;j<odd.size();j++)
        {
            std::cout<<odd[j];
        }
        std::cout<<"\n";      
    }   
    return 0;
}
