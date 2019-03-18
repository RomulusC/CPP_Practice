class Solution {
private:
    int outPut =0;
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) 
    {
        int m_temp=0;
        int n_temp=0;
       
        int temp=0;
        
        std::vector<int> topBottom;
        std::vector<int> leftRight;
        for(u_int i=0;i<grid.size();i++)
        {
            for(int n=0; n<grid.size();n++)
                {
                    n_temp= std::max(grid[i][n],n_temp);                    
                }
           leftRight.emplace_back(n_temp);
            n_temp=0;                   
        }
         
        for(u_int j=0;j<grid.size();j++)
        {
            for(int m=0; m<grid.size();m++)
                {
                    m_temp= std::max(grid[m][j],m_temp);                    
                }
            topBottom.emplace_back(m_temp);
            m_temp=0;                       
        }      
       
        for(int i=0;i<grid.size();i++)
        {
            for(int j=0;j<grid.size();j++)
            {
                if(grid[i][j]<std::min(topBottom[j],leftRight[i]))
                {
                    outPut +=std::min(topBottom[j],leftRight[i])-grid[i][j];
                }
            }            
        }        
        return outPut;
    }    
};