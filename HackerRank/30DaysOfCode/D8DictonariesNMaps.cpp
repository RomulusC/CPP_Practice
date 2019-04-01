#include <string>
#include <iostream>
#include <map>

int main() 
{
    std::map<std::string,unsigned int> map{};
    unsigned int n{};
    unsigned int i_num{};
    std::string i_string{};
    scanf("%i",&n);    
    

    for(unsigned int i =0;i<n;i++ )
    {
        i_string ="";
        i_num = 0;
        std::cin>>i_string>>i_num;        
        if(i_string!=""&&i_num!=0) map.insert(std::pair<std::string,unsigned int>(i_string,i_num));                      
    }

    for(unsigned int i=0; i<n;i++)
    {
        i_string="";
        std::cin>>i_string;
        if(i_string!="")
        {
            auto it = map.find(i_string);
            if(it!=map.end())std::cout<<it->first<<"="<<it->second<<"\n";
            else std::cout<<"Not found\n";            
        }        
    }

    return 0;
}
