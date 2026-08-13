#include <iostream>
using namespace std;

struct node
{
    int val;
    node* next;

    node(int x)
    {
        val = x;
        next = nullptr;
    }
};

// INSERT FRONT 
void insertfront(node*& head, int value)
{
    node* newnode = new node(value);

    if(head == nullptr)
    {
        head = newnode;
        head->next = head;
        return;
    }

    newnode->next = head;

    node* temp = head;

    while(temp->next != head)
    {
        temp = temp->next;
    }

    temp->next = newnode;

    head = newnode;
}
// INSERT BACK
void insertback(node*& head, int value)
{
    node* newnode = new node(value);

    if(head == nullptr)
    {
        head = newnode;
        head->next=head;
        return;
    }

    node* temp = head;

    while(temp->next != head)
      {  temp = temp->next;}

    temp->next = newnode;
    newnode->next=head;
}


// DELETE FRONT
void deletefront(node*& head)
{
    if(head == nullptr)
        return;

    if(head->next == head)
    {
        delete head;
        head = nullptr;
        return;
    }
   node* temp = head;
    node* last = head;

    while(last->next != head)
    {
        last = last->next;
    }

    head = head->next;
    last->next = head;

    delete temp;
}
//delete back
void deleteback(node*& head)
{
    if(head == nullptr)
        return;

    // Only one node
    if(head->next == head)
    {
        delete head;
        head = nullptr;
        return;
    }

    node* front = head->next;
    node* cur = head;

    while(front->next != head)
    {
        cur = front;
        front = front->next;
    }

    delete front;
    cur->next = head;
}


void findndeletemid(node*& head)
{
    if(head == nullptr || head->next == head)
        return;

    node* prev = nullptr;
    node* slow = head;
    node* fast = head;

    do
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    while(fast != head && fast->next != head);

    prev->next = slow->next;

    delete slow;
}


// PRINT
void printList(node* head)
{
    if(head == nullptr)
    {
        cout << "Empty\n";
        return;
    }

    node* temp = head;

    do
    {
        cout << temp->val << " -> ";
        temp = temp->next;
    }
    while(temp != head);

    cout << "(back to head)\n";
}


 // DETECT CYCLE== ALWAYS TRUEE

// REVERSE
node* reverse(node* head)
{       if(head == nullptr || head->next == head)
        return head;

    node* prev = nullptr;
    node* curr = head;

    do
    {
        node* next = curr->next;

        curr->next = prev;
         
        prev = curr;
        curr = next;
    }while(curr != head);
    head->next=prev; //** this is because of the last pointer which initally point to head now has to point to previous which is the new head */
    return prev;
}
node* searchval(node* head, int target)
{
    node* temp = head;

    do
    {
        if(temp->val == target)
            return temp;

        temp = temp->next;
    }while(temp != head);

    return nullptr;
}

int main()
{  node* head = nullptr;
    
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