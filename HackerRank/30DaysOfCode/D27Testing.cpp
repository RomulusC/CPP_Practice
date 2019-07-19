#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

int minimum_index(vector<int> seq) {
    if (seq.empty()) {
        throw invalid_argument("Cannot get the minimum value index from an empty sequence");
    }
    int min_idx = 0;
    for (int i = 1; i < seq.size(); ++i) {
        if (seq[i] < seq[min_idx]) {
            min_idx = i;
        }
    }
    return min_idx;
}


class TestDataEmptyArray 
{
public:
/*
    static std::vector<int> vec;
    TestDataEmptyArray(std::vector<int>& _vec)
    {
        vec = _vec;
    }
*/
    static vector<int> get_array() 
    {
        return std::vector<int>();
    }

};

class TestDataUniqueValues {
private:
    static int minimum;

public:
    static vector<int> get_array() 
    {
        std::vector<int> vec = std::vector<int>();
        minimum = 0;
        int maximum = 10;
        for(int i = minimum; i<maximum; i++)
        {
            vec.emplace_back(i);
        }     
        return vec;
    }

    static int get_expected_result() 
    {
        return minimum;
    }

};

class TestDataExactlyTwoDifferentMinimums {
private:
    static int minimum;

public:
    static vector<int> get_array() 
    {
        std::vector<int> vec = std::vector<int>();
        minimum = 0;
        int maximum = 10;
        for(int i = minimum; i<maximum; i++)
        {
            vec.emplace_back(i);
        }     
        vec.emplace_back(minimum);
        return vec;
    }

    static int get_expected_result() 
    {
       return minimum;
    }

};




void TestWithEmptyArray() {
    try {
        auto seq = TestDataEmptyArray::get_array();
        auto result = minimum_index(seq);
    } catch (invalid_argument& e) {
        return;
    }
    assert(false);
}

void TestWithUniqueValues() {
    auto seq = TestDataUniqueValues::get_array();
    assert(seq.size() >= 2);

    assert(set<int>(seq.begin(), seq.end()).size() == seq.size());

    auto expected_result = TestDataUniqueValues::get_expected_result();
    auto result = minimum_index(seq);
    assert(result == expected_result);
}

void TestWithExactlyTwoDifferentMinimums() {
    auto seq = TestDataExactlyTwoDifferentMinimums::get_array();
    assert(seq.size() >= 2);

    auto tmp = seq;
    sort(tmp.begin(), tmp.end());
    assert(tmp[0] == tmp[1] and (tmp.size() == 2 or tmp[1] < tmp[2]));

    auto expected_result = TestDataExactlyTwoDifferentMinimums::get_expected_result();
    auto result = minimum_index(seq);
    assert(result == expected_result);
}

int main() {
    TestWithEmptyArray();
    TestWithUniqueValues();
    TestWithExactlyTwoDifferentMinimums();
    cout << "OK" << endl;
    return 0;
}
