/*
Sample input:
4
-1
10
16
18
*/
using namespace std;
#include <iostream>

class Person
{
    public:
        int age;
        Person(int initialAge);
        void amIOld();
        void yearPasses();
    };

    Person::Person(int initialAge)
    {
        if (initialAge<1)
        {
            std::cout<<"Age is not valid, setting age to 0.\n"; 
            age=0;
        }
        else age = initialAge;
        // Add some more code to run some checks on initialAge

    }

    void Person::amIOld()
    {
        if(age<13) std::cout<<"You are young.\n";
        else if(age>=13&&age<18)std::cout<<"You are a teenager.\n";
        else std::cout<<"You are old.\n";
        // Do some computations in here and print out the correct statement to the console 

    }

    void Person::yearPasses()
    {
        age++;
        // Increment the age of the person in here

    }

int main(){
    int t;
	int age;
    cin >> t;
    for(int i=0; i < t; i++) {
    	cin >> age;
        Person p(age);
        p.amIOld();
        for(int j=0; j < 3; j++) {
        	p.yearPasses(); 
        }
        p.amIOld();
      
		cout << '\n';
    }

    return 0;
}