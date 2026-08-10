#include <iostream>
#include <cmath>
using namespace std;

/*
============================================================
1. COUNT DIGITS
============================================================

Problem:
Given an integer n, count how many digits it contains.

Example:
n = 12345
Answer = 5

Idea:
Keep dividing the number by 10.
Every division removes the last digit.

12345 -> 1234 -> 123 -> 12 -> 1 -> 0

Number of divisions = number of digits.
*/
int countDigits(int n)
{
    if (n == 0)
        return 1;

    int count = 0;

    while (n != 0)
    {
        n /= 10;
        count++;
    }

    return count;
}


/*
============================================================
2. REVERSE A NUMBER
============================================================

Problem:
Reverse the digits of a number.

Example:
n = 12345
Answer = 54321

Idea:
Take the last digit using % 10.
Add it to the reversed number.
Remove the last digit using / 10.

Example:

12345
last digit = 5
reverse = 5

1234
last digit = 4
reverse = 54

...and so on.
*/
int reverseNumber(int n)
{
    int reverse = 0;

    while (n != 0)
    {
        int digit = n % 10;
        reverse = reverse * 10 + digit;
        n /= 10;
    }

    return reverse;
}


/*
============================================================
3. PALINDROME NUMBER
============================================================

Problem:
Check whether a number reads the same forwards and backwards.

Example:
121 -> Palindrome
123 -> Not Palindrome

Idea:
Store the original number.
Reverse the number.
Compare original and reversed.

If they are equal -> palindrome.
*/
bool isPalindrome(int n)
{
    int original = n;
    int reverse = reverseNumber(n);

    return original == reverse;
}


/*
============================================================
4. GCD / HCF
============================================================

Problem:
Find the Greatest Common Divisor (GCD/HCF) of two numbers.

Example:
12 and 18

Factors of 12: 1,2,3,4,6,12
Factors of 18: 1,2,3,6,9,18

GCD = 6

Best simple method:
Euclidean Algorithm

gcd(a,b) = gcd(b, a%b)

Keep doing this until b becomes 0.
*/
int gcd(int a, int b)
{
    while (b != 0)
    {
        int remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}


/*
============================================================
5. ARMSTRONG NUMBER
============================================================

Problem:
Check whether a number is an Armstrong number.

For a 3-digit number:
Sum of cubes of digits = original number.

Example:
153

1^3 + 5^3 + 3^3
= 1 + 125 + 27
= 153

Therefore 153 is an Armstrong number.

For a general n-digit number:
Raise every digit to the power of number of digits.
*/
bool isArmstrong(int n)
{
    int original = n;
    int digits = countDigits(n);

    int sum = 0;

    while (n != 0)
    {
        int digit = n % 10;

        sum += pow(digit, digits);

        n /= 10;
    }

    return sum == original;
}


/*
============================================================
6. PRIME NUMBER
============================================================

Problem:
Check whether a number is prime.

A prime number:
- is greater than 1
- has exactly two factors:
  1 and itself

Examples:
2 -> Prime
3 -> Prime
4 -> Not Prime
7 -> Prime

We only check divisors up to sqrt(n).

Why?
If n = a*b and both a and b were greater than sqrt(n),
their product would be greater than n.
*/
bool isPrime(int n)
{
    if (n < 2)
        return false;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}


/*
============================================================
7. EVEN OR ODD
============================================================

Problem:
Check whether a number is even or odd.

Idea:
A number is even if it is completely divisible by 2.

n % 2 == 0 -> Even
n % 2 != 0 -> Odd
*/
bool isEven(int n)
{
    return n % 2 == 0;
}


/*
============================================================
8. LEAP YEAR
============================================================

Problem:
Check whether a year is a leap year.

Rules:

1. If divisible by 400 -> Leap Year

OR

2. If divisible by 4 AND NOT divisible by 100
   -> Leap Year

Otherwise -> Not Leap Year

Examples:
2024 -> Leap Year
1900 -> Not Leap Year
2000 -> Leap Year
*/
bool isLeapYear(int year)
{
    if (year % 400 == 0)
        return true;

    if (year % 4 == 0 && year % 100 != 0)
        return true;

    return false;
}


/*
============================================================
9. FACTORIAL OF N
============================================================

Problem:
Calculate n!

Example:

5! = 5 * 4 * 3 * 2 * 1
   = 120

Important:
0! = 1

Simple iterative solution is easiest to remember.
*/
long long factorial(int n)
{
    long long fact = 1;

    for (int i = 1; i <= n; i++)
    {
        fact *= i;
    }

    return fact;
}


/*
============================================================
10. FIBONACCI SEQUENCE
============================================================

Problem:
Print the first n Fibonacci numbers.

Fibonacci:

0 1 1 2 3 5 8 13 ...

Every number is the sum of the previous two.

next = first + second

Then shift:

first = second
second = next
*/
void fibonacci(int n)
{
    int first = 0;
    int second = 1;

    for (int i = 0; i < n; i++)
    {
        cout << first << " ";

        int next = first + second;

        first = second;
        second = next;
    }

    cout << endl;
}


/*
============================================================
11. SUM OF FIRST N NUMBERS
============================================================

Problem:
Find:

1 + 2 + 3 + ... + n

Example:
n = 5

1 + 2 + 3 + 4 + 5 = 15

Two common methods:

1. Loop
2. Formula

Formula:
sum = n * (n + 1) / 2

For interviews, remember this formula.
*/
long long sumOfN(int n)
{
    return 1LL * n * (n + 1) / 2;
}


/*
============================================================
MAIN
============================================================

This program demonstrates all the above functions.

Change n/a/b/year to test different cases.
*/
int main()
{
    int n = 153;

    // 1. Count digits
    cout << "Digits: "
         << countDigits(n) << endl;


    // 2. Reverse number
    cout << "Reverse: "
         << reverseNumber(n) << endl;


    // 3. Palindrome
    cout << "Palindrome: "
         << (isPalindrome(n) ? "Yes" : "No")
         << endl;


    // 4. GCD / HCF
    int a = 12;
    int b = 18;

    cout << "GCD: "
         << gcd(a, b) << endl;


    // 5. Armstrong
    cout << "Armstrong: "
         << (isArmstrong(n) ? "Yes" : "No")
         << endl;


    // 6. Prime
    cout << "Prime: "
         << (isPrime(n) ? "Yes" : "No")
         << endl;


    // 7. Even / Odd
    cout << "Even/Odd: "
         << (isEven(n) ? "Even" : "Odd")
         << endl;


    // 8. Leap Year
    int year = 2024;

    cout << "Leap Year: "
         << (isLeapYear(year) ? "Yes" : "No")
         << endl;


    // 9. Factorial
    int factN = 5;

    cout << "Factorial: "
         << factorial(factN) << endl;


    // 10. Fibonacci
    int fibN = 10;

    cout << "Fibonacci: ";
    fibonacci(fibN);


    // 11. Sum of first N numbers
    int sumN = 10;

    cout << "Sum of first N numbers: "
         << sumOfN(sumN) << endl;


    return 0;
}