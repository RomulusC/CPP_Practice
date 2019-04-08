/*https://www.hackerrank.com/challenges/30-binary-search-trees/problem?isFullScreen=false&utm_campaign=30_days_of_code_continuous&utm_medium=email&utm_source=daily_reminder
Sample input:
7
3
5
2
1
4
6
7
------------------
Sample Output:
3
*/
#include <iostream>
#include <cstddef>

using namespace std;	

class Node{
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d){
            data = d;
            left = NULL;
            right = NULL;
        }
};
class Solution{
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            }
            else {
                Node* cur;
                if(data <= root->data){
                    cur = insert(root->left, data);
                    root->left = cur;
                }
                else{
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }

		int getHeight(Node* root)
        {
            return height(root)-1;
            
        }
        int height(Node* root)
        {
          if (root == nullptr)
            return 0;          
         
          int lheight = height(root->left);
          int rheight = height(root->right);

          if (lheight > rheight)
            return (lheight + 1);
          else
            return (rheight + 1);
        }
        
        

}; //End of Solution

int main() {
    Solution myTree;
    Node* root = NULL;
    int t;
    int data;

    cin >> t;

    while(t-- > 0){
        cin >> data;
        root = myTree.insert(root, data);
    }
    int height = myTree.getHeight(root);
    cout << height;

    return 0;
}
    
       
            
        