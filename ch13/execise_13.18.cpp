#include <iostream>
#include <string>

using namespace std;

class Employee
{
  public:
    Employee() : id(num++) {
        cout << id << endl;
    }
    Employee(const string& str) : id(num++), name(str) {
        cout << id << endl;
    }

    Employee(const Employee &employee) = delete;
    Employee &operator=(const Employee &employee) = delete;  

    static int num;

  private:
    int id;
    string name;
};

int Employee::num = 0;

int main()
{
    Employee e1;
    Employee e2("hello");
}