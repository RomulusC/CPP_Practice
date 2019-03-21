#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
	Node* next;
	Node* prev;
	int value;
	int key;
	Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
	Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
	map<int, Node*> mp; //map the key to the node in the linked list
	int cp;  //capacity
	Node* tail=NULL; // double linked list tail pointer
	Node* head=NULL; // double linked list head pointer
	virtual void set(int, int) = 0; //set function
	virtual int get(int) = 0; //get function

};
class LRUCache : Cache
{

public:
	LRUCache(int _cap)
	{
    head = NULL;
    tail = NULL;
		cp = _cap;
	}
	void set(int _key, int _val) override
	{   
		auto search = mp.find(_key);
    
		if (search != mp.end())
     {       
			Node *node = search->second;
			node->value = _val;
  
			if (node != tail && node != head) 
      {
				node->prev->next = node->next;
				node->next->prev = node->prev;
			}
			else if (node == head) 	return;

			else if (node == tail) 
      {
				node->prev->next = NULL;
				tail = node->prev;
			}

			node->next = head;
			node->prev = NULL;
			head->prev = node;
			head = node;
		}
		else
		{
			if (mp.size() < cp)
			{        
				if (head == NULL)
				{				 
					head = new Node(NULL,NULL,_key, _val);                   
					tail = head;
					mp.insert(std::make_pair(_key, head));
					return;
				}
				Node *node = new Node(NULL,head,_key, _val);			
				head->prev = node;
				head = node;
				mp.insert(std::make_pair(_key, node));
			}
			else
			{
        Node *n_tail = tail->prev;
				n_tail->next = NULL;
				mp.erase(tail->key);
				delete tail;
				tail = n_tail;
				Node *node = new Node(NULL,head, _key, _val);       
				head->prev = node;			
				head = node;
			}
		}
	}
	int get(int _key) override
	{
		auto search = mp.find(_key);
		if (search != mp.end())
		{
			Node* node = search->second;

			if (node != head && node != tail)
			{
				node->prev->next = node->next;
				node->next->prev = node->prev;
			}
			else if (node==head) return head->value;
			
			else if (node == tail) 
			{
				node->prev->next = NULL;
				tail = node->prev;
			}
      head->prev = node;
      node->prev = NULL;
      node->next = head;
			head = node;
			return search->second->value;
		}
		else 	return -1;		
	}
};

int main() {
	int n, capacity, i;
	cin >> n >> capacity;
	LRUCache l(capacity);
	for (i = 0; i < n; i++) {
		string command;
		cin >> command;
		if (command == "get") {
			int key;
			cin >> key;
			cout << l.get(key) << endl;
		}
		else if (command == "set") {
			int key, value;
			cin >> key >> value;
			l.set(key, value);
		}		
	}
	return 0;
}
