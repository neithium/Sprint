# C++ Interview — What to Memorize Cheat Sheet

> **Purpose:** Fast interview revision.  
> Do not memorize entire programs. Memorize the **core pattern, invariant, and key lines**.

---

# 1. Sorting

## Bubble Sort

### Memorize
- Compare adjacent elements.
- Swap if they are in the wrong order.
- After every pass, the largest unsorted element moves to the end.
- **Optimization:** if a complete pass makes no swaps, the array is already sorted.

### Key code

```cpp
for(int i = 0; i < n - 1; i++)
{
    bool swapped = false;

    for(int j = 0; j < n - i - 1; j++)
    {
        if(a[j] > a[j + 1])
        {
            swap(a[j], a[j + 1]);
            swapped = true;
        }
    }

    if(!swapped)
        break;
}
```

### Complexity
- Best: `O(n)` with optimization
- Average/Worst: `O(n^2)`
- Space: `O(1)`

---

## Selection Sort

### Memorize
> Find the minimum in the unsorted portion and put it at the front.

```cpp
for(int i = 0; i < n - 1; i++)
{
    int minIndex = i;

    for(int j = i + 1; j < n; j++)
    {
        if(a[j] < a[minIndex])
            minIndex = j;
    }

    swap(a[i], a[minIndex]);
}
```

- Time: `O(n^2)`
- Space: `O(1)`

---

## Insertion Sort

### Memorize
> Take one element and insert it into the correct position in the already-sorted left portion.

```cpp
for(int i = 1; i < n; i++)
{
    int key = a[i];
    int j = i - 1;

    while(j >= 0 && a[j] > key)
    {
        a[j + 1] = a[j];
        j--;
    }

    a[j + 1] = key;
}
```

- Best: `O(n)`
- Worst: `O(n^2)`
- Stable
- Good for nearly sorted arrays

---

## Merge Sort

### Memorize

```text
Divide
  ↓
Sort left
  ↓
Sort right
  ↓
Merge
```

Key idea:

> Merge two sorted halves using two pointers.

- Time: `O(n log n)`
- Array space: `O(n)`
- Stable

---

# 2. Arrays

## Reverse an Array

### Memorize
> Two pointers: `left` and `right`.

```cpp
int l = 0, r = n - 1;

while(l < r)
{
    swap(a[l], a[r]);
    l++;
    r--;
}
```

---

## Minimum and Maximum

### Memorize
> One pass, maintain `min` and `max`.

```cpp
int mn = a[0];
int mx = a[0];

for(int x : a)
{
    mn = min(mn, x);
    mx = max(mx, x);
}
```

Time: `O(n)`

---

## Second Largest

### Memorize
> Maintain `largest` and `secondLargest` in one pass.

Be careful with duplicates.

Typical pattern:

```cpp
int largest = INT_MIN;
int second = INT_MIN;

for(int x : a)
{
    if(x > largest)
    {
        second = largest;
        largest = x;
    }
    else if(x > second && x != largest)
    {
        second = x;
    }
}
```

---

## Check if Array is Sorted

### Memorize
> Check every adjacent pair.

```cpp
for(int i = 1; i < n; i++)
{
    if(a[i] < a[i - 1])
        return false;
}

return true;
```

---

## Remove Duplicates

For a **sorted array**:

### Memorize
> Slow pointer stores the next unique position.

```cpp
int j = 0;

for(int i = 1; i < n; i++)
{
    if(a[i] != a[j])
        a[++j] = a[i];
}
```

New length = `j + 1`.

---

## Rotate Array

### Memorize
For right rotation by `k`:

```text
Reverse whole array
Reverse first k
Reverse remaining n-k
```

```cpp
k %= n;

reverse(a.begin(), a.end());
reverse(a.begin(), a.begin() + k);
reverse(a.begin() + k, a.end());
```

---

## Missing Number

For numbers `0...n`:

### Memorize
> XOR everything with indices.

```cpp
int ans = n;

for(int i = 0; i < n; i++)
    ans ^= i ^ a[i];

return ans;
```

Why XOR?
- `x ^ x = 0`
- `x ^ 0 = x`

---

## Maximum Subarray — Kadane's Algorithm ⭐⭐⭐

### Memorize

> Keep the best sum ending at the current position.

```cpp
int curr = a[0];
int best = a[0];

for(int i = 1; i < n; i++)
{
    curr = max(a[i], curr + a[i]);
    best = max(best, curr);
}
```

Mental rule:

```text
Should I:
start a new subarray?
OR
extend the previous one?
```

- Time: `O(n)`
- Space: `O(1)`

---

## Longest Subarray with Given Sum

For **positive numbers**:

### Memorize
> Sliding window: expand right, shrink left when sum becomes too large.

For arrays containing negative numbers, use a **prefix sum + hash map** approach instead.

---

## Merge Two Sorted Arrays Without Extra Space

### Memorize
> Compare from the end / use the gap method depending on the exact problem constraints.

For the common in-place merge of two sorted arrays where both arrays have fixed sizes, know the **gap method**.

Core idea:

```text
gap = ceil((n + m) / 2)
compare elements gap apart
reduce gap
```

---

## Two Sum ⭐⭐⭐

### Memorize
> Store `value -> index` in a hash map.

```cpp
unordered_map<int,int> mp;

for(int i = 0; i < n; i++)
{
    int need = target - a[i];

    if(mp.count(need))
        return {mp[need], i};

    mp[a[i]] = i;
}
```

Average time: `O(n)`.

---

## Sort 0, 1, 2 — Dutch National Flag ⭐⭐⭐

### Memorize

Three regions:

```text
[0 ... low-1]       = 0
[low ... mid-1]     = 1
[mid ... high]      = unknown
[high+1 ... n-1]    = 2
```

```cpp
int low = 0, mid = 0, high = n - 1;

while(mid <= high)
{
    if(a[mid] == 0)
        swap(a[low++], a[mid++]);

    else if(a[mid] == 1)
        mid++;

    else
        swap(a[mid], a[high--]);
}
```

Time: `O(n)`, Space: `O(1)`.

---

## Stock Buy and Sell

For one transaction:

### Memorize
> Keep the minimum price seen so far and calculate today's profit.

```cpp
int minPrice = a[0];
int profit = 0;

for(int price : a)
{
    minPrice = min(minPrice, price);
    profit = max(profit, price - minPrice);
}
```

---

## Next Permutation ⭐⭐

### Memorize the 3-step pattern:

```text
1. Find first decreasing element from right
2. Find just larger element from right
3. Swap them
4. Reverse the suffix
```

Example:

```text
1 2 3
    ↑ pivot

→ 1 3 2
```

---

## Pascal's Triangle

### Memorize
Every internal value is:

```text
triangle[i][j] =
triangle[i-1][j-1] + triangle[i-1][j]
```

Edges are always `1`.

---

# 3. Strings

## Reverse String

### Memorize
> Two pointers.

```cpp
int l = 0, r = s.size() - 1;

while(l < r)
{
    swap(s[l], s[r]);
    l++;
    r--;
}
```

---

## Palindrome

### Memorize
> Compare from both ends.

```cpp
while(l < r)
{
    if(s[l] != s[r])
        return false;

    l++;
    r--;
}

return true;
```

---

## Duplicate Characters

### Memorize
> Frequency array / hash map.

```cpp
int freq[256] = {};

for(char c : s)
    freq[(unsigned char)c]++;

for(int i = 0; i < 256; i++)
{
    if(freq[i] > 1)
        cout << char(i);
}
```

---

## Longest Common Prefix

### Memorize
> Start with the first string as prefix and shrink it while comparing.

```text
flower
flow
flight

prefix = "flower"
→ "flow"
→ "fl"
```

---

## Anagram ⭐⭐

### Memorize
> Same characters + same frequencies.

```cpp
int freq[256] = {};

for(char c : a)
    freq[(unsigned char)c]++;

for(char c : b)
    freq[(unsigned char)c]--;

for(int x : freq)
    if(x != 0)
        return false;
```

---

## Pangram

### Memorize
> Track whether all 26 letters occurred.

```cpp
bool seen[26] = {};

for(char c : s)
{
    c = tolower(c);

    if(c >= 'a' && c <= 'z')
        seen[c - 'a'] = true;
}
```

Then check all 26.

---

## Roman to Integer

### Memorize
> If current value < next value, subtract. Otherwise add.

```cpp
if(value[s[i]] < value[s[i + 1]])
    ans -= value[s[i]];
else
    ans += value[s[i]];
```

---

## Balanced Parentheses ⭐⭐⭐

### Memorize

```text
Opening → PUSH
Closing → MATCH TOP + POP
```

```cpp
stack<char> st;

for(char c : s)
{
    if(c == '(' || c == '[' || c == '{')
        st.push(c);
    else
    {
        if(st.empty())
            return false;

        char top = st.top();
        st.pop();

        if(c == ')' && top != '(') return false;
        if(c == ']' && top != '[') return false;
        if(c == '}' && top != '{') return false;
    }
}

return st.empty();
```

---

## KMP ⭐⭐⭐

### Memorize the conceptual chain

```text
Pattern
  ↓
Build LPS
  ↓
Mismatch
  ↓
Do NOT restart pattern from 0
  ↓
Jump using LPS
```

LPS:

> **Longest Proper Prefix which is also a Suffix**

Example:

```text
Pattern: a b a b
LPS:     0 0 1 2
```

Don't blindly memorize the implementation. Understand what `lps[j-1]` means.

---

## Longest Palindromic Substring ⭐⭐⭐

### Memorize

> Every palindrome has a center. Expand around it.

For every index:

```cpp
expand(i, i);       // odd length
expand(i, i + 1);   // even length
```

Complexity: `O(n²)`.

---

# 4. Linked Lists

## SLL Insert Front

### Memorize

```cpp
newNode->next = head;
head = newNode;
```

---

## SLL Insert Back

### Memorize

```cpp
while(temp->next != nullptr)
    temp = temp->next;

temp->next = newNode;
```

---

## SLL Delete Front

```cpp
SNode* temp = head;
head = head->next;
delete temp;
```

---

## SLL Delete Back

### Memorize
> Stop at the second-last node.

```cpp
while(temp->next->next != nullptr)
    temp = temp->next;

delete temp->next;
temp->next = nullptr;
```

Handle one-node lists separately.

---

## DLL

### Memorize
Whenever you change a DLL connection:

> **Update both `next` and `prev`.**

```text
SLL:
current → next

DLL:
current → next
current ← prev
```

---

## Circular Linked List

### Memorize
> There is no `nullptr` at the end.

Stop when:

```cpp
temp == head
```

Traversal is commonly:

```cpp
do
{
    // process
    temp = temp->next;
}
while(temp != head);
```

---

## Merge Two Sorted Linked Lists ⭐⭐⭐

### Memorize
> Compare the current nodes and attach the smaller one.

```text
a → current
b → current

take smaller
move that pointer
repeat
```

Use a dummy node to simplify the implementation.

Time: `O(n + m)`, Space: `O(1)`.

---

## Reverse Linked List Iteratively ⭐⭐⭐

### Memorize this almost exactly:

```cpp
SNode* prev = nullptr;
SNode* curr = head;

while(curr != nullptr)
{
    SNode* next = curr->next;

    curr->next = prev;

    prev = curr;
    curr = next;
}

return prev;
```

Mental model:

```text
save next
reverse arrow
move prev
move curr
```

---

## Reverse Linked List Recursively

### Memorize

```cpp
SNode* newHead = reverseRecursive(head->next);

head->next->next = head;
head->next = nullptr;

return newHead;
```

Base case:

```cpp
if(head == nullptr || head->next == nullptr)
    return head;
```

---

## Fast + Slow Pointer ⭐⭐⭐

Memorize:

```cpp
slow = slow->next;
fast = fast->next->next;
```

Used for:
- Middle of list
- Cycle detection
- Cycle starting point
- Palindrome

---

## Cycle Detection — Floyd ⭐⭐⭐

### Memorize

```text
slow → 1 step
fast → 2 steps
```

If:

```cpp
slow == fast
```

→ cycle exists.

---

## Cycle Starting Point ⭐⭐⭐

After slow and fast meet:

```cpp
slow = head;

while(slow != fast)
{
    slow = slow->next;
    fast = fast->next;
}
```

Meeting point = start of cycle.

---

## Palindrome Linked List

### Memorize the recipe

```text
Find middle
   ↓
Reverse second half
   ↓
Compare both halves
```

This combines:
- Fast/slow pointer
- Reverse linked list
- Comparison

---

## Check if Linked List is Circular

### Memorize
> Starting from head, if traversal eventually returns to **head**, it is circular.

Do not confuse this with arbitrary cycle detection.

---

## Merge Sort on Linked List ⭐⭐⭐

### Memorize

```text
Find middle
   ↓
Split
   ↓
Merge sort left
   ↓
Merge sort right
   ↓
Merge
```

Time: `O(n log n)`.

### Interview judgment

> Merge Sort is generally preferred for linked lists because merging can be done efficiently by pointer manipulation and linked lists do not support random access.

---

## Quick Sort on Linked List

### Memorize

```text
Choose pivot
   ↓
Partition
   ↓
Sort left
   ↓
Sort right
```

Average: `O(n log n)`  
Worst: `O(n²)`.

For linked lists, **prefer Merge Sort** when asked which sorting algorithm is better suited.

---

## Rotate Linked List ⭐⭐

For right rotation by `k`:

```text
Find length + tail
      ↓
k %= length
      ↓
Make list circular
      ↓
Find new tail
      ↓
Break circle
```

---

# 5. Recursion

## General Recursion

### Memorize the three questions

Before writing recursion, ask:

```text
1. What is the base case?
2. How do I reduce the problem?
3. What happens when recursion returns?
```

---

## Power

Basic:

```cpp
if(n == 0)
    return 1;

return x * power(x, n - 1);
```

Complexity: `O(n)`.

### Fast Power

```text
x^n
 ↓
calculate x^(n/2)
 ↓
square it
```

Complexity: `O(log n)`.

---

## Sort a Stack ⭐⭐

### Memorize

```text
Remove top
   ↓
Recursively sort remaining stack
   ↓
Insert removed element correctly
```

Two functions:

```text
sortStack()
insertSorted()
```

---

## Reverse a Stack ⭐⭐

### Memorize

```text
Remove top
   ↓
Recursively reverse remaining stack
   ↓
Insert removed element at bottom
```

Two functions:

```text
reverseStack()
insertAtBottom()
```

---

## N-Queens ⭐⭐⭐

### Memorize

> **Choose → Explore → Undo**

```cpp
board[row][col] = 1;

if(solve(row + 1))
    return true;

board[row][col] = 0;
```

The final assignment is the **backtracking** step.

N-Queens is a classic example of:

```text
Backtracking
```

Same pattern appears in:
- Sudoku
- Permutations
- Combinations
- Subsets
- Maze problems

---

## Tower of Hanoi ⭐⭐⭐

### Memorize

To move `n` disks:

```text
Move n-1
    ↓
Move largest
    ↓
Move n-1
```

Recursive structure:

```cpp
hanoi(n-1, source, destination, auxiliary);

move largest;

hanoi(n-1, auxiliary, source, destination);
```

Number of moves:

```text
2^n - 1
```

Time: `O(2^n)`  
Recursion stack: `O(n)`.

---

# 6. Bit Manipulation

## Odd / Even ⭐⭐⭐

### Memorize

```cpp
n & 1
```

```text
1 → odd
0 → even
```

---

## Power of 2 ⭐⭐⭐

### Memorize

```cpp
n > 0 && (n & (n - 1)) == 0
```

Reason:

> A positive power of 2 has exactly one set bit.

---

## Remove Lowest Set Bit ⭐⭐⭐

### Memorize

```cpp
n = n & (n - 1);
```

It removes the lowest `1` bit.

---

## Count Set Bits ⭐⭐⭐

### Memorize

```cpp
int count = 0;

while(n)
{
    n = n & (n - 1);
    count++;
}
```

Each iteration removes one set bit.

---

## Swap Using XOR

### Memorize

```cpp
a ^= b;
b ^= a;
a ^= b;
```

Core XOR properties:

```text
x ^ x = 0
x ^ 0 = x
```

In real C++, prefer `std::swap`; this is mainly an interview trick.

---

## Divide Without `*`, `/`, `%` ⭐⭐

### Memorize

> Use binary long division with left shifts.

Concept:

```text
Find largest (divisor << i)
that fits inside dividend.
Subtract it.
Add 2^i to quotient.
Repeat.
```

---

## Number of Bits to Convert A to B ⭐⭐⭐

### Memorize

```cpp
countSetBits(a ^ b)
```

Why?

```text
A XOR B
```

has `1` exactly where the bits differ.

---

## Power Set ⭐⭐⭐

### Memorize

For `n` elements:

```text
Number of subsets = 2^n
```

Represent each subset using a bitmask.

```cpp
for(int mask = 0; mask < (1 << n); mask++)
{
    for(int i = 0; i < n; i++)
    {
        if(mask & (1 << i))
        {
            // include arr[i]
        }
    }
}
```

The key line:

```cpp
mask & (1 << i)
```

means:

> Is element `i` included?

---

## Prime Factors

### Memorize

> Check factors only up to `sqrt(n)`.

```cpp
for(int i = 2; i * i <= n; i++)
{
    while(n % i == 0)
    {
        cout << i;
        n /= i;
    }
}

if(n > 1)
    cout << n;
```

---

## Divisors

### Memorize

If `i` divides `n`, then:

```text
i
n / i
```

are both divisors.

So loop only to:

```text
sqrt(n)
```

```cpp
for(int i = 1; i * i <= n; i++)
{
    if(n % i == 0)
    {
        cout << i;

        if(i != n / i)
            cout << n / i;
    }
}
```

---

# 7. Maths / Number Problems

## Count Digits

### Memorize

Repeatedly remove the last digit:

```cpp
while(n > 0)
{
    count++;
    n /= 10;
}
```

Special case: `n == 0`.

---

## Reverse Number

### Memorize

```cpp
rev = rev * 10 + n % 10;
n /= 10;
```

This is one of the most important number-manipulation patterns.

---

## Palindrome Number

### Memorize

```text
Save original
   ↓
Reverse number
   ↓
Compare original == reversed
```

---

## GCD / HCF ⭐⭐⭐

### Memorize Euclid's Algorithm

```cpp
while(b != 0)
{
    int temp = b;
    b = a % b;
    a = temp;
}

return a;
```

Core identity:

```text
gcd(a,b) = gcd(b, a%b)
```

---

## Armstrong Number

### Memorize

For each digit:

```text
digit = n % 10
sum += digit^number_of_digits
n /= 10
```

Then compare:

```text
sum == original
```

---

## Prime Number

### Memorize

> Only check divisors up to `sqrt(n)`.

```cpp
if(n < 2)
    return false;

for(int i = 2; i * i <= n; i++)
{
    if(n % i == 0)
        return false;
}

return true;
```

---

## Even / Odd

Normal arithmetic:

```cpp
n % 2 == 0
```

Bit version:

```cpp
n & 1
```

---

## Leap Year

### Memorize the exact rule

```text
Divisible by 400 → leap
OR
Divisible by 4 AND NOT divisible by 100 → leap
```

```cpp
bool leap =
    (year % 400 == 0) ||
    (year % 4 == 0 && year % 100 != 0);
```

---

## Factorial

### Iterative

```cpp
long long fact = 1;

for(int i = 1; i <= n; i++)
    fact *= i;
```

### Recursive

```cpp
if(n <= 1)
    return 1;

return n * factorial(n - 1);
```

---

## Fibonacci

### Iterative

### Memorize
> Keep the previous two values.

```cpp
int a = 0, b = 1;

for(int i = 0; i < n; i++)
{
    cout << a << " ";

    int c = a + b;
    a = b;
    b = c;
}
```

Avoid naive recursive Fibonacci in interviews unless specifically asked; it is exponential.

---

## Sum of First N Numbers

### Formula

```text
n(n+1)/2
```

Prefer this over a loop when the problem simply asks for the sum.

---

# 8. Pattern Problems

## Pyramid

### Memorize the structure

For each row:

```text
spaces
+
stars
```

For a centered pyramid:

```cpp
for(int i = 1; i <= n; i++)
{
    for(int j = 1; j <= n - i; j++)
        cout << " ";

    for(int j = 1; j <= 2*i - 1; j++)
        cout << "*";

    cout << '\n';
}
```

The key formula:

```text
spaces = n - i
stars  = 2*i - 1
```

---

# 9. Core Pointer / C Fundamentals

## Pointer Basics

### Memorize

```cpp
int x = 10;
int *p = &x;
```

Meaning:

```text
x       = actual value
&x      = address of x
p       = stores address of x
*p      = value at that address
```

The classic confusion:

```cpp
int *p = &x;
```

means:

> `p` is a pointer to int, and `p` stores the address of `x`.

Not:

```cpp
*p = &x;
```

---

## Pointer to Pointer

### Memorize

```cpp
int x = 10;

int *p = &x;

int **q = &p;
```

Think:

```text
q
 ↓
p
 ↓
x
```

Therefore:

```text
*q  → p
**q → x
```

---

# 10. Fast Interview Pattern Map

When you see this...

| Problem wording / situation | Think |
|---|---|
| Reverse array/string | Two pointers |
| Palindrome | Two pointers |
| Duplicate characters | Frequency map/array |
| Anagram | Frequency comparison |
| Balanced brackets | Stack |
| Longest palindrome | Expand around center |
| KMP | LPS |
| Two Sum | Hash map |
| Sorted 0/1/2 | Dutch National Flag |
| Maximum subarray | Kadane |
| Missing number | XOR |
| Rotate array | Reversal |
| Linked-list middle | Slow/Fast |
| Linked-list cycle | Floyd |
| Cycle starting point | Reset slow to head |
| Reverse linked list | `prev/curr/next` |
| Palindrome linked list | Middle + reverse + compare |
| Merge sorted lists | Two pointers + dummy |
| Linked-list sorting | Merge Sort |
| Stack recursion | Remove → recurse → restore |
| N-Queens | Backtracking |
| Tower of Hanoi | `n-1 → largest → n-1` |
| Odd/even | `n & 1` |
| Power of 2 | `n & (n-1)` |
| Remove lowest set bit | `n & (n-1)` |
| Count set bits | Repeated `n & (n-1)` |
| Bits A → B | `countSetBits(a ^ b)` |
| Power set | Bitmask |
| Prime/divisors | Up to `sqrt(n)` |
| GCD | Euclid |

---

# 11. The 20 Lines Worth Memorizing

These are the highest-value snippets from everything above.

## 1. Two Pointers

```cpp
while(l < r)
{
    swap(a[l], a[r]);
    l++;
    r--;
}
```

## 2. Kadane

```cpp
curr = max(a[i], curr + a[i]);
best = max(best, curr);
```

## 3. Two Sum

```cpp
if(mp.count(target - a[i]))
    return {mp[target - a[i]], i};

mp[a[i]] = i;
```

## 4. Dutch National Flag

```cpp
if(a[mid] == 0)
    swap(a[low++], a[mid++]);
else if(a[mid] == 1)
    mid++;
else
    swap(a[mid], a[high--]);
```

## 5. Reverse Linked List

```cpp
next = curr->next;
curr->next = prev;
prev = curr;
curr = next;
```

## 6. Fast/Slow

```cpp
slow = slow->next;
fast = fast->next->next;
```

## 7. Floyd Cycle

```cpp
if(slow == fast)
    return true;
```

## 8. Cycle Start

```cpp
slow = head;

while(slow != fast)
{
    slow = slow->next;
    fast = fast->next;
}
```

## 9. Merge Lists

```cpp
if(a->data < b->data)
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
```

## 10. Recursion Base Case

```cpp
if(n == 0)
    return ...;
```

## 11. Backtracking

```cpp
choose();

if(solve())
    return true;

undo();
```

## 12. Hanoi

```cpp
hanoi(n-1, source, destination, auxiliary);
move(n);
hanoi(n-1, auxiliary, source, destination);
```

## 13. Odd

```cpp
n & 1
```

## 14. Power of 2

```cpp
n > 0 && (n & (n-1)) == 0
```

## 15. Remove Lowest Set Bit

```cpp
n &= n - 1;
```

## 16. A → B Bit Differences

```cpp
countSetBits(a ^ b)
```

## 17. Power Set

```cpp
if(mask & (1 << i))
```

## 18. GCD

```cpp
while(b)
{
    a %= b;
    swap(a, b);
}
```

## 19. Reverse Number

```cpp
rev = rev * 10 + n % 10;
n /= 10;
```

## 20. Prime Check

```cpp
for(int i = 2; i * i <= n; i++)
    if(n % i == 0)
        return false;
```

---

# Final Rule

Do **not** memorize code line-by-line for every problem.

Memorize:

```text
PATTERN
   ↓
KEY INVARIANT
   ↓
2–5 CRITICAL LINES
   ↓
COMPLEXITY
```

For an interview, being able to explain **why the pattern works** is more valuable than reproducing a 40-line solution from memory.
