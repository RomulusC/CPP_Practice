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
void iQr(std::vector<float>& outPut,const std::vector<int>& vec) //Inter Quartile Range
{
    outPut = {};
    
    std::vector<int> vec2 = vec;
    std::sort(vec2.begin(), vec2.end());

    if(vec2.size() % 2 !=0) //Q3 if N is odd
    {
       if((vec2.size()-1)%4 ==0)
       {
           
            outPut.emplace_back((vec2[((vec2.size()-1)/4)-1]+ vec2[((vec2.size()-1)/4)]) /2);
            outPut.emplace_back(vec2[((vec2.size()+1)/2)-1]);
            outPut.emplace_back(((vec2[((vec2.size()-1)/4)-1+((vec2.size()+1)/2)])+   (vec2[((vec2.size()-1)/4)-1+((vec2.size()+1)/2)+1])) /2 );

           
       } 
       else
       {
            
            outPut.emplace_back(vec2[((vec2.size()+1)/4)-1]);
            outPut.emplace_back(vec2[((vec2.size()+1)/2)-1]);
            outPut.emplace_back(vec2[(vec.size()+1)-((vec2.size()+1)/4)-1]);
       }
       
              
    }
    else //Q3 if N is even
    {
        outPut.emplace_back(vec2[std::ceil(vec2.size()/4)]);
        outPut.emplace_back((float)(vec2[(vec2.size()/2)-1] + vec2[(vec2.size()/2)])  /2 );

        outPut.emplace_back(vec2[std::ceil(vec2.size()/4)+(vec2.size()/2)]);
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
