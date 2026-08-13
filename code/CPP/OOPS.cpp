#include <iostream>
using namespace std;

class Bank
{
private:
    int acc_id;
    double balance;

public:

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

 

int main()
{
    Bank b;

    b.setAccId(23);
    b.setBalance(3500);

    b.deposit(34323);
    b.withdraw(3343);

    b.getBalance();
    b.getAccId();
}