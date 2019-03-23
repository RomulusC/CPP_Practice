#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

int main() {
  int N, S, P, Q;

  std::cin >> N >> S >> P >> Q;
    
  std::vector<int32_t> a(N);

  std::map<int32_t, int> map;

  a[0] = std::fmod(S, std::pow(2, 31));
  map[a[0]]++;
  for (int i = 1; i < N; i++) {
    a[i] = a[i - 1] * P + (std::fmod(Q, std::pow(2, 31)));
    map[a[i]]++;
  }

  for (std::map<int32_t, int>::iterator it = map.begin(); it != map.end(); it++) {
    // std::cout<<it->first<<" "<<it->second<<std::endl;
  }

  std::cout << map.size();
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  return 0;
}
