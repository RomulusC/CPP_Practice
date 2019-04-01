#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Person{
	protected:
		string firstName;
		string lastName;
		int id;
	public:
		Person(string firstName, string lastName, int identification){
			this->firstName = firstName;
			this->lastName = lastName;
			this->id = identification;
		}
		void printPerson(){
			cout<< "Name: "<< lastName << ", "<< firstName <<"\nID: "<< id << "\n"; 
		}
	
};

class Student :  public Person
{
	private:
		vector<int> testScores;  
	public:
        Student(const std::string &f_name, const std::string &l_name,
                  const int &_id, const vector<int> &_scores) : Person(f_name,l_name,_id), testScores(_scores) {}

        char calculate() 
        {
            int answ = testScores[0];
            for(int i = 1; i<testScores.size();i++)
            {
              answ += testScores[i];
            }
            answ = answ/testScores.size();
            if(answ<40) return 'T';
            else if(answ<55)return 'D';
            else if(answ<70)return 'P';
            else if(answ<80)return 'A';
            else if(answ<90)return 'E';
            else return 'O';
        }
        /*	
        *   Class Constructor
        *   
        *   Parameters:
        *   firstName - A string denoting the Person's first name.
        *   lastName - A string denoting the Person's last name.
        *   id - An integer denoting the Person's ID number.
        *   scores - An array of integers denoting the Person's test scores.
        */
        // Write your constructor here

        /*	
        *   Function Name: calculate
        *   Return: A character denoting the grade.
        */
        // Write your function here
};

int main() {
	string firstName;
  	string lastName;
	int id;
  	int numScores;
	cin >> firstName >> lastName >> id >> numScores;
  	vector<int> scores;
  	for(int i = 0; i < numScores; i++){
	  	int tmpScore;
	  	cin >> tmpScore;
		scores.push_back(tmpScore);
	}
	Student* s = new Student(firstName, lastName, id, scores);
	s->printPerson();
	cout << "Grade: " << s->calculate() << "\n";
	return 0;
}