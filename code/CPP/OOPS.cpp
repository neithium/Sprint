#include <iostream>
using namespace std;

class Bank
{
private:
    int acc_id;
    double balance;

public:
    Bank(double initialBalance = 0)
    {
        balance = initialBalance;
    }
    void setBalance(double balance)
    {
        this->balance = balance;
    }

    void setAccId(int acc_id)
    {
        this->acc_id = acc_id;
    }

    void deposit(double money)
    {
        if(money > 0)
            balance += money;
    }

    void withdraw(double money)
    {
        if(money <= 0)
            return;

        if(money > balance)
        {
            cout << "Insufficient balance\n";
            return;
        }

        balance -= money;
    }

    void getBalance()
    {
        cout << "Current balance: " << balance << endl;
    }

    void getAccId()
    {
        cout << "Account ID: " << acc_id << endl;
    }
};

class Person
{
    private:
        int age;string name;
    public:
        Person(){}
        Person(int age, string name)
        {
            if(age>0)this->age=age;
            this->name=name;
        }
        virtual void introduce()=0;
        virtual ~Person(){cout<<"Person destructor called"<<endl;}

};
class Student: public Person
{
    private:
        char grade;int rollno;
    public:

        Student(){}
        Student(int rollno, char grade,int age, string name): Person(age,name)
       {    
            if(rollno>0)this->rollno=rollno;
            this->grade=grade;
        }
        Student(int rollno,int age, string name):Person(age,name)
        { if(rollno>0)this->rollno=rollno;}
        void introduce() override 
        {cout<<"I am a student"<<endl;}

        void set_grade(char grade){this->grade=grade;}
        void get_grade(){cout<<"the grade of student is"<<grade<<endl;}
        ~Student(){cout<<"stu destructor called"<<endl;}

};

class Teacher:public Person, public Bank 
{
    private:
        int empId; double salary;
    public:
        Teacher(int age, string name, int empID, double salary):Person(age,name)
        {
            this->empId=empID;
            this->salary=salary;
        }
            void updateStudentGrade(Student& student, char grade)
            {
                student.set_grade(grade);
                student.get_grade();
            }

            void introduce() override
            {
                cout << "I am a teacher" << endl;
            }
            
};

 

int main()
{
    Bank b;
    Person* p1 = new Student(23, 'A', 16, "VARUN");
    Person* p2 = new Teacher(25, "ARUN", 83, 40000.0);

    p1->introduce();
    p2->introduce();

    delete p1;
    delete p2;
    b.setAccId(23);
    b.setBalance(3500);

    b.deposit(34323);
    b.withdraw(3343);

    b.getBalance();
    b.getAccId();
    Teacher* t = new Teacher(25,"ARUN", 83, 40000.0);
    Student s(23,'A',16, "VARUN");

    s.introduce();
    (*t).deposit(3400);
    (*t).setAccId(43);
    t->updateStudentGrade(s,'C');

    return 0;
}