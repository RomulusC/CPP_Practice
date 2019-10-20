#include <iostream>
#include <vector>
#include <string>

int main()
{
    int nGenes;
    scanf("%d", &nGenes);
    std::vector<std::string> charTable(nGenes);
    std::vector<int>  intTable(nGenes);   

    for(int i =0; i<nGenes;i++)
    {
        std::cin>>charTable[i];
    }
    for(int i =0; i<nGenes;i++)
    {
        scanf("%d",&intTable[i]);
       
    } 

    int n;
    scanf("%d",&n);
   
    int min=0, max=0;
    for(int i =0; i<n;i++) //input number
    {
        int start, end;
        std::string gene;
        
        scanf("%d %d", &start, &end);
        std::cin>>gene;
        

        int localhealth=0;
        for(int k = start; k<=end;k++) //charTable[k]
        {
            std::size_t found = gene.find(charTable[k]);
            while(found!=std::string::npos)            
            {
                localhealth+=intTable[k];
                found = gene.find(charTable[k],found+1);              
               
            }           
        }
        min = std::min(localhealth, min);
        max = std::max(localhealth, max);    
    }

    std::cout<<min<<" "<<max<<"\n";

    return 0;

}