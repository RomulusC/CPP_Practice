#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
class AdvancedArithmetic{
    public:
        virtual int divisorSum(int n)=0;
};

class Calculator : public AdvancedArithmetic {
public:
  int divisorSum(int n) {
    const int o = n;
    int answ{};
    while (n > 0) {
      if (o % n == 0)
        answ += n;
      n--;
    }
    return answ;
  }
};

int main(){
    int n;
    cin >> n;
    AdvancedArithmetic *myCalculator = new Calculator(); 
    int sum = myCalculator->divisorSum(n);
    cout << "I implemented: AdvancedArithmetic\n" << sum;
    return 0;
}