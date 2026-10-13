#include <iostream>
#include <algorithm>
using namespace std;

// ============================================================
// SINGLY LINKED LIST (SLL)
// ============================================================
struct node {
    int val;
    node* next;
    node(int x) { val = x; next = nullptr; }
};

// INSERT FRONT: O(1)
void insertfront(node*& head, int value) {
    node* newnode = new node(value);
    newnode->next = head;
    head = newnode;
}

// INSERT BACK: O(n)
void insertback(node*& head, int value) {
    node* newnode = new node(value);
    if (head == nullptr) { head = newnode; return; }
    node* temp = head;
    while (temp->next != nullptr) temp = temp->next;
    temp->next = newnode;
}

// DELETE FRONT: O(1)
void deletefront(node*& head) {
    if (head == nullptr) return;
    node* temp = head;
    head = head->next;
    delete temp;
}

// DELETE BACK: O(n)
void deleteback(node*& head) {
    if (head == nullptr) return;
    if (head->next == nullptr) { delete head; head = nullptr; return; }
    node* cur = head;
    node* front = head->next;
    while (front->next != nullptr) { cur = front; front = front->next; }
    cur->next = nullptr;
    delete front;
}

// PRINT SLL: O(n)
void printList(node* head) {
    node* temp = head;
    while (temp != nullptr) { cout << temp->val << " -> "; temp = temp->next; }
    cout << "NULL\n";
}

// SEARCH BY VALUE: O(n). Returns first matching node address, or nullptr.
node* searchval(node* head, int target) {
    node* temp = head;
    while (temp != nullptr) {
        if (temp->val == target) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// REVERSE SLL ITERATIVELY: O(n) time, O(1) auxiliary space
node* reverse(node* head) {
    node* prev = nullptr;
    node* curr = head;
    while (curr != nullptr) {
        node* nextnode = curr->next; // Save the rest of the list.
        curr->next = prev;           // Reverse this link.
        prev = curr;
        curr = nextnode;
    }
    return prev;
}

// REVERSE SLL RECURSIVELY: O(n) time, O(n) call-stack space
node* reverserecursive(node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    node* newhead = reverserecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newhead;
}

// FIND AND DELETE MIDDLE: O(n) time, O(1) space.
// For an even number of nodes, this deletes the second middle node.
void findndeletemid(node*& head) {
    if (head == nullptr || head->next == nullptr) return;
    node* prev = nullptr;
    node* slow = head;
    node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = slow->next;
    delete slow;
}

// DETECT CYCLE (Floyd): O(n) time, O(1) space
bool Detectcycle(node* head) {
    node* slow = head;
    node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// PALINDROME CHECK: O(n) time, O(1) space.
// Reverse second half, compare, and restore the original list.
bool isPalindrome(node* head) {
    if (head == nullptr || head->next == nullptr) return true;

    node* slow = head;
    node* fast = head;
    node* firsthalfend = nullptr;
    while (fast != nullptr && fast->next != nullptr) {
        firsthalfend = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    bool oddlength = (fast != nullptr);
    node* secondhalfstart = oddlength ? slow->next : slow;
    node* reversedsecond = reverse(secondhalfstart);

    if (oddlength) slow->next = reversedsecond;
    else firsthalfend->next = reversedsecond;

    bool same = true;
    node* left = head;
    node* right = reversedsecond;
    while (right != nullptr) {
        if (left->val != right->val) { same = false; break; }
        left = left->next;
        right = right->next;
    }

    node* restoredsecond = reverse(reversedsecond);
    if (oddlength) slow->next = restoredsecond;
    else firsthalfend->next = restoredsecond;
    return same;
}

// MERGE TWO SORTED SLLs: O(m+n) time, O(1) auxiliary space.
// Reuses existing nodes.
node* mergesorted(node* head1, node* head2) {
    node dummy(0);
    node* tail = &dummy;
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->val <= head2->val) { tail->next = head1; head1 = head1->next; }
        else { tail->next = head2; head2 = head2->next; }
        tail = tail->next;
    }
    tail->next = (head1 != nullptr) ? head1 : head2;
    return dummy.next;
}

// INTERSECTION OF TWO SLLs: O(m+n) time, O(1) space.
// Compare node addresses, not values.
node* getIntersectionNode(node* headA, node* headB) {
    node* a = headA;
    node* b = headB;
    while (a != b) {
        a = (a == nullptr) ? headB : a->next;
        b = (b == nullptr) ? headA : b->next;
    }
    return a; // Shared node address, or nullptr.
}

// DELETE NTH NODE FROM LEFT (1-based): O(n) time, O(1) space.
// Invalid n leaves the list unchanged.
node* removeNthFromLeft(node* head, int n) {
    if (head == nullptr || n <= 0) return head;
    if (n == 1) { node* temp = head; head = head->next; delete temp; return head; }
    node* prev = head;
    for (int i = 1; i < n - 1 && prev != nullptr; i++) prev = prev->next;
    if (prev == nullptr || prev->next == nullptr) return head;
    node* target = prev->next;
    prev->next = target->next;
    delete target;
    return head;
}


// DELETE ITH NODE FROM LEFT (1-BASED) /// o(n) time, id say it is pretty easier than the previous one
node* removeNthFromLeft(node* head, int n)
{
    if (head == nullptr || n <= 0)
        return head;

    // Special case: deleting the first node
    if (n == 1)
    {
        node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    node* prev = head;
    int counter = 1;

    // Stop at the node immediately before the target
    while (prev->next != nullptr && counter < n - 1)
    {
        prev = prev->next;
        counter++;
    }

    // Target position does not exist
    if (prev->next == nullptr)
        return head;

    node* target = prev->next;
    prev->next = target->next;
    delete target;

    return head;
}

// DELETE NTH NODE FROM RIGHT (1-based): O(n) time, O(1) space.
// Uses a dummy node and a gap of n nodes. Invalid n leaves list unchanged.
node* removeNthFromRight(node* head, int n) {
    if (head == nullptr || n <= 0) return head;
    node dummy(0);
    dummy.next = head;
    node* fast = &dummy;
    node* slow = &dummy;
    for (int i = 0; i < n; i++) {
        fast = fast->next;
        if (fast == nullptr) return head; // n exceeds list length.
    }
    while (fast->next != nullptr) { fast = fast->next; slow = slow->next; }
    node* target = slow->next;
    slow->next = target->next;
    delete target;
    return dummy.next;
}

// DELETE NTH NODE FROM RIGHT (1-BASED) -- easier approach

node* removeNthFromRight(node* head, int n)
{
    if (head == nullptr || n <= 0)
        return head;

    // Count the total number of nodes
    int len = 0;
    node* temp = head;

    while (temp != nullptr)
    {
        len++;
        temp = temp->next;
    }

    // Invalid position
    if (n > len)
        return head;

    // Convert right position to left position
    int pos = len - n + 1;

    // Special case: deleting the first node
    if (pos == 1)
    {
        temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    // Reach the node before the target
    node* prev = head;
    int counter = 1;

    while (prev->next != nullptr && counter < pos - 1)
    {
        prev = prev->next;
        counter++;
    }

    // Unlink and delete the target node
    node* target = prev->next;
    prev->next = target->next;
    delete target;

    return head;
}
// ============================================================
// DOUBLY LINKED LIST (DLL)
// ============================================================
struct dllnode {
    int val;
    dllnode* prev;
    dllnode* next;
    dllnode(int x) { val = x; prev = nullptr; next = nullptr; }
};

// REVERSE DLL ITERATIVELY: O(n) time, O(1) space
// Explicit pointer assignments are used; no std::swap.
dllnode* reversedll(dllnode* head) {
    dllnode* curr = head;
    dllnode* newhead = nullptr;
    while (curr != nullptr) {
        dllnode* originalnext = curr->next;
        curr->next = curr->prev;
        curr->prev = originalnext;
        newhead = curr;
        curr = originalnext;
    }
    return newhead;
}

// REVERSE DLL RECURSIVELY: O(n) time, O(n) call-stack space
dllnode* reversedllrecursive(dllnode* curr) {
    if (curr == nullptr) return nullptr;
    dllnode* originalnext = curr->next;
    curr->next = curr->prev;
    curr->prev = originalnext;
    if (originalnext == nullptr) return curr;
    return reversedllrecursive(originalnext);
}

void printDLL(dllnode* head) {
    dllnode* temp = head;
    while (temp != nullptr) { cout << temp->val << " <-> "; temp = temp->next; }
    cout << "NULL\n";
}

// ============================================================
// CIRCULAR SINGLY LINKED LIST (CSLL)
// The tail points back to head. These functions use node.
// ============================================================
void printCircular(node* head) {
    if (head == nullptr) { cout << "EMPTY\n"; return; }
    node* temp = head;
    do { cout << temp->val << " -> "; temp = temp->next; } while (temp != head);
    cout << "(back to head)\n";
}

// REVERSE CSLL ITERATIVELY: O(n) time, O(1) space
node* reverseCircular(node* head) {
    if (head == nullptr || head->next == head) return head;
    node* oldhead = head;
    node* prev = head;
    node* curr = head->next;
    while (curr != oldhead) {
        node* nextnode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextnode;
    }
    oldhead->next = prev; // Close the circle.
    return prev;           // Original tail is the new head.
}

// ============================================================
// CIRCULAR DOUBLY LINKED LIST (CDLL)
// ============================================================
struct cdllnode {
    int val;
    cdllnode* prev;
    cdllnode* next;
    cdllnode(int x) { val = x; prev = nullptr; next = nullptr; }
};

void printCircularDLL(cdllnode* head) {
    if (head == nullptr) { cout << "EMPTY\n"; return; }
    cdllnode* temp = head;
    do { cout << temp->val << " <-> "; temp = temp->next; } while (temp != head);
    cout << "(back to head)\n";
}

// REVERSE CDLL ITERATIVELY: O(n) time, O(1) space
cdllnode* reverseCircularDLL(cdllnode* head) {
    if (head == nullptr || head->next == head) return head;
    cdllnode* curr = head;
    do {
        cdllnode* originalnext = curr->next;
        curr->next = curr->prev;
        curr->prev = originalnext;
        curr = originalnext;
    } while (curr != head);
    return head->prev; // Original tail becomes the new head.
}

// ============================================================
// EXAMPLE MAIN: basic SLL operations and selected algorithms.
// Each other function can be tested separately.
// ============================================================
int main() {
    node* head = nullptr;
    insertfront(head, 10);
    insertfront(head, 30);
    insertback(head, 20);
    insertfront(head, 40);

    cout << "Original SLL: ";
    printList(head);

    head = reverse(head);
    cout << "Reversed SLL: ";
    printList(head);

    cout << "Contains cycle? " << (Detectcycle(head) ? "Yes" : "No") << '\n';
    cout << "Is palindrome? " << (isPalindrome(head) ? "Yes" : "No") << '\n';

    head = removeNthFromRight(head, 2);
    cout << "After deleting 2nd node from right: ";
    printList(head);

    findndeletemid(head);
    cout << "After deleting middle node: ";
    printList(head);

    deletefront(head);
    deleteback(head);
    cout << "After deleting front and back: ";
    printList(head);

    while (head != nullptr) deletefront(head);
    return 0;
}