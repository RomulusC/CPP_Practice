//Sample Input
//5
//10 40 30 50 20
//1 2 3 4 5

#include <vector>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <iomanip>


void ParseStringVector(std::vector<int>& _vector, const std::string& _string)
{
    std::istringstream iss(_string);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());

    for(int i=0;i<results.size();i++)
    {
        
        _vector.emplace_back(stoi(results[i]));
    }    

}
float WeightedSum(std::vector<int>& x, std::vector<int>& w)
{
   
    if(x.size()!=w.size()) return 0;
    
    float numerator{};
    float denominator{};

    for(int i=0;i<x.size();i++)
    {
        numerator+=w[i]*x[i];
    }
    for(int i=0;i<x.size();i++)
    {
        denominator+=w[i];
    }



    return numerator/denominator;
}

int main() 
{
    int n{};
    std::vector<int> x;
    std::vector<int> w;
    std::string input{};

    std::cin>>input;    
    n = std::stoi(input);

    std::cin.ignore();
    std::getline(std::cin,input);    
    ParseStringVector(x,input);
    
    
    std::getline(std::cin,input);    
    ParseStringVector(w,input);
    
    std::cout<< std::fixed<<std::setprecision(1)<<WeightedSum(x,w); 

    
    return 0;
}
