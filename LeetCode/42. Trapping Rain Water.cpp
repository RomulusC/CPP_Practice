class Solution 
{
private:
    int totalWater=0;
public:
    
    int trap(std::vector<int>& height) 
    {
        for(int i =0; i<height.size();i++)
        {
            indexTotalWaterVolume(i,height);
            
        }
        
        return totalWater;
    }
    void indexTotalWaterVolume(int element ,std::vector<int>& height)
    {
        
        int lmax=0,rmax=0;
        for(int i =element-1;i>=0;i--)
        {
            if(height[i]>lmax)
            {
                lmax=height[i];
            }
        }
         for(int i =element+1;i<height.size();i++)
        {
            if(height[i]>rmax)
            {
                rmax=height[i];
            }
        }
        int localw= std::min(lmax,rmax)-height[element];
        if(localw>0)
        {
            totalWater+=localw;
        }
     
       
    }
};