#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <cctype>

using namespace std;


/*
============================================================
1. REVERSE A STRING
============================================================

Problem:
Reverse a given string.

Example:

Input:
"hello"

Output:
"olleh"

Simple idea:

Use two pointers:

left  -> beginning
right -> end

Swap characters and move towards the middle.

Time:  O(n)
Space: O(1)
*/
void reverseString(string& s)
{
    int left = 0;
    int right = s.length() - 1;

    while (left < right)
    {
        swap(s[left], s[right]);

        left++;
        right--;
    }
}


/*
============================================================
2. PALINDROME
============================================================

Problem:
Check whether a string reads the same forwards
and backwards.

Examples:

"madam" -> Palindrome
"racecar" -> Palindrome
"hello" -> Not Palindrome

Idea:

Compare:

first  with last
second with second-last
...

If any pair is different -> Not Palindrome.

Time:  O(n)
Space: O(1)
*/
bool isPalindrome(string s)
{
    int left = 0;
    int right = s.length() - 1;

    while (left < right)
    {
        if (s[left] != s[right])
            return false;

        left++;
        right--;
    }

    return true;
}


/*
============================================================
3. DUPLICATES IN A STRING
============================================================

Problem:
Find duplicate characters in a string.

Example:

Input:
"programming"

Duplicates:
r
g
m

Idea:

Use a frequency array.

For ASCII characters:

freq[256]

Count every character.

If frequency > 1,
that character is duplicated.

Time:  O(n)
Space: O(1)

Because the character set is fixed (256 ASCII characters).
*/
void printDuplicates(string s)
{
    int freq[256] = {0};

    for (char c : s)
    {
        freq[(unsigned char)c]++;
    }

    cout << "Duplicate characters: ";

    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 1)
        {
            cout << (char)i << " ";
        }
    }

    cout << endl;
}


/*
============================================================
4. LONGEST COMMON PREFIX
============================================================

Problem:
Given multiple strings, find their longest common prefix.

Example:

flower
flow
flight

Answer:

"fl"

Idea:

Start with the first string as the prefix.

Then compare it with every other string.

If characters stop matching,
shorten the prefix.

Time: O(total characters)
Space: O(1) extra
*/
string longestCommonPrefix(vector<string>& strs)
{
    if (strs.empty())
        return "";

    string prefix = strs[0];

    for (int i = 1; i < strs.size(); i++)
    {
        int j = 0;

        while (j < prefix.length() &&
               j < strs[i].length() &&
               prefix[j] == strs[i][j])
        {
            j++;
        }

        prefix = prefix.substr(0, j);

        if (prefix.empty())
            return "";
    }

    return prefix;
}


/*
============================================================
5. ANAGRAM
============================================================

Problem:
Check whether two strings are anagrams.

Anagrams contain exactly the same characters
with the same frequencies.

Examples:

"listen"
"silent"

-> Anagrams

"hello"
"world"

-> Not Anagrams


IDEA:

Count characters in both strings.

If all frequencies match -> Anagram.

Time: O(n)
Space: O(1) for fixed ASCII alphabet.
*/
bool areAnagrams(string a, string b)
{
    if (a.length() != b.length())
        return false;

    int freq[256] = {0};

    for (char c : a)
        freq[(unsigned char)c]++;

    for (char c : b)
        freq[(unsigned char)c]--;

    for (int i = 0; i < 256; i++)
    {
        if (freq[i] != 0)
            return false;
    }

    return true;
}


/*
============================================================
6. PANAGRAM
============================================================

Problem:
Check whether a sentence contains every letter
of the English alphabet at least once.

Example:

"The quick brown fox jumps over the lazy dog"

-> Pangram


IDEA:

Use an array of size 26.

Convert each character to lowercase.

For:

'a' -> index 0
'b' -> index 1
...
'z' -> index 25

Then check whether all 26 positions were found.

Time: O(n)
Space: O(1)
*/
bool isPangram(string s)
{
    bool present[26] = {false};

    for (char c : s)
    {
        c = tolower((unsigned char)c);

        if (c >= 'a' && c <= 'z')
        {
            present[c - 'a'] = true;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (!present[i])
            return false;
    }

    return true;
}


/*
============================================================
7. ROMAN TO INTEGER
============================================================

Problem:
Convert a Roman numeral to an integer.

Examples:

III   -> 3
IV    -> 4
IX    -> 9
LVIII -> 58
MCMXCIV -> 1994


Roman values:

I = 1
V = 5
X = 10
L = 50
C = 100
D = 500
M = 1000


IMPORTANT RULE:

Normally we ADD.

But if the current value is smaller than
the next value, we SUBTRACT.

Example:

IV

I = 1
V = 5

Since:

1 < 5

answer = answer - 1

Then add 5.

Result = 4


Time: O(n)
Space: O(1)
*/
int romanToInteger(string s)
{
    unordered_map<char, int> value =
    {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };

    int answer = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (i + 1 < s.length() &&
            value[s[i]] < value[s[i + 1]])
        {
            answer -= value[s[i]];
        }
        else
        {
            answer += value[s[i]];
        }
    }

    return answer;
}


/*
============================================================
8. BALANCED PARENTHESES
============================================================

Problem:
Check whether brackets are properly balanced.

Examples:

"()[]{}"
-> Balanced

"([{}])"
-> Balanced

"([)]"
-> Not Balanced

"(]"
-> Not Balanced


IDEA:

Use a STACK.

Opening bracket:

(
[
{

-> push into stack.

Closing bracket:

)
]
}

-> check whether it matches the top.

If it matches:
pop.

At the end:

stack empty -> Balanced
stack not empty -> Not Balanced


Time: O(n)
Space: O(n)
*/
bool isBalanced(string s)
{
    stack<char> st;

    for (char c : s)
    {
        // Opening brackets
        if (c == '(' ||
            c == '[' ||
            c == '{')
        {
            st.push(c);
        }

        // Closing brackets
        else
        {
            if (st.empty())
                return false;

            char top = st.top();
            st.pop();

            if (c == ')' && top != '(')
                return false;

            if (c == ']' && top != '[')
                return false;

            if (c == '}' && top != '{')
                return false;
        }
    }

    return st.empty();
}


/*
============================================================
9. KMP ALGORITHM
============================================================

Problem:
Find whether a pattern exists inside a text.

Example:

Text:
"ababcabcabababd"

Pattern:
"ababd"

Pattern exists.

KMP = Knuth-Morris-Pratt


WHY KMP?

Naive string matching can repeatedly compare
the same characters.

KMP avoids unnecessary comparisons.


CORE IDEA:

Build an LPS array.

LPS =
Longest Proper Prefix which is also a Suffix.

Example:

Pattern:
"abab"

LPS:

0 0 1 2


The LPS array tells us where we can continue
after a mismatch.


TWO STEPS:

1. Build LPS array
2. Use LPS to search


Time:
O(n + m)

n = text length
m = pattern length

This is much better than naive O(n*m).
*/
vector<int> buildLPS(string pattern)
{
    int n = pattern.length();

    vector<int> lps(n, 0);

    int len = 0;
    int i = 1;

    while (i < n)
    {
        if (pattern[i] == pattern[len])
        {
            len++;

            lps[i] = len;

            i++;
        }
        else
        {
            if (len != 0)
            {
                /*
                Do NOT move i.

                Try the next smaller prefix.
                */
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}


/*
KMP SEARCH

Returns the starting index of pattern
inside text.

If not found:

return -1
*/
int KMP(string text, string pattern)
{
    if (pattern.empty())
        return 0;

    vector<int> lps = buildLPS(pattern);

    int i = 0; // text index
    int j = 0; // pattern index

    while (i < text.length())
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;

            // Entire pattern matched
            if (j == pattern.length())
            {
                return i - j;
            }
        }
        else
        {
            if (j != 0)
            {
                /*
                Pattern mismatch.

                Don't restart from zero.

                Use LPS information.
                */
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return -1;
}


/*
============================================================
10. LONGEST PALINDROMIC SUBSTRING
============================================================

Problem:
Find the longest substring that is a palindrome.

Example:

Input:
"babad"

Possible answers:

"bab"
"aba"

Both have length 3.


IMPORTANT:

Substring means CONTIGUOUS.

"bba" is not a substring of "babad".


EASY INTERVIEW APPROACH:

Expand Around Center.

Every palindrome has a center.

Examples:

"aba"

    a
   / \
  b   b

Center = 'b'


For odd length:
center is one character.

For even length:
center is between two characters.


For every index:

1. Expand from (i, i)
   -> odd-length palindrome

2. Expand from (i, i+1)
   -> even-length palindrome


Time: O(n^2)
Space: O(1)
*/
string longestPalindrome(string s)
{
    if (s.empty())
        return "";

    int start = 0;
    int maxLength = 1;


    /*
    Lambda to expand around a center.

    left and right represent the center.
    */
    auto expand = [&](int left, int right)
    {
        while (left >= 0 &&
               right < s.length() &&
               s[left] == s[right])
        {
            left--;
            right++;
        }

        /*
        We went one step too far.

        Actual palindrome is:

        left + 1 ... right - 1
        */

        int length = right - left - 1;

        if (length > maxLength)
        {
            maxLength = length;

            start = left + 1;
        }
    };


    for (int i = 0; i < s.length(); i++)
    {
        // Odd length palindrome
        expand(i, i);

        // Even length palindrome
        expand(i, i + 1);
    }

    return s.substr(start, maxLength);
}


/*
============================================================
MAIN
============================================================

All problems are demonstrated below.
*/
int main()
{
    /*
    --------------------------------------------------------
    1. Reverse String
    --------------------------------------------------------
    */

    string s1 = "hello";

    reverseString(s1);

    cout << "Reversed String: "
         << s1 << endl;


    /*
    --------------------------------------------------------
    2. Palindrome
    --------------------------------------------------------
    */

    string s2 = "madam";

    cout << "Palindrome: "
         << (isPalindrome(s2) ? "Yes" : "No")
         << endl;


    /*
    --------------------------------------------------------
    3. Duplicate Characters
    --------------------------------------------------------
    */

    string s3 = "programming";

    printDuplicates(s3);


    /*
    --------------------------------------------------------
    4. Longest Common Prefix
    --------------------------------------------------------
    */

    vector<string> words =
    {
        "flower",
        "flow",
        "flight"
    };

    cout << "Longest Common Prefix: "
         << longestCommonPrefix(words)
         << endl;


    /*
    --------------------------------------------------------
    5. Anagram
    --------------------------------------------------------
    */

    string a = "listen";
    string b = "silent";

    cout << "Anagram: "
         << (areAnagrams(a, b) ? "Yes" : "No")
         << endl;


    /*
    --------------------------------------------------------
    6. Pangram
    --------------------------------------------------------
    */

    string sentence =
        "The quick brown fox jumps over the lazy dog";

    cout << "Pangram: "
         << (isPangram(sentence) ? "Yes" : "No")
         << endl;


    /*
    --------------------------------------------------------
    7. Roman to Integer
    --------------------------------------------------------
    */

    string roman = "MCMXCIV";

    cout << "Roman to Integer: "
         << romanToInteger(roman)
         << endl;


    /*
    --------------------------------------------------------
    8. Balanced Parentheses
    --------------------------------------------------------
    */

    string brackets = "([{}])";

    cout << "Balanced Parentheses: "
         << (isBalanced(brackets) ? "Yes" : "No")
         << endl;


    /*
    --------------------------------------------------------
    9. KMP
    --------------------------------------------------------
    */

    string text = "ababcabcabababd";
    string pattern = "ababd";

    cout << "KMP Pattern Index: "
         << KMP(text, pattern)
         << endl;


    /*
    --------------------------------------------------------
    10. Longest Palindromic Substring
    --------------------------------------------------------
    */

    string palindromeString = "babad";

    cout << "Longest Palindromic Substring: "
         << longestPalindrome(palindromeString)
         << endl;


    return 0;
}