//Sample Outputs 
//9
//3 7 8 5 12 14 21 13 18

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <cmath>
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
float Median(const std::vector<int>& vec)
{
    std::vector<int> vec2 = vec;
    
    std::sort(vec2.begin(), vec2.end());

    int pos= ((vec.size()+1)/2)-1;  

    return ((float)vec2[pos]+ (float)vec2[pos+1]) /2;   
}
void iQr(std::vector<float>& outPut,const std::vector<int>& vec) //Inter Quartile Range
{
    outPut = {};    
    std::vector<float> vec2{};
    outPut.push_back(Median(vec));
    
    if(vec.size() %2==0)
    {

        
        outPut.push_back(Median(vec));
    }
    else
    {

    }
    

    

}

int main() 
{
    int n{};
    std::vector<int> vec{};
    std::string st;
    std::vector<float> outPut{};

    std::cin>>n;
    std::cin.ignore();
    std::getline(std::cin,st);
    ParseStringVector(vec,st);
    
    iQr(outPut,vec);
    
    for(int i=0;i<outPut.size();i++)
    {
           
        std::cout<<std::setprecision(3)<<outPut[i]<<"\n";
    }   
    std::cout<<"\n";
     return 0;
}
