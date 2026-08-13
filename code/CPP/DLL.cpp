#include <iostream>
using namespace std;

struct node
{
    int val;
    node* next;
    node* prev;

    node(int x)
    {
        val = x;
        next = nullptr;
        prev= nullptr;
    }
};


// INSERT FRONT
void insertfront(node*& head, int value)
{
    node* newnode = new node(value);
    if(head == nullptr)
    {
        head = newnode;
        return;
    }
    newnode->next = head;
    head->prev=newnode;
    head = newnode;
}


// INSERT BACK
void insertback(node*& head, int value)
{
    node* newnode = new node(value);

    if(head == nullptr)
    {
        head = newnode;
        return;
    }

    node* temp = head;

    while(temp->next != nullptr)
      {  temp = temp->next;}

    temp->next = newnode;
    newnode->prev=temp;
}


// DELETE FRONT
void deletefront(node*& head)
{
    if(head == nullptr)
        return;

    node* temp = head;

    head = head->next;

    if(head != nullptr)
        head->prev = nullptr;

    delete temp;
}


// DELETE BACK
void deleteback(node*& head)
{
    if(head == nullptr)
        return;

    if(head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }

    node* front = head->next;
    node* cur = head;

    while(front->next != nullptr)
    {
        cur = front;
        front = front->next;
    }

    delete front;
    cur->next = nullptr;
}


// DELETE MIDDLE
void findndeletemid(node*& head)
{
    if(head == nullptr || head->next == nullptr)
        return;

    node* prev = nullptr;
    node* slow = head;
    node* fast = head;

    while(fast && fast->next)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev->next = slow->next;
    slow->next->prev = prev;

    delete slow;
}


// PRINT
void printList(node* head)
{
    node* temp = head;

    while(temp != nullptr)
    {
        cout << temp->val << " -> ";
        temp = temp->next;
    }

    cout << "NULL\n";
}


// DETECT CYCLE
bool Detectcycle(node* head)
{
    node* slow = head;
    node* fast = head;

    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
            return true;
    }

    return false;
}


// REVERSE
node* reverse(node* head)
{
    node* prev = nullptr;
    node* curr = head;

    while(curr != nullptr)
    {
        node* next = curr->next;

        curr->next = prev;
        curr->prev=next;
        prev = curr;
        curr = next;
    }

    return prev;
}
node* searchval(node* head, int target)
{
    node* temp = head;

    while(temp != nullptr)
    {
        if(temp->val == target)
            return temp;

        temp = temp->next;
    }

    return nullptr;
}

int main()
{   node* head= nullptr;
   printList(head);
    insertfront(head, 30);printList(head);
    insertback(head, 20);printList(head);
    insertfront(head, 40);printList(head);
    head=reverse(head);
    printList(head);
    deletefront(head);printList(head);
    deleteback(head);
    printList(head);

}