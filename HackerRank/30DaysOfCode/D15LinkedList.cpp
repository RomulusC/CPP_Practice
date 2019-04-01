/* https://www.hackerrank.com/challenges/30-linked-list/problem
Sample Input:
4
2
3
4
1
--------
Sample Output:
2 3 4 1
*/
#include <iostream>
#include <cstddef>
using namespace std;	
class Node
{
    public:
        int data;
        Node *next;
        Node(int d){
            data=d;
            next=NULL;
        }
};
class Solution{
    public:

      Node* insert(Node *head,int data)
      {
          if(head==NULL)return new Node(data);
          else
          {
              Node* n = head;
              while(n->next!=NULL)
              {
                  n=n->next;
              }
              n->next = new Node(data);
              return head;
          }
          //Complete this method
      }

      void display(Node *head)
      {
          Node *start=head;
          while(start)
          {
              cout<<start->data<<" ";
              start=start->next;
          }
      }
};
int main()
{
	Node* head=NULL;
  	Solution mylist;
    int T,data;
    cin>>T;
    while(T-->0){
        cin>>data;
        head=mylist.insert(head,data);
    }	
	mylist.display(head);
		
}