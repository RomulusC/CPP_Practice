/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution 
{
private:
        vector<int> outPut;
public:
    vector<int> postorderTraversal(TreeNode* root) 
    {
        
        postOrder(root);
        return outPut;
    }
    void postOrder(TreeNode* node)
    {
        if(node==NULL)
            return;
        postOrder(node->left);
        
        postOrder(node->right);
        
        outPut.emplace_back(node->val);
        
        
    }
};