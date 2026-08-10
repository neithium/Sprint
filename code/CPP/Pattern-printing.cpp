#include <iostream>
using namespace std;

/*
============================================================
PATTERN PROBLEMS
============================================================

IMPORTANT IDEA:

Almost every pattern problem uses:

    for (each row)
    {
        for (each column)
        {
            print something;
        }

        cout << endl;
    }

The main question is:

    "How many things do I print in each row?"

For most beginner patterns:

Row 1 -> something
Row 2 -> something something
Row 3 -> something something something
...

Learn the relationship between:

    row number
    number of spaces
    number of stars/numbers
============================================================
*/


/*
============================================================
1. RIGHT HALF PYRAMID
============================================================

Problem:

Print:

*
**
***
****
*****

For n = 5.

Observation:

Row 1 -> 1 star
Row 2 -> 2 stars
Row 3 -> 3 stars
Row 4 -> 4 stars
Row 5 -> 5 stars

Therefore:

number of stars = row

Pattern:

for i = 1 to n
    print i stars
*/
void rightHalfPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << "* ";
        }

        cout << endl;
    }
}


/*
============================================================
2. INVERTED RIGHT HALF PYRAMID
============================================================

Problem:

Print:

*****
****
***
**
*

Observation:

Row 1 -> 5 stars
Row 2 -> 4 stars
Row 3 -> 3 stars
Row 4 -> 2 stars
Row 5 -> 1 star

Number of stars:

n - i + 1

*/
void invertedRightHalfPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i + 1; j++)
        {
            cout << "* ";
        }

        cout << endl;
    }
}


/*
============================================================
3. FULL PYRAMID
============================================================

Problem:

Print:

    *
   ***
  *****
 *******
*********

For n = 5.

There are TWO things to understand:

1. Spaces
2. Stars

For row i:

Spaces = n - i
Stars  = 2*i - 1

Example:

Row 1:
Spaces = 4
Stars  = 1

Row 2:
Spaces = 3
Stars  = 3

Row 3:
Spaces = 2
Stars  = 5

Row 4:
Spaces = 1
Stars = 7

Row 5:
Spaces = 0
Stars = 9
*/
void fullPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        // Print spaces
        for (int j = 1; j <= n - i; j++)
        {
            cout << " ";
        }

        // Print stars
        for (int j = 1; j <= 2 * i - 1; j++)
        {
            cout << "*";
        }

        cout << endl;
    }
}


/*
============================================================
4. INVERTED FULL PYRAMID
============================================================

Problem:

Print:

*********
 *******
  *****
   ***
    *

Observation:

Spaces increase.

Stars decrease.

For row i:

Spaces = i - 1
Stars  = 2*(n-i) + 1

*/
void invertedFullPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        // Spaces
        for (int j = 1; j <= i - 1; j++)
        {
            cout << " ";
        }

        // Stars
        for (int j = 1; j <= 2 * (n - i) + 1; j++)
        {
            cout << "*";
        }

        cout << endl;
    }
}


/*
============================================================
5. DIAMOND
============================================================

Problem:

Print:

    *
   ***
  *****
 *******
  *****
   ***
    *

A diamond is simply:

    Full Pyramid
        +
    Inverted Pyramid

The second half starts from n-1,
otherwise the middle row gets printed twice.
*/
void diamond(int n)
{
    // Upper half
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            cout << " ";
        }

        for (int j = 1; j <= 2 * i - 1; j++)
        {
            cout << "*";
        }

        cout << endl;
    }

    // Lower half
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = 1; j <= n - i; j++)
        {
            cout << " ";
        }

        for (int j = 1; j <= 2 * i - 1; j++)
        {
            cout << "*";
        }

        cout << endl;
    }
}


/*
============================================================
6. NUMBER PYRAMID
============================================================

Problem:

Print:

    1
   123
  12345
 1234567

For each row:

Spaces = n - i
Numbers = 2*i - 1

The only difference from the star pyramid
is that we print numbers instead of stars.
*/
void numberPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        // Spaces
        for (int j = 1; j <= n - i; j++)
        {
            cout << " ";
        }

        // Numbers
        for (int j = 1; j <= 2 * i - 1; j++)
        {
            cout << j;
        }

        cout << endl;
    }
}


/*
============================================================
7. SAME NUMBER PYRAMID
============================================================

Problem:

Print:

    1
   222
  33333
 4444444
555555555

Observation:

Row i prints:

    number i

    exactly 2*i - 1 times
*/
void sameNumberPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        // Spaces
        for (int j = 1; j <= n - i; j++)
        {
            cout << " ";
        }

        // Same number
        for (int j = 1; j <= 2 * i - 1; j++)
        {
            cout << i;
        }

        cout << endl;
    }
}


/*
============================================================
8. INVERTED NUMBER PYRAMID
============================================================

Problem:

Print:

123456789
 1234567
  12345
   123
    1

For row i:

Spaces = i - 1
Numbers = 2*(n-i) + 1
*/
void invertedNumberPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        // Spaces
        for (int j = 1; j <= i - 1; j++)
        {
            cout << " ";
        }

        // Numbers
        for (int j = 1; j <= 2 * (n - i) + 1; j++)
        {
            cout << j;
        }

        cout << endl;
    }
}


/*
============================================================
9. HOLLOW PYRAMID
============================================================

Problem:

Print:

    *
   * *
  *   *
 *     *
*********

Unlike the full pyramid, we don't print every star.

We print:

1. First star
2. Last star
3. Entire bottom row

Condition:

    j == 1
    OR
    j == number_of_stars
    OR
    i == n
*/
void hollowPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        // Spaces
        for (int j = 1; j <= n - i; j++)
        {
            cout << " ";
        }

        // Pyramid width
        int width = 2 * i - 1;

        for (int j = 1; j <= width; j++)
        {
            if (j == 1 || j == width || i == n)
                cout << "*";
            else
                cout << " ";
        }

        cout << endl;
    }
}


/*
============================================================
10. HOLLOW INVERTED PYRAMID
============================================================

Problem:

*********
 *     *
  *   *
   * *
    *

Again:

Print stars only at the boundaries.

The first row is completely filled.

For other rows:

    first position -> *
    last position  -> *
*/
void hollowInvertedPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        // Spaces
        for (int j = 1; j <= i - 1; j++)
        {
            cout << " ";
        }

        int width = 2 * (n - i) + 1;

        for (int j = 1; j <= width; j++)
        {
            if (j == 1 || j == width || i == 1)
                cout << "*";
            else
                cout << " ";
        }

        cout << endl;
    }
}


/*
============================================================
11. FLOYD'S TRIANGLE
============================================================

Problem:

Print:

1
2 3
4 5 6
7 8 9 10

Unlike previous patterns, the number does NOT reset
for every row.

We maintain one variable:

num

and keep increasing it.
*/
void floydsTriangle(int n)
{
    int num = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << num << " ";
            num++;
        }

        cout << endl;
    }
}


/*
============================================================
12. 0-1 TRIANGLE
============================================================

Problem:

Print:

1
01
101
0101
10101

Observation:

If:

    (row + column) is even
        print 1

    otherwise
        print 0
*/
void zeroOneTriangle(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if ((i + j) % 2 == 0)
                cout << "1";
            else
                cout << "0";
        }

        cout << endl;
    }
}


/*
============================================================
MAIN
============================================================

Change n and call whichever pattern you want to practice.

For interview preparation, don't just run them.

Try writing each function yourself after seeing
the pattern once.
*/
int main()
{
    int n = 5;

    cout << "\n1. Right Half Pyramid\n";
    rightHalfPyramid(n);

    cout << "\n2. Inverted Right Half Pyramid\n";
    invertedRightHalfPyramid(n);

    cout << "\n3. Full Pyramid\n";
    fullPyramid(n);

    cout << "\n4. Inverted Full Pyramid\n";
    invertedFullPyramid(n);

    cout << "\n5. Diamond\n";
    diamond(n);

    cout << "\n6. Number Pyramid\n";
    numberPyramid(n);

    cout << "\n7. Same Number Pyramid\n";
    sameNumberPyramid(n);

    cout << "\n8. Inverted Number Pyramid\n";
    invertedNumberPyramid(n);

    cout << "\n9. Hollow Pyramid\n";
    hollowPyramid(n);

    cout << "\n10. Hollow Inverted Pyramid\n";
    hollowInvertedPyramid(n);

    cout << "\n11. Floyd's Triangle\n";
    floydsTriangle(n);

    cout << "\n12. 0-1 Triangle\n";
    zeroOneTriangle(n);

    return 0;
}