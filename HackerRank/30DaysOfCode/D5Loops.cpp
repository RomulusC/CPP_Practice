#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    if(n>20)n=20;
    if(n<0)n=0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int answ{};
    for(int i =1; i<=10;i++)
    {
        answ = n*i;
        printf("%d x %d = %d\n",n,i,answ);
    }
    return 0;
}
