#include <iostream>
#include <vector>



int main()
{
    std::vector<std::vector<int>> arr(6);
    for (int i = 0; i < 6; i++) 
    {
        arr[i].resize(6);

        for (int j = 0; j < 6; j++) 
        {
            std::cin >> arr[i][j];
        }        
    }    
    std::vector<int> w;
    w.reserve(16);
    int count =0;
    for(int i =0; i<6;i++)
    {
        for(int j =0; j<6;j++)
        {
            if(i+2<6&&j+2<6)
            {
                int temp = arr[i][j];
                 
                temp = temp + arr[i][j+1];
                temp = temp + arr[i][j+2];
               
                temp = temp + arr[i+1][j+1];
                temp = temp + arr[i+2][j];
                temp = temp + arr[i+2][j+1];
                temp = temp + arr[i+2][j+2];                
               
                w.emplace_back(temp);                 

            }
        }       
    }

    int weight = w[0];
        for(int i =0;i<w.size();i++)
        {
            
            if(w[i]>weight)weight =w[i];
            
        }
        std::cout<<weight<<"\n";
        
    return 0;
}
