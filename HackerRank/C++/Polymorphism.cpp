#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>

struct Node
{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache
{
   
   protected: 
   std::map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};
class LRUCache : Cache
{
    public:

    LRUCache(int capacity)
    {
        cp = capacity;

    }
    int get(int _i) override
    {
        auto set  = mp.find(_i);
        if(set->first==_i)
        {            
            return set->first;
        } 
        else return -1;
    }
    void set(int _i, int _j) override
    {
        Node* node = new Node();
        node.key =_j;
        mp.insert(_i,new Node(_j));
    }
    

};

int main() 
{
   int n, capacity,i;
   std::cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) 
   {
      std::string command;
      std::cin >> command;
      if(command == "get") 
      {
        int key;
        std::cin >> key;
        std::cout << l.get(key) << std::endl;
      } 
      else if(command == "set") 
      {
        int key, value;
        std::cin >> key >> value;
        l.set(key,value);
      }
   }
   return 0;
}
