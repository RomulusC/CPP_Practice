//Incomplete, need to return
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

int main() {
  unsigned long N, S, P, Q;

  std::cin >> N >> S >> P >> Q;

  std::vector<unsigned long> a(N);


    const unsigned long x = std::pow(2, 31);
  a[0] = S % x;
 
  for (unsigned long i = 1; i < N; i++)
   {
    a[i] = a[i - 1] * P + (Q % x);
  
  }

  
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  return 0;
}
