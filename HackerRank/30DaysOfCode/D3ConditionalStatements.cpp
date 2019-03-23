#include <bits/stdc++.h>

using namespace std;



int main()
{
    int N;
    cin >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(N%2!=0) std::cout<<"Weird\n";
    else if (N>=2&&N<=5) std::cout<<"Not Weird\n";
    else if (N >= 6 && N <= 20) std::cout << "Weird\n";
    else if (N>20) std::cout<<"Not Weird\n";
    
    return 0;
}
