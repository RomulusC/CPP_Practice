//Sample Input
//5
//10 40 30 50 20
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

void ParseStringVector(std::vector<int> &_vector, const std::string &_string) {
  std::istringstream iss(_string);
  std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                   std::istream_iterator<std::string>());

  for (int i = 0; i < results.size(); i++) {
    _vector.emplace_back(stoi(results[i]));
  }
}

int main() {
  int n{};
  int mean{};
  double sd{};

  double numerator{};

  std::string input;
  std::vector<int> iVec{};

  
  std::cin >> input;
  //std::cin.ignore(); //WEBSITE PARSING BUG
  std::cin.ignore();
  
 
  std::getline(std::cin, input);
  
  ParseStringVector(iVec, input);
  n = iVec.size();

  for (int i = 0; i < iVec.size(); i++) {
    mean += iVec[i];
  }
  mean = mean / iVec.size();

  for (int i = 0; i < iVec.size(); i++) {
    numerator += std::pow(iVec[i] - mean, 2);
  }
  sd = std::sqrt(numerator / n);

  std::cout << std::fixed << std::setprecision(1) << sd << "\n";

  
  return 0;
}
