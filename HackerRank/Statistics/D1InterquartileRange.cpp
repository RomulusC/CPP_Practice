//Sample Outputs 
//6
//6 12 8 10 20 16
//5 4 3 2 1 5

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
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

template <typename  T>
T Interporlation(T& x, T& y) 
{

    return ((x+y)/2);      
}

template <typename  T>
T Median(const std::vector<T>& vec)
{
    std::vector<T> vec2 = vec;    
    std::sort(vec2.begin(), vec2.end());

    if(vec2.size() % 2 == 0) return Interporlation(vec2[(int)vec2.size()/2],vec2[((int)vec2.size()/2)-1]);

    else return vec2[std::ceil(vec2.size()/2)];         
}

void iQr(std::vector<float>& outPut,const std::vector<int>& vec) //Inter Quartile Range
{
    outPut = std::vector<float>(3,0);    
    std::vector<float> vec2{};
    std::vector<float> vecL{};
    std::vector<float> vecU{};

    for(auto x : vec)
    {
        vec2.emplace_back(x);
    }
    std::sort(vec2.begin(),vec2.end());

    if(vec2.size() % 2 == 0)
    {
        for(int i =0;i<vec2.size();i++)
        {
            if(i<vec2.size()/2) vecL.emplace_back(vec2[i]);
            else vecU.emplace_back(vec2[i]);            
        }       
    }

    else
    {
        for(int i =0;i<vec2.size();i++)
        {            
            if(i<vec2.size()/2) vecL.emplace_back(vec2[i]);

            else if(i>vec2.size()/2) vecU.emplace_back(vec2[i]);             
        }               
    }

    outPut[0]=(Median(vecL));
    outPut[1]=(Median(vec2));
    outPut[2]=(Median(vecU));  
        
}

int main() 
{
    int n{};
    std::vector<int> elem{};
    std::vector<int> freq{};
    std::vector<int> vec{};
    std::string st;
    std::vector<float> outPut{};

    std::cin>>n;
    std::cin.ignore();

    std::getline(std::cin,st);
    ParseStringVector(elem,st);

    std::getline(std::cin,st);
    ParseStringVector(freq,st);
    
   for(int i =0; i<elem.size();i++)
   {
      for(int j=0;j<freq[i];j++)
      {
        vec.emplace_back(elem[i]);
      }
   }
    
    iQr(outPut,vec);   

    std::cout<<std::fixed<<std::setprecision(1)<<outPut[2]-outPut[0]<<"\n";

   
     return 0;
}
