/* https://www.hackerrank.com/challenges/virtual-functions/problem
Sample input:
4
1
Walter 56 99
2
Jesse 18 50 48 97 76 34 98
2
Pinkman 22 10 12 0 18 45 50
1
White 58 87
------------------------------
Sample output:
Walter 56 99 1
Jesse 18 403 1
Pinkman 22 135 2
White 58 87 2
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

class Person 
{  
protected:
 int age{};
 std::string name{};
public:       
   
    virtual void getdata() 
    {
        std::cin >> this->name >> this->age;
    }
    virtual void putdata() 
    {
        std::cout << this->name << " " << this->age << std::endl;
    }
};

class Professor : public Person 
{
    private:
    static unsigned int id;
      int publications;
      int cur_id;

    public:
      Professor() { this->cur_id = id++; }
      
      void getdata() { std::cin >> this->name >> this->age >> this->publications; }
      void putdata() 
      {
        std::cout << this->name << " "
            << this->age << " "
            << this->publications << " "
            << this->cur_id <<"\n";
    }
}; unsigned int Professor::id = 1;


class Student : public Person 
{
    private:
    static unsigned int id;
      int cur_id;
      int marks[6];

    public:
      Student() { this->cur_id = id++; }      
      
      void getdata() 
      {
        std::cin >> this->name >> this->age;
        for (int i=0; i<6; i++) 
        {
            std::cin >> marks[i];
        }
    }
    void putdata() 
    {
        int marksSum = 0;
        for (int i=0; i<6; i++) 
        {
            marksSum += marks[i];
        }
        std::cout << this->name << " "
            << this->age << " "
            << marksSum << " "
            << this->cur_id <<"\n";
    }
}; unsigned int Student::id = 1;



int main(){

    int n, val;
    std::cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        std::cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }    
    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.
    return 0;

}
