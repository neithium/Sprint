#include <iostream>
#include <stack>
#include <vector>

using namespace std;


/*
====================================================================
                    RECURSION INTERVIEW SHEET
====================================================================

Topics covered:

1. Power of a number
2. Sort a Stack using Recursion
3. Reverse a Stack using Recursion
4. N-Queens Problem
5. Tower of Hanoi

====================================================================

RECURSION GOLDEN RULE:

Every recursive function needs:

1. BASE CASE
   -> When should recursion stop?

2. RECURSIVE CASE
   -> How do we reduce the problem?

Think:

    BIG PROBLEM
         |
         v
    SMALLER PROBLEM
         |
         v
    SMALLER PROBLEM
         |
         v
      BASE CASE

====================================================================
*/


/*
====================================================================
1. POWER OF A NUMBER
====================================================================

Problem:

Calculate:

x^n

Example:

2^5 = 2 * 2 * 2 * 2 * 2
    = 32


Recursive idea:

x^n = x * x^(n-1)

Example:

2^5
= 2 * 2^4
= 2 * 2 * 2^3
= 2 * 2 * 2 * 2^2
= ...
= 32


BASE CASE:

x^0 = 1


Time: O(n)
Space: O(n) recursion stack
*/

long long power(int x, int n)
{
    // Base case
    if (n == 0)
        return 1;

    // Recursive case
    return x * power(x, n - 1);
}


/*
====================================================================
1B. POWER - OPTIMIZED RECURSIVE VERSION
====================================================================

We can do better than O(n).

Use:

x^n

If n is even:

x^n = (x^(n/2)) * (x^(n/2))

If n is odd:

x^n = x * x^(n/2) * x^(n/2)


Example:

2^8

Instead of:

2 * 2 * 2 * 2 * 2 * 2 * 2 * 2

we calculate:

2^4
then:

2^2
then:

2^1

Time: O(log n)
Space: O(log n)
*/

long long fastPower(long long x, int n)
{
    if (n == 0)
        return 1;

    long long half = fastPower(x, n / 2);

    if (n % 2 == 0)
        return half * half;

    return x * half * half;
}


/*
====================================================================
2. SORT A STACK USING RECURSION
====================================================================

Problem:

Sort a stack so that the smallest element is at the top.

Example:

Input:

    | 3 |
    | 1 |
    | 2 |
    | 4 |

After sorting:

    | 1 |
    | 2 |
    | 3 |
    | 4 |


IMPORTANT:

We are NOT using another stack.

We only use recursion.

IDEA:

1. Remove the top element.
2. Recursively sort the remaining stack.
3. Insert the removed element into its correct position.

So:

sortStack(stack)

    remove top
        |
        v
    sort remaining stack
        |
        v
    insert removed element correctly


This uses TWO recursive functions:

sortStack()
insertSorted()


Time: O(n^2)
Space: O(n) recursion stack
*/


void insertSorted(stack<int>& st, int value)
{
    /*
    If stack is empty OR
    top is greater than value,

    value belongs at the top.
    */

    if (st.empty() || st.top() > value)
    {
        st.push(value);
        return;
    }

    /*
    Otherwise remove the top,
    recursively insert value,
    then restore the top.
    */

    int top = st.top();
    st.pop();

    insertSorted(st, value);

    st.push(top);
}


void sortStack(stack<int>& st)
{
    // Base case
    if (st.empty())
        return;

    // Remove top
    int top = st.top();
    st.pop();

    // Sort remaining stack
    sortStack(st);

    // Insert removed element correctly
    insertSorted(st, top);
}


/*
====================================================================
3. REVERSE A STACK USING RECURSION
====================================================================

Problem:

Reverse a stack without using another stack.

Example:

Before:

    | 1 |
    | 2 |
    | 3 |
    | 4 |

After:

    | 4 |
    | 3 |
    | 2 |
    | 1 |


IDEA:

Remove everything recursively until the stack becomes empty.

Then, while recursion returns,
insert each removed element at the BOTTOM.


Two functions:

reverseStack()
insertAtBottom()


Example:

Stack:

1 2 3

Remove 3
Remove 2
Remove 1

Stack is empty.

Now recursion returns:

insert 1 at bottom
insert 2 at bottom
insert 3 at bottom

Result:

3 2 1


Time: O(n^2)
Space: O(n)
*/


void insertAtBottom(stack<int>& st, int value)
{
    if (st.empty())
    {
        st.push(value);
        return;
    }

    int top = st.top();
    st.pop();

    insertAtBottom(st, value);

    st.push(top);
}


void reverseStack(stack<int>& st)
{
    // Base case
    if (st.empty())
        return;

    // Remove top
    int top = st.top();
    st.pop();

    // Reverse remaining stack
    reverseStack(st);

    // Put removed element at bottom
    insertAtBottom(st, top);
}


/*
====================================================================
4. N-QUEENS PROBLEM
====================================================================

Problem:

Place N queens on an N x N chessboard such that:

1. No two queens share the same row.
2. No two queens share the same column.
3. No two queens share the same diagonal.


Example for N = 4:

. Q . .
. . . Q
Q . . .
. . Q .


IDEA:

We place ONE queen per row.

For every row:

Try every column.

If placing a queen there is safe:

    place queen
        |
        v
    recursively solve next row
        |
        v
    if it fails:
        remove queen
        try another column


This is BACKTRACKING.


BACKTRACKING PATTERN:

choose
   ↓
explore
   ↓
undo


Time:

O(N!)

approximately, in the typical backtracking analysis.

Space:

O(N^2) for the board
+
O(N) recursion
*/


bool isSafe(vector<vector<int>>& board,
            int row,
            int col,
            int n)
{
    /*
    ------------------------------------------------------------
    1. Check same column
    ------------------------------------------------------------
    */

    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
            return false;
    }


    /*
    ------------------------------------------------------------
    2. Check upper-left diagonal
    ------------------------------------------------------------
    */

    int i = row - 1;
    int j = col - 1;

    while (i >= 0 && j >= 0)
    {
        if (board[i][j] == 1)
            return false;

        i--;
        j--;
    }


    /*
    ------------------------------------------------------------
    3. Check upper-right diagonal
    ------------------------------------------------------------
    */

    i = row - 1;
    j = col + 1;

    while (i >= 0 && j < n)
    {
        if (board[i][j] == 1)
            return false;

        i--;
        j++;
    }


    return true;
}


bool solveNQueens(vector<vector<int>>& board,
                  int row,
                  int n)
{
    /*
    BASE CASE:

    If we successfully placed queens
    in all rows, solution exists.
    */

    if (row == n)
        return true;


    /*
    Try every column in this row.
    */

    for (int col = 0; col < n; col++)
    {
        if (isSafe(board, row, col, n))
        {
            // Choose
            board[row][col] = 1;

            // Explore
            if (solveNQueens(board, row + 1, n))
                return true;

            // Undo
            board[row][col] = 0;
        }
    }

    return false;
}


void printBoard(vector<vector<int>>& board)
{
    for (auto row : board)
    {
        for (int cell : row)
        {
            if (cell == 1)
                cout << "Q ";
            else
                cout << ". ";
        }

        cout << endl;
    }
}


void nQueens(int n)
{
    vector<vector<int>> board(
        n,
        vector<int>(n, 0)
    );

    if (solveNQueens(board, 0, n))
    {
        cout << "N-Queens Solution:\n";
        printBoard(board);
    }
    else
    {
        cout << "No solution exists.\n";
    }
}


/*
====================================================================
5. TOWER OF HANOI
====================================================================

Problem:

We have three rods:

Source
Auxiliary
Destination


Example:

       |              |              |
      [1]             |              |
     [ 2 ]            |              |
    [  3  ]           |              |

Move all disks from Source to Destination.


RULES:

1. Move only one disk at a time.
2. Only the top disk can be moved.
3. A larger disk cannot be placed on a smaller disk.


RECURSIVE IDEA:

To move n disks from:

Source -> Destination

we need:

1. Move n-1 disks:
   Source -> Auxiliary

2. Move largest disk:
   Source -> Destination

3. Move n-1 disks:
   Auxiliary -> Destination


So:

hanoi(n, source, auxiliary, destination)

    hanoi(n-1, source, destination, auxiliary)

    move largest disk

    hanoi(n-1, auxiliary, source, destination)


BASE CASE:

If n == 1:

Simply move the disk.


NUMBER OF MOVES:

2^n - 1


Time: O(2^n)
Space: O(n)
*/


void towerOfHanoi(int n,
                  char source,
                  char auxiliary,
                  char destination)
{
    // Base case
    if (n == 1)
    {
        cout << "Move disk 1 from "
             << source
             << " to "
             << destination
             << endl;

        return;
    }


    // Move n-1 disks to auxiliary
    towerOfHanoi(
        n - 1,
        source,
        destination,
        auxiliary
    );


    // Move largest disk
    cout << "Move disk "
         << n
         << " from "
         << source
         << " to "
         << destination
         << endl;


    // Move n-1 disks to destination
    towerOfHanoi(
        n - 1,
        auxiliary,
        source,
        destination
    );
}


/*
====================================================================
UTILITY FUNCTION
====================================================================
*/

void printStack(stack<int> st)
{
    cout << "Stack: ";

    while (!st.empty())
    {
        cout << st.top() << " ";

        st.pop();
    }

    cout << endl;
}


/*
====================================================================
MAIN
====================================================================
*/

int main()
{
    /*
    ================================================================
    1. POWER
    ================================================================
    */

    cout << "2^5 = "
         << power(2, 5)
         << endl;


    /*
    ================================================================
    1B. FAST POWER
    ================================================================
    */

    cout << "Fast 2^10 = "
         << fastPower(2, 10)
         << endl;


    /*
    ================================================================
    2. SORT STACK
    ================================================================
    */

    stack<int> s1;

    s1.push(3);
    s1.push(1);
    s1.push(4);
    s1.push(2);

    cout << "\nBefore sorting:\n";
    printStack(s1);

    sortStack(s1);

    cout << "After sorting:\n";
    printStack(s1);


    /*
    ================================================================
    3. REVERSE STACK
    ================================================================
    */

    stack<int> s2;

    s2.push(1);
    s2.push(2);
    s2.push(3);
    s2.push(4);

    cout << "\nBefore reversing:\n";
    printStack(s2);

    reverseStack(s2);

    cout << "After reversing:\n";
    printStack(s2);


    /*
    ================================================================
    4. N-QUEENS
    ================================================================
    */

    cout << "\nN-Queens:\n";

    nQueens(4);


    /*
    ================================================================
    5. TOWER OF HANOI
    ================================================================
    */

    cout << "\nTower of Hanoi:\n";

    towerOfHanoi(
        3,
        'A',
        'B',
        'C'
    );


    return 0;
}