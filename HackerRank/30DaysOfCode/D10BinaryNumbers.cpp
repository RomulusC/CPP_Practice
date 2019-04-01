#include <iostream>
#include <cmath>
#include <string>
#include <vector>


int main()
{
    float n;
    std::cin >> n;
    std::vector<bool> vec{};
    while(n>0)
    {
        n = n/2;
        if(std::floor(n)!=n)
        {
            n = std::floor(n);
            vec.insert(vec.begin(),true);
        }
        else vec.insert(vec.begin(),false);        
    }   

/*  for(int i=0; i<vec.size();i++)
    {
        std::cout<<vec[i];
    }
    std::cout<<"\n";
*/

    int count=0;
    int t_count=0;
    for(int i=0; i<vec.size();i++)
    {
        if(vec[i]==true) t_count++;
        else 
        {
            if(t_count>count) count = t_count;
            t_count=0;
        }        
    }
    if(t_count>count) count = t_count;
    std::cout<<count<<"\n";

    return 0;
}
