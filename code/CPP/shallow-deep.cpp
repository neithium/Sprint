#include <iostream>
using namespace std;

class Student
{
private:
    int* marks;

public:
    Student(int m)
    {
        marks = new int(m);
    }

    // Copy constructor
    Student(const Student& other)
    {
        marks = other.marks;   // SHALLOW COPY
    }
   /** Deep copy const
    Student(const Student& other)
    {
        marks = new int(*other.marks);// Point to data memebrs of two different objects
    } */
    void setMarks(int m)
    {
        *marks = m;
    }
   
    void display()
    {
        cout << *marks << endl;
    }

    ~Student()
    {
        delete marks;
    }
};

int main()
{
    Student s1(90);
    Student s2 = s1;

    s1.setMarks(50);

    s1.display();
    s2.display();
}