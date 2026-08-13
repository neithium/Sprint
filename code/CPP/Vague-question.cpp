#include <iostream>
using namespace std;

struct Node
{
    string name;
    int age;
    string date;

    Node* next;

    Node(string name, int age, string date)
    {
        this->name = name;
        this->age = age;
        this->date = date;
        next = nullptr;
    }
};


void insert(Node*& head, string name, int age, string date)
{
    Node* newNode = new Node(name, age, date);

    if(head == nullptr)
    {
        head = newNode;
        return;
    }

    Node* temp = head;

    while(temp->next != nullptr)
        temp = temp->next;

    temp->next = newNode;
}


void sortList(Node* head, int choice)
{
    if(head == nullptr)
        return;

    bool swapped;

    do
    {
        swapped = false;

        Node* curr = head;

        while(curr->next != nullptr)
        {
            bool shouldSwap = false;

            if(choice == 1)
            {
                if(curr->name > curr->next->name)
                    shouldSwap = true;
            }
            else if(choice == 2)
            {
                if(curr->age > curr->next->age)
                    shouldSwap = true;
            }
            else if(choice == 3)
            {
                if(curr->date > curr->next->date)
                    shouldSwap = true;
            }

            if(shouldSwap)
            {
                swap(curr->name, curr->next->name);
                swap(curr->age, curr->next->age);
                swap(curr->date, curr->next->date);

                swapped = true;
            }

            curr = curr->next;
        }

    } while(swapped);
}


void printList(Node* head)
{
    Node* temp = head;

    while(temp != nullptr)
    {
        cout << temp->name
             << " | "
             << temp->age
             << " | "
             << temp->date
             << endl;

        temp = temp->next;
    }
}


int main()
{
    Node* head = nullptr;

    insert(head, "report.pdf", 10, "2026-08-10");
    insert(head, "notes.txt", 3, "2026-08-12");
    insert(head, "image.png", 7, "2026-08-05");
    insert(head, "abc.txt", 1, "2026-08-01");

    cout << "Original:\n";
    printList(head);

    cout << "\nSorted by name:\n";
    sortList(head, 1);
    printList(head);

    cout << "\nSorted by age:\n";
    sortList(head, 2);
    printList(head);

    cout << "\nSorted by date:\n";
    sortList(head, 3);
    printList(head);
}