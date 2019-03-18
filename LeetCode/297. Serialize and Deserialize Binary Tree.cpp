//NEED TO RETURN, NOT FUNCTIONAL



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    std::string outPut;
    // Encodes a tree to a single string.
std::string serialize(TreeNode* root) 
    {
        std::vector<int> vector;
        std::string string;
        if(root==NULL)
        {
            string.clear();
            return "";
        }
        
        std::queue<TreeNode*> q1;
        std::queue<TreeNode*> q2;       
        
        q1.push(root);  
        string+=std::to_string(q1.front()->val);         

        
        while(!q1.empty())
        {           
           
           
            if(q1.front()==NULL)
            {
                q1.pop();
            }
            else
            {
            if(q1.front()->left!=NULL) q2.push(q1.front()->left);         
            else q2.push(NULL);          
           
            if(q1.front()->right!=NULL) q2.push(q1.front()->right);
            else q2.push(NULL);            
            q1.pop();
                
            if(q1.empty())
            {
                q1=q2;
                while(!q2.empty())
                {
                   if(q2.front()!=NULL) string+=","+std::to_string(q2.front()->val);                
                    else string+=",n";
                    
                    q2.pop();
                }                   
            }
            }
        }          
       
        return string;
    }  

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) 
    {
        if(data=="") return nullptr;
        
        std::vector<std::string> s;
        
        int i=0,j;
        while(i<data.length())
        {
            if(data[i]==',')
                i++;
            j=i;
            while(i<data.length() && data[i]!=',')
                i++;
            std::string tmp = data.substr(j,i-j);
            s.push_back(tmp);
        }
        TreeNode *root = new TreeNode(stoi(s[0]));
        std::vector<TreeNode*> tr;
        tr.push_back(root);
        
        int cur = 0,lr = 0;
        for(int i=1;i<s.size();i++,lr++)
        {
            if(s[i] == "n")
            {
                if(lr%2 == 0)
                    tr[cur]->left = nullptr;
                else
                    tr[cur++]->right = nullptr;
            }
            else
            {
                TreeNode *tmp = new TreeNode(stoi(s[i]));
                if(lr%2 == 0){
                    tr[cur]->left = tmp;
                }
                else{
                    tr[cur++]->right = tmp;
                }
                
                tr.push_back(tmp);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));