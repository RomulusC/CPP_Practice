/* https://www.hackerrank.com/challenges/s10-basic-statistics/problem
Sample input
"10"                                                         = input count
"64630 11735 14216 99233 14470 4978 73429 38120 51135 67060" = inputs
-------------------------------------------------------------------------
Sample output:
"43900.6"  - mean
"44627.5"  - median
"4978"     - mode
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <map>


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
float Mean(const std::vector<int>& vec)
{
    float x{};
    for(int i =0; i<vec.size();i++)
    {
        x+=vec[i];
    }
   
    x = x/vec.size();
    
    return x;
}
float Median(const std::vector<int>& vec)
{
    std::vector<int> vec2 = vec;
    
    std::sort(vec2.begin(), vec2.end());

    int pos= ((vec.size()+1)/2)-1;  

    return ((float)vec2[pos]+ (float)vec2[pos+1]) /2;   
}
int Mode(const std::vector<int>& vec)
{
    std::map<int,int> x{};
    
    for( int i=0;i<vec.size();i++)
    {
        x[vec[i]]++;
    }
    int output{};

    int max = -1;
    int maxKey{};

for (std::map<int, int>::const_iterator it = x.begin(); it != x.end(); ++it) 
{
   if (it->second > max) 
   {
       maxKey = it->first;
       max = it->second;
       
   }
}
    return maxKey;
}

int main() 
{
    
    std::string N_string{};
    std::string i_string{};
    int n{};
    std::vector<int> vec{};

    std::cin>>N_string;   
    std::cin.ignore();
    std::getline(std::cin, i_string);

    n = stoi(N_string);    
    
    ParseStringVector(vec,i_string);
    
    std::cout<<Mean(vec)<<"\n";
    std::cout<<Median(vec)<<"\n";
    std::cout<<Mode(vec);
   
    return 0;
}
