class Solution 
{
public:
    std::vector<int> getRow(int rowIndex) 
    {
        std::vector<int> pTriangle;
        pTriangle.reserve(rowIndex+1);
        for(int i = 0; i <= rowIndex; i++){
            pTriangle.push_back(1);
            for(int j = i - 1; j > 0; j--){
                pTriangle[j] = pTriangle[j] + pTriangle[j - 1];
            }
        }
        return pTriangle;
    }
};