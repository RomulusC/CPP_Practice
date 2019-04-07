#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int GetNthPrime(const int &_i) {
  if (_i <= 0)
    return 0;
  if (_i == 1)
    return 2;
  if (_i == 2)
    return 3;

  auto pnt = [&](const int n) { return (n / log(n)); };
  int temp = 4; // start from 5
  while (true) {
    temp++;
    if (pnt(temp) >= _i)
      break;
  }

  const size_t n = temp;

  std::vector<bool> vec(n + 1, true);
  vec[0] = false;
  vec[1] = false;

  for (size_t i = 2; i <= std::floor(std::sqrt(n)); i++) {
    if (vec[i] == true) {
      int m = 0;
      for (size_t j = std::pow(i, 2); j <= n; j = std::pow(i, 2) + (m * i)) {
        vec[j] = false;
        m++;
      }
    }
  }
  temp = 0;
  for (int i = 0; i < vec.size(); i++) {
    temp += vec[i];
    if (temp == _i)
      return i;
  }
  return 0;
}

vector<int> waiter(vector<int> &number, int q) 
{

  vector<vector<int>> A{};
  A.emplace_back(number);
  vector<vector<int>> B{};
  

  for (int it = 1; it <= q; it++)
    {
        int ithP = GetNthPrime(it);
        B.emplace_back(vector<int>{});
        A.emplace_back(vector<int>{});
        for (int itt = A[it - 1].size() - 1; itt >= 0; itt--)
            {
                if(A[it-1][itt]%ithP==0)B[it-1].emplace_back(A[it-1][itt]);
                else A[it].emplace_back(A[it-1][itt]);
            }
    }
    vector<int> answ{};
    for (int bx = 0; bx < B.size(); bx++)
    {
      for (int by = B[bx].size()-1; by >=0; by--) 
      {
        answ.emplace_back(B[bx][by]);
      }
    }
    for (int a = A.back().size()-1;a>=0;a--)
    {
      answ.emplace_back(A.back()[a]);
    }
    return answ;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string nq_temp;
  getline(cin, nq_temp);

  vector<string> nq = split_string(nq_temp);

  int n = stoi(nq[0]);

  int q = stoi(nq[1]);

  string number_temp_temp;
  getline(cin, number_temp_temp);

  vector<string> number_temp = split_string(number_temp_temp);

  vector<int> number(n);

  for (int number_itr = 0; number_itr < n; number_itr++) {
    int number_item = stoi(number_temp[number_itr]);

    number[number_itr] = number_item;
  }

  vector<int> result = waiter(number, q);

  for (int result_itr = 0; result_itr < result.size(); result_itr++) {
    fout << result[result_itr];

    if (result_itr != result.size() - 1) {
      fout << "\n";
    }
  }

  fout << "\n";

  fout.close();

  return 0;
}

vector<string> split_string(string input_string) {
  string::iterator new_end =
      unique(input_string.begin(), input_string.end(),
             [](const char &x, const char &y) { return x == y and x == ' '; });

  input_string.erase(new_end, input_string.end());

  while (input_string[input_string.length() - 1] == ' ') {
    input_string.pop_back();
  }

  vector<string> splits;
  char delimiter = ' ';

  size_t i = 0;
  size_t pos = input_string.find(delimiter);

  while (pos != string::npos) {
    splits.push_back(input_string.substr(i, pos - i));

    i = pos + 1;
    pos = input_string.find(delimiter, i);
  }

  splits.push_back(
      input_string.substr(i, min(pos, input_string.length()) - i + 1));

  return splits;
}
