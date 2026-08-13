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

    newnode->next = head;
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
        temp = temp->next;

    temp->next = newnode;
}


// DELETE FRONT
void deletefront(node*& head)
{
    if(head == nullptr)
        return;

    node* temp = head;

    head = head->next;

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

//delete nth node from the end;
node* removeNth(node* head, int n)
{
    if(head == nullptr)
        return head;

    int len = 0;
    node* temp = head;

    // Count nodes
    while(temp != nullptr)
    {
        len++;
        temp = temp->next;
    }

    // Delete head
    if(n == len)
    {
        temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    // Go to node before target
    temp = head;

    for(int i = 1; i < len - n; i++)
        temp = temp->next;

    node* target = temp->next;

    temp->next = target->next;

    delete target;

    return head;
}
int main()
{   node* head= new node(10);
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