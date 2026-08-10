#include <iostream>
using namespace std;


/*
====================================================================
                    LINKED LIST INTERVIEW SHEET
====================================================================

Topics covered:

1.  Singly Linked List (SLL)
    - Creation
    - Insert front
    - Insert back
    - Delete front
    - Delete back
    - Print

2.  Doubly Linked List (DLL)
    - Creation
    - Insert front
    - Insert back
    - Delete front
    - Delete back
    - Print

3.  Circular Linked List
    - Creation
    - Insert front
    - Insert back
    - Delete front
    - Delete back
    - Print

4.  Merge two sorted SLL
5.  Merge two sorted DLL
6.  Reverse SLL - Iterative
7.  Reverse SLL - Recursive
8.  Loop detection - Floyd's Algorithm
9.  Starting point of loop
10. Palindrome Linked List
11. Check whether linked list is circular
12. Merge Sort on Linked List
13. Quick Sort on Linked List
14. Rotate Linked List

====================================================================
*/


/*
====================================================================
1. SINGLY LINKED LIST
====================================================================

Node:

[data | next]

Example:

10 -> 20 -> 30 -> NULL

Each node stores:

1. Data
2. Pointer to next node
*/


struct SNode
{
    int data;
    SNode* next;

    SNode(int value)
    {
        data = value;
        next = nullptr;
    }
};


/*
--------------------------------------------------------------------
INSERT AT FRONT
--------------------------------------------------------------------

Before:

10 -> 20 -> 30

insertFront(5)

After:

5 -> 10 -> 20 -> 30
*/

void insertFront(SNode*& head, int value)
{
    SNode* newNode = new SNode(value);

    newNode->next = head;

    head = newNode;
}


/*
--------------------------------------------------------------------
INSERT AT BACK
--------------------------------------------------------------------

Before:

10 -> 20

insertBack(30)

After:

10 -> 20 -> 30
*/

void insertBack(SNode*& head, int value)
{
    SNode* newNode = new SNode(value);

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    SNode* temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}


/*
--------------------------------------------------------------------
DELETE FRONT
--------------------------------------------------------------------

Before:

10 -> 20 -> 30

After:

20 -> 30
*/

void deleteFront(SNode*& head)
{
    if (head == nullptr)
        return;

    SNode* temp = head;

    head = head->next;

    delete temp;
}


/*
--------------------------------------------------------------------
DELETE BACK
--------------------------------------------------------------------

Before:

10 -> 20 -> 30

After:

10 -> 20
*/

void deleteBack(SNode*& head)
{
    if (head == nullptr)
        return;

    // Only one node
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }

    SNode* temp = head;

    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    delete temp->next;

    temp->next = nullptr;
}


/*
--------------------------------------------------------------------
PRINT SLL
--------------------------------------------------------------------
*/

void printSLL(SNode* head)
{
    while (head != nullptr)
    {
        cout << head->data << " -> ";
        head = head->next;
    }

    cout << "NULL\n";
}


/*
====================================================================
2. DOUBLY LINKED LIST
====================================================================

Node:

[prev | data | next]

Example:

NULL <- 10 <-> 20 <-> 30 -> NULL

Every node has:

prev -> previous node
next -> next node
*/


struct DNode
{
    int data;
    DNode* prev;
    DNode* next;

    DNode(int value)
    {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};


/*
--------------------------------------------------------------------
INSERT FRONT - DLL
--------------------------------------------------------------------
*/

void insertFront(DNode*& head, int value)
{
    DNode* newNode = new DNode(value);

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    newNode->next = head;

    head->prev = newNode;

    head = newNode;
}


/*
--------------------------------------------------------------------
INSERT BACK - DLL
--------------------------------------------------------------------
*/

void insertBack(DNode*& head, int value)
{
    DNode* newNode = new DNode(value);

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    DNode* temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;

    newNode->prev = temp;
}


/*
--------------------------------------------------------------------
DELETE FRONT - DLL
--------------------------------------------------------------------
*/

void deleteFront(DNode*& head)
{
    if (head == nullptr)
        return;

    DNode* temp = head;

    head = head->next;

    if (head != nullptr)
        head->prev = nullptr;

    delete temp;
}


/*
--------------------------------------------------------------------
DELETE BACK - DLL
--------------------------------------------------------------------
*/

void deleteBack(DNode*& head)
{
    if (head == nullptr)
        return;

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }

    DNode* temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->prev->next = nullptr;

    delete temp;
}


/*
--------------------------------------------------------------------
PRINT DLL
--------------------------------------------------------------------
*/

void printDLL(DNode* head)
{
    while (head != nullptr)
    {
        cout << head->data << " <-> ";
        head = head->next;
    }

    cout << "NULL\n";
}


/*
====================================================================
3. CIRCULAR LINKED LIST
====================================================================

Unlike normal SLL:

10 -> 20 -> 30 -> NULL

Circular:

10 -> 20 -> 30
^             |
|_____________|

The last node points back to head.

IMPORTANT:

There is NO nullptr at the end.

So normal:

while(temp != nullptr)

cannot be used for traversal.

We stop when:

temp->next == head
*/


struct CNode
{
    int data;
    CNode* next;

    CNode(int value)
    {
        data = value;
        next = nullptr;
    }
};


/*
--------------------------------------------------------------------
INSERT FRONT - CIRCULAR
--------------------------------------------------------------------
*/

void insertFront(CNode*& head, int value)
{
    CNode* newNode = new CNode(value);

    // Empty list
    if (head == nullptr)
    {
        head = newNode;
        newNode->next = head;

        return;
    }

    CNode* temp = head;

    while (temp->next != head)
    {
        temp = temp->next;
    }

    newNode->next = head;

    temp->next = newNode;

    head = newNode;
}


/*
--------------------------------------------------------------------
INSERT BACK - CIRCULAR
--------------------------------------------------------------------
*/

void insertBack(CNode*& head, int value)
{
    CNode* newNode = new CNode(value);

    if (head == nullptr)
    {
        head = newNode;
        newNode->next = head;

        return;
    }

    CNode* temp = head;

    while (temp->next != head)
    {
        temp = temp->next;
    }

    temp->next = newNode;

    newNode->next = head;
}


/*
--------------------------------------------------------------------
DELETE FRONT - CIRCULAR
--------------------------------------------------------------------
*/

void deleteFront(CNode*& head)
{
    if (head == nullptr)
        return;

    // Only one node
    if (head->next == head)
    {
        delete head;
        head = nullptr;

        return;
    }

    CNode* last = head;

    while (last->next != head)
    {
        last = last->next;
    }

    CNode* temp = head;

    head = head->next;

    last->next = head;

    delete temp;
}


/*
--------------------------------------------------------------------
DELETE BACK - CIRCULAR
--------------------------------------------------------------------
*/

void deleteBack(CNode*& head)
{
    if (head == nullptr)
        return;

    // One node
    if (head->next == head)
    {
        delete head;
        head = nullptr;

        return;
    }

    CNode* temp = head;

    while (temp->next->next != head)
    {
        temp = temp->next;
    }

    delete temp->next;

    temp->next = head;
}


/*
--------------------------------------------------------------------
PRINT CIRCULAR LIST
--------------------------------------------------------------------
*/

void printCircular(CNode* head)
{
    if (head == nullptr)
    {
        cout << "Empty\n";
        return;
    }

    CNode* temp = head;

    do
    {
        cout << temp->data << " -> ";

        temp = temp->next;

    } while (temp != head);

    cout << "(back to head)\n";
}


/*
====================================================================
4. MERGE TWO SORTED SINGLY LINKED LISTS
====================================================================

Example:

List 1:

1 -> 3 -> 5

List 2:

2 -> 4 -> 6

Result:

1 -> 2 -> 3 -> 4 -> 5 -> 6


IDEA:

Compare the current nodes of both lists.

Take the smaller one.

Move that pointer forward.

Time: O(n + m)
Space: O(1)
*/


SNode* mergeSLL(SNode* a, SNode* b)
{
    if (a == nullptr)
        return b;

    if (b == nullptr)
        return a;

    SNode dummy(0);

    SNode* tail = &dummy;

    while (a != nullptr && b != nullptr)
    {
        if (a->data < b->data)
        {
            tail->next = a;
            a = a->next;
        }
        else
        {
            tail->next = b;
            b = b->next;
        }

        tail = tail->next;
    }

    if (a != nullptr)
        tail->next = a;

    else
        tail->next = b;

    return dummy.next;
}


/*
====================================================================
5. MERGE TWO SORTED DOUBLY LINKED LISTS
====================================================================

Same idea as SLL.

But because DLL has prev pointers,
we must update both:

next
prev
*/


DNode* mergeDLL(DNode* a, DNode* b)
{
    if (a == nullptr)
        return b;

    if (b == nullptr)
        return a;

    DNode dummy(0);

    DNode* tail = &dummy;

    while (a != nullptr && b != nullptr)
    {
        DNode* chosen;

        if (a->data < b->data)
        {
            chosen = a;
            a = a->next;
        }
        else
        {
            chosen = b;
            b = b->next;
        }

        tail->next = chosen;
        chosen->prev = tail;

        tail = chosen;
    }

    if (a != nullptr)
    {
        tail->next = a;
        a->prev = tail;
    }
    else
    {
        tail->next = b;

        if (b != nullptr)
            b->prev = tail;
    }

    DNode* head = dummy.next;

    if (head != nullptr)
        head->prev = nullptr;

    return head;
}


/*
====================================================================
6. REVERSE SLL - ITERATIVE
====================================================================

Example:

1 -> 2 -> 3 -> NULL

becomes:

3 -> 2 -> 1 -> NULL


Three pointers:

prev
curr
next


At every step:

next = curr->next

curr->next = prev

prev = curr

curr = next


This is one of the MOST IMPORTANT linked-list
interview problems.

Time: O(n)
Space: O(1)
*/


SNode* reverseIterative(SNode* head)
{
    SNode* prev = nullptr;
    SNode* curr = head;

    while (curr != nullptr)
    {
        SNode* next = curr->next;

        curr->next = prev;

        prev = curr;

        curr = next;
    }

    return prev;
}


/*
====================================================================
7. REVERSE SLL - RECURSIVE
====================================================================

Example:

1 -> 2 -> 3

We recursively reverse:

2 -> 3

Then attach 1 at the end.

Key line:

head->next->next = head;

Then:

head->next = nullptr;


Time: O(n)
Space: O(n) because of recursion stack.
*/


SNode* reverseRecursive(SNode* head)
{
    // Base case
    if (head == nullptr ||
        head->next == nullptr)
    {
        return head;
    }

    SNode* newHead =
        reverseRecursive(head->next);

    head->next->next = head;

    head->next = nullptr;

    return newHead;
}


/*
====================================================================
8. LOOP DETECTION - FLOYD'S CYCLE ALGORITHM
====================================================================

Problem:

Detect whether a linked list contains a cycle.

Example:

1 -> 2 -> 3 -> 4
          ^    |
          |____|


Use two pointers:

slow -> moves 1 step
fast -> moves 2 steps

If they meet:

There is a cycle.

If fast reaches nullptr:

No cycle.


Time: O(n)
Space: O(1)

IMPORTANT:

This is called:

Floyd's Cycle Detection Algorithm

or

Tortoise and Hare Algorithm.
*/


bool hasLoop(SNode* head)
{
    SNode* slow = head;
    SNode* fast = head;

    while (fast != nullptr &&
           fast->next != nullptr)
    {
        slow = slow->next;

        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}


/*
====================================================================
9. FIND STARTING POINT OF LOOP
====================================================================

Suppose:

1 -> 2 -> 3 -> 4 -> 5
          ^         |
          |_________|


After slow and fast meet:

Reset slow to head.

Then move:

slow = slow->next
fast = fast->next

one step at a time.

Where they meet again is the starting point
of the loop.


Time: O(n)
Space: O(1)
*/


SNode* loopStart(SNode* head)
{
    SNode* slow = head;
    SNode* fast = head;

    // Step 1: Detect cycle
    while (fast != nullptr &&
           fast->next != nullptr)
    {
        slow = slow->next;

        fast = fast->next->next;

        if (slow == fast)
            break;
    }

    // No cycle
    if (fast == nullptr ||
        fast->next == nullptr)
    {
        return nullptr;
    }

    // Step 2: Find starting point
    slow = head;

    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}


/*
====================================================================
10. PALINDROME LINKED LIST
====================================================================

Example:

1 -> 2 -> 3 -> 2 -> 1

Palindrome -> YES


EFFICIENT APPROACH:

1. Find middle using slow/fast.
2. Reverse second half.
3. Compare first half and second half.

Time: O(n)
Space: O(1)


IMPORTANT INTERVIEW PATTERN:

Fast/slow pointer
+
Reverse linked list
+
Compare
*/


bool isPalindromeList(SNode* head)
{
    if (head == nullptr ||
        head->next == nullptr)
    {
        return true;
    }

    // Find middle
    SNode* slow = head;
    SNode* fast = head;

    while (fast->next != nullptr &&
           fast->next->next != nullptr)
    {
        slow = slow->next;

        fast = fast->next->next;
    }

    // Reverse second half
    SNode* secondHalf =
        reverseIterative(slow->next);

    SNode* firstHalf = head;

    SNode* temp = secondHalf;

    // Compare
    while (temp != nullptr)
    {
        if (firstHalf->data != temp->data)
            return false;

        firstHalf = firstHalf->next;
        temp = temp->next;
    }

    return true;
}


/*
====================================================================
11. CHECK IF LINKED LIST IS CIRCULAR
====================================================================

Important distinction:

A linked list is circular if eventually we return
to the HEAD.

Example:

1 -> 2 -> 3
     ^    |
     |____|

If last node points to head:

last->next == head


We can traverse until:

temp == head

But we must carefully handle NULL.


Time: O(n)
Space: O(1)
*/


bool isCircular(SNode* head)
{
    if (head == nullptr)
        return false;

    SNode* temp = head->next;

    while (temp != nullptr &&
           temp != head)
    {
        temp = temp->next;
    }

    return temp == head;
}


/*
====================================================================
12. MERGE SORT ON LINKED LIST
====================================================================

Why Merge Sort?

Linked lists are excellent for merge sort because
we don't need random access.

Steps:

1. Find middle.
2. Split list into two halves.
3. Recursively sort both halves.
4. Merge sorted halves.

Example:

4 -> 2 -> 1 -> 3

Split:

4 -> 2

1 -> 3

Sort:

2 -> 4

1 -> 3

Merge:

1 -> 2 -> 3 -> 4


Time: O(n log n)
Space: O(log n) recursion stack.


IMPORTANT:

Merge sort is generally preferred over quicksort
for linked lists.
*/


SNode* mergeSort(SNode* head)
{
    // Base case
    if (head == nullptr ||
        head->next == nullptr)
    {
        return head;
    }

    // Find middle
    SNode* slow = head;
    SNode* fast = head->next;

    while (fast != nullptr &&
           fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split
    SNode* second = slow->next;

    slow->next = nullptr;

    // Sort both halves
    SNode* left = mergeSort(head);
    SNode* right = mergeSort(second);

    // Merge
    return mergeSLL(left, right);
}


/*
====================================================================
13. QUICK SORT ON LINKED LIST
====================================================================

Quick Sort can also be implemented on linked lists.

Basic idea:

Choose a pivot.

Partition nodes into:

less than pivot
equal to pivot
greater than pivot

Then recursively sort the smaller parts.


However:

For linked lists, Merge Sort is generally preferred.

Why?

Merge sort:
- Doesn't require random access
- Easy to split using slow/fast
- Easy to merge by changing pointers

Quick sort:
- Partitioning is less convenient
- Performance depends on pivot choice


The implementation below uses the simpler
"data swapping" approach.

Time:
Average O(n log n)
Worst O(n^2)

Space:
O(log n) average recursion.
*/


SNode* getTail(SNode* head)
{
    while (head != nullptr &&
           head->next != nullptr)
    {
        head = head->next;
    }

    return head;
}


SNode* partitionList(SNode* head,
                     SNode* end,
                     SNode*& newHead,
                     SNode*& newEnd)
{
    SNode* pivot = end;

    SNode* prev = nullptr;
    SNode* curr = head;

    SNode* tail = pivot;

    newHead = nullptr;

    while (curr != pivot)
    {
        if (curr->data < pivot->data)
        {
            if (newHead == nullptr)
                newHead = curr;

            prev = curr;
            curr = curr->next;
        }
        else
        {
            /*
            Move current node after pivot.
            */

            if (prev != nullptr)
                prev->next = curr->next;

            SNode* temp = curr->next;

            curr->next = nullptr;

            tail->next = curr;

            tail = curr;

            curr = temp;
        }
    }

    if (newHead == nullptr)
        newHead = pivot;

    newEnd = tail;

    return pivot;
}


SNode* quickSortRecursive(SNode* head,
                          SNode* end)
{
    if (head == nullptr ||
        head == end)
    {
        return head;
    }

    SNode* newHead = nullptr;
    SNode* newEnd = nullptr;

    SNode* pivot =
        partitionList(
            head,
            end,
            newHead,
            newEnd
        );

    /*
    Sort left side
    */

    if (newHead != pivot)
    {
        SNode* temp = newHead;

        while (temp->next != pivot)
        {
            temp = temp->next;
        }

        temp->next = nullptr;

        newHead =
            quickSortRecursive(
                newHead,
                temp
            );

        temp = getTail(newHead);

        temp->next = pivot;
    }

    /*
    Sort right side
    */

    pivot->next =
        quickSortRecursive(
            pivot->next,
            newEnd
        );

    return newHead;
}


SNode* quickSort(SNode* head)
{
    SNode* end = getTail(head);

    return quickSortRecursive(head, end);
}


/*
====================================================================
14. ROTATE LINKED LIST
====================================================================

Problem:

Rotate the list to the RIGHT by k positions.

Example:

1 -> 2 -> 3 -> 4 -> 5

k = 2

Answer:

4 -> 5 -> 1 -> 2 -> 3


IDEA:

1. Find length.
2. Make the list temporarily circular.
3. Find the new tail.
4. Break the circle.


Example:

1 -> 2 -> 3 -> 4 -> 5
^                   |
|___________________|

Then break before 4.


Time: O(n)
Space: O(1)
*/


SNode* rotateRight(SNode* head, int k)
{
    if (head == nullptr ||
        head->next == nullptr ||
        k == 0)
    {
        return head;
    }

    // Find length and tail
    int length = 1;

    SNode* tail = head;

    while (tail->next != nullptr)
    {
        tail = tail->next;
        length++;
    }

    k = k % length;

    if (k == 0)
        return head;

    // Make circular
    tail->next = head;

    // Find new tail
    int steps = length - k;

    SNode* newTail = head;

    for (int i = 1; i < steps; i++)
    {
        newTail = newTail->next;
    }

    // New head
    SNode* newHead = newTail->next;

    // Break circle
    newTail->next = nullptr;

    return newHead;
}


/*
====================================================================
UTILITY FUNCTION
====================================================================
*/

void printList(SNode* head)
{
    while (head != nullptr)
    {
        cout << head->data << " -> ";
        head = head->next;
    }

    cout << "NULL\n";
}


/*
====================================================================
MAIN
====================================================================

Basic demonstration of the important operations.
====================================================================
*/

int main()
{
    /*
    ============================================================
    SINGLY LINKED LIST
    ============================================================
    */

    SNode* head = nullptr;

    insertBack(head, 10);
    insertBack(head, 20);
    insertBack(head, 30);

    insertFront(head, 5);

    cout << "SLL: ";
    printSLL(head);

    deleteFront(head);

    cout << "After deleting front: ";
    printSLL(head);

    deleteBack(head);

    cout << "After deleting back: ";
    printSLL(head);


    /*
    ============================================================
    DOUBLY LINKED LIST
    ============================================================
    */

    DNode* dhead = nullptr;

    insertBack(dhead, 10);
    insertBack(dhead, 20);
    insertBack(dhead, 30);

    insertFront(dhead, 5);

    cout << "\nDLL: ";
    printDLL(dhead);

    deleteFront(dhead);

    cout << "After deleting front: ";
    printDLL(dhead);

    deleteBack(dhead);

    cout << "After deleting back: ";
    printDLL(dhead);


    /*
    ============================================================
    CIRCULAR LINKED LIST
    ============================================================
    */

    CNode* chead = nullptr;

    insertBack(chead, 10);
    insertBack(chead, 20);
    insertBack(chead, 30);

    insertFront(chead, 5);

    cout << "\nCircular List: ";
    printCircular(chead);

    deleteFront(chead);

    cout << "After deleting front: ";
    printCircular(chead);

    deleteBack(chead);

    cout << "After deleting back: ";
    printCircular(chead);


    /*
    ============================================================
    MERGE TWO SORTED LISTS
    ============================================================
    */

    SNode* a = nullptr;
    SNode* b = nullptr;

    insertBack(a, 1);
    insertBack(a, 3);
    insertBack(a, 5);

    insertBack(b, 2);
    insertBack(b, 4);
    insertBack(b, 6);

    SNode* merged = mergeSLL(a, b);

    cout << "\nMerged SLL: ";
    printList(merged);


    /*
    ============================================================
    REVERSE
    ============================================================
    */

    SNode* r = nullptr;

    insertBack(r, 1);
    insertBack(r, 2);
    insertBack(r, 3);
    insertBack(r, 4);

    r = reverseIterative(r);

    cout << "\nIterative Reverse: ";
    printList(r);

    r = reverseRecursive(r);

    cout << "Recursive Reverse: ";
    printList(r);


    /*
    ============================================================
    PALINDROME
    ============================================================
    */

    SNode* p = nullptr;

    insertBack(p, 1);
    insertBack(p, 2);
    insertBack(p, 3);
    insertBack(p, 2);
    insertBack(p, 1);

    cout << "\nPalindrome: "
         << (isPalindromeList(p) ? "Yes" : "No")
         << endl;


    /*
    ============================================================
    MERGE SORT
    ============================================================
    */

    SNode* ms = nullptr;

    insertBack(ms, 4);
    insertBack(ms, 2);
    insertBack(ms, 1);
    insertBack(ms, 5);
    insertBack(ms, 3);

    ms = mergeSort(ms);

    cout << "\nMerge Sorted: ";
    printList(ms);


    /*
    ============================================================
    QUICK SORT
    ============================================================
    */

    SNode* qs = nullptr;

    insertBack(qs, 4);
    insertBack(qs, 1);
    insertBack(qs, 5);
    insertBack(qs, 2);
    insertBack(qs, 3);

    qs = quickSort(qs);

    cout << "Quick Sorted: ";
    printList(qs);


    /*
    ============================================================
    ROTATION
    ============================================================
    */

    SNode* rot = nullptr;

    insertBack(rot, 1);
    insertBack(rot, 2);
    insertBack(rot, 3);
    insertBack(rot, 4);
    insertBack(rot, 5);

    rot = rotateRight(rot, 2);

    cout << "\nRotated Right by 2: ";
    printList(rot);


    return 0;
}