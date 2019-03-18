/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) 
    {
        val = _val;
        children = _children;
    }
};
*/
class Solution 
{
private:
    vector<int> outPut;
    
    void PostOrder(Node* _node)
    {
        if(_node==NULL)
        return;
        
        for(int i=0; i<_node->children.size();i++)
        {
            PostOrder(_node->children[i]);
        }
        outPut.emplace_back(_node->val);
    }
public:
    vector<int> postorder(Node* root) 
    {
        PostOrder(root);
        return outPut;
    }   
};