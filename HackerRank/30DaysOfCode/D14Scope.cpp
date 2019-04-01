#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Difference {
    private:
    vector<int> elements;
  
  	public:
  	int maximumDifference;
    Difference(vector<int>& _vec)
    : elements(_vec){}
    void computeDifference()
    {
      int min = std::abs(elements[0]), max = std::abs(elements[0]);
      for (unsigned int i = 1; i < this->elements.size(); i++) {
        if (std::abs(elements[i]) < min)
          min = std::abs(elements[i]);
        if (std::abs(elements[i]) > max)
          max = std::abs(elements[i]);
      }
      this->maximumDifference = max - min;
    }	

}; // End of Difference class

int main() {
    int N;
    cin >> N;
    
    vector<int> a;
    
    for (int i = 0; i < N; i++) {
        int e;
        cin >> e;
        
        a.push_back(e);
    }
    
    Difference d(a);
    
    d.computeDifference();
    
    cout << d.maximumDifference;
    
    return 0;
}