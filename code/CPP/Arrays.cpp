#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <bits/stdc++.h>

using namespace std;


/*
============================================================
1. KADANE'S ALGORITHM ⭐⭐⭐⭐⭐
============================================================

Problem:
Find the largest sum of any contiguous subarray.

Example:

arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4}

Best subarray:

[4, -1, 2, 1]

Sum = 4 + (-1) + 2 + 1
    = 6

Answer = 6


CORE IDEA:

At every element, ask:

    "Should I continue my current subarray,
     or start a new subarray here?"

We maintain:

    currentSum
    maxSum

currentSum = max(arr[i], currentSum + arr[i])

maxSum = max(maxSum, currentSum)


IMPORTANT:

This is one of the most important array algorithms
for interviews.

Time:  O(n)
Space: O(1)
*/
int kadane(vector<int>& arr)
{
    int currentSum = arr[0];
    int maxSum = arr[0];

    for (int i = 1; i < arr.size(); i++)
    {
        currentSum = max(arr[i],
                         currentSum + arr[i]);

        maxSum = max(maxSum, currentSum);
    }

    return maxSum;
}


/*
============================================================
2. REVERSE AN ARRAY
============================================================

Problem:
Reverse the array in-place.

Example:

Input:
1 2 3 4 5

Output:
5 4 3 2 1


IDEA:

Use two pointers:

left  -> beginning
right -> end

Swap them.

Then:

left++
right--

Stop when:

left >= right

Time:  O(n)
Space: O(1)
*/
void reverseArray(vector<int>& arr)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left < right)
    {
        swap(arr[left], arr[right]);

        left++;
        right--;
    }
}


/*
============================================================
3. FIND MINIMUM AND MAXIMUM
============================================================

Problem:
Find the smallest and largest element.

Example:

1 5 2 9 3

Minimum = 1
Maximum = 9

IDEA:

Keep two variables:

minValue
maxValue

Scan the array once.

Time:  O(n)
Space: O(1)
*/
void findMinMax(vector<int>& arr)
{
    int minValue = arr[0];
    int maxValue = arr[0];

    for (int x : arr)
    {
        minValue = min(minValue, x);
        maxValue = max(maxValue, x);
    }

    cout << "Minimum: " << minValue << endl;
    cout << "Maximum: " << maxValue << endl;
}


/*
============================================================
4. SECOND LARGEST ELEMENT
============================================================

Problem:
Find the second largest DISTINCT element.

Example:

10 5 8 20 15

Largest = 20
Second Largest = 15


IDEA:

Maintain:

largest
secondLargest

Whenever we find a new largest:

secondLargest = largest
largest = current

Otherwise, if current is between them:

secondLargest = current


Time:  O(n)
Space: O(1)
*/
int secondLargest(vector<int>& arr)
{
    int largest = INT_MIN;
    int second = INT_MIN;

    for (int x : arr)
    {
        if (x > largest)
        {
            second = largest;
            largest = x;
        }
        else if (x > second && x != largest)
        {
            second = x;
        }
    }

    return second;
}


/*
============================================================
5. CHECK IF ARRAY IS SORTED
============================================================

Problem:
Check whether an array is sorted in non-decreasing order.

Example:

1 2 2 4 5

Sorted -> Yes

1 3 2 4

Sorted -> No


IDEA:

Compare every element with the previous element.

If:

arr[i] < arr[i-1]

then the array is not sorted.

Time:  O(n)
Space: O(1)
*/
bool isSorted(vector<int>& arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] < arr[i - 1])
            return false;
    }

    return true;
}


/*
============================================================
6. REMOVE DUPLICATES FROM SORTED ARRAY
============================================================

Problem:
Remove duplicates from a SORTED array in-place.

Example:

1 1 2 2 3 3 4

After removing duplicates:

1 2 3 4


IMPORTANT:

This solution assumes the array is SORTED.

IDEA:

Use two pointers.

i -> position of last unique element
j -> scans the array

Whenever:

arr[j] != arr[i]

we found a new unique element.

Move it forward.

Time:  O(n)
Space: O(1)
*/
int removeDuplicates(vector<int>& arr)
{
    if (arr.empty())
        return 0;

    int i = 0;

    for (int j = 1; j < arr.size(); j++)
    {
        if (arr[j] != arr[i])
        {
            i++;
            arr[i] = arr[j];
        }
    }

    return i + 1;
}


/*
============================================================
7. LEFT ROTATION BY ONE
============================================================

Problem:

Input:
1 2 3 4 5

Left rotate by 1:

2 3 4 5 1


IDEA:

Save first element.

Shift everything left.

Put first element at the end.

Time:  O(n)
Space: O(1)
*/
void leftRotateByOne(vector<int>& arr)
{
    int first = arr[0];

    for (int i = 1; i < arr.size(); i++)
    {
        arr[i - 1] = arr[i];
    }

    arr[arr.size() - 1] = first;
}


/*
============================================================
8. LEFT ROTATION BY K
============================================================

Problem:

Input:
1 2 3 4 5

k = 2

Output:
3 4 5 1 2


BEST EASY METHOD:

Use the reversal algorithm.

For left rotation by k:

1. Reverse first k elements
2. Reverse remaining elements
3. Reverse entire array


Example:

1 2 | 3 4 5

Reverse first part:

2 1 | 3 4 5

Reverse second part:

2 1 | 5 4 3

Reverse everything:

3 4 5 1 2


Time:  O(n)
Space: O(1)
*/
void leftRotate(vector<int>& arr, int k)
{
    int n = arr.size();

    k = k % n;

    reverse(arr.begin(), arr.begin() + k);
    reverse(arr.begin() + k, arr.end());
    reverse(arr.begin(), arr.end());
}


/*
============================================================
9. FIND THE MISSING NUMBER
============================================================

Problem:

Array contains numbers from:

0 to n

with exactly one number missing.

Example:

0 1 2 4 5

Missing = 3


IDEA:

Use XOR.

Important XOR properties:

x ^ x = 0
x ^ 0 = x

If we XOR:

0 ^ 1 ^ 2 ^ 3 ^ 4 ^ 5

with all elements in the array,

everything appearing twice cancels.

Only the missing number remains.

Time:  O(n)
Space: O(1)
*/
int missingNumber(vector<int>& arr)
{
    int n = arr.size();

    int xorValue = n;

    for (int i = 0; i < n; i++)
    {
        xorValue ^= i;
        xorValue ^= arr[i];
    }

    return xorValue;
}


/*
============================================================
10. LONGEST SUBARRAY WITH GIVEN SUM
============================================================

Problem:

Find the length of the longest subarray
whose sum equals k.

Example:

arr = {1, 2, 3, 1, 1, 1, 1}
k = 3

Longest valid subarray:

{1, 1, 1}

or

{1, 2}

depending on the array.

For an array containing POSITIVE numbers,
sliding window is the easiest approach.


IDEA:

Use:

left
right
sum

Expand right.

If sum > k:
move left forward.

If sum == k:
update answer.

Time:  O(n)
Space: O(1)

IMPORTANT:

This simple sliding-window version works when
the array contains NON-NEGATIVE numbers.

For arbitrary positive/negative numbers,
use prefix sum + unordered_map.
*/
int longestSubarrayPositive(vector<int>& arr, int k)
{
    int left = 0;
    int sum = 0;
    int maxLength = 0;

    for (int right = 0; right < arr.size(); right++)
    {
        sum += arr[right];

        while (sum > k && left <= right)
        {
            sum -= arr[left];
            left++;
        }

        if (sum == k)
        {
            maxLength = max(maxLength,
                            right - left + 1);
        }
    }

    return maxLength;
}


/*
============================================================
11. MERGE TWO SORTED ARRAYS WITHOUT EXTRA SPACE
============================================================

Problem:

arr1 = {1, 4, 7, 8}
arr2 = {2, 3, 9}

After merging:

arr1 = {1, 2, 3, 4}
arr2 = {7, 8, 9}

We don't create a third array.


IDEA:

Compare:

last element of arr1
with
first element of arr2

If arr1's last element is larger,
swap them.

Then sort both arrays.

This is the simple interview-friendly approach.

Time:
O((n+m) log(n+m)) because of sorting.

Space:
O(1) auxiliary space.
*/
void mergeWithoutExtraSpace(vector<int>& arr1,
                            vector<int>& arr2)
{
    int n = arr1.size();
    int m = arr2.size();

    int i = n - 1;
    int j = 0;

    while (i >= 0 && j < m)
    {
        if (arr1[i] > arr2[j])
        {
            swap(arr1[i], arr2[j]);

            i--;
            j++;
        }
        else
        {
            break;
        }
    }

    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
}


/*
============================================================
12. TWO SUM
============================================================

Problem:

Given an array and target,
find two elements whose sum equals target.

Example:

arr = {2, 7, 11, 15}
target = 9

2 + 7 = 9

Answer:
indices 0 and 1


IDEA:

For every number x:

We need:

target - x

Use a hash map to check whether
the required value has already appeared.

Time:  O(n) average
Space: O(n)
*/
vector<int> twoSum(vector<int>& arr, int target)
{
    unordered_map<int, int> mp;

    for (int i = 0; i < arr.size(); i++)
    {
        int required = target - arr[i];

        if (mp.find(required) != mp.end())
        {
            return {mp[required], i};
        }

        mp[arr[i]] = i;
    }

    return {};
}


/*
============================================================
13. SORT ARRAY OF 0s, 1s AND 2s
============================================================

Problem:

Sort:

2 0 2 1 1 0

into:

0 0 1 1 2 2


IMPORTANT:

Do NOT use normal sort.

Use the Dutch National Flag Algorithm.


Three regions:

[0 ... low-1]       -> 0
[low ... mid-1]     -> 1
[mid ... high]      -> unknown
[high+1 ... end]    -> 2


Rules:

If arr[mid] == 0:

    swap(low, mid)
    low++
    mid++

If arr[mid] == 1:

    mid++

If arr[mid] == 2:

    swap(mid, high)
    high--

IMPORTANT:

When swapping with high,
DO NOT increment mid immediately.

The new value at mid has not been processed yet.

Time:  O(n)
Space: O(1)
*/
void sort012(vector<int>& arr)
{
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;

    while (mid <= high)
    {
        if (arr[mid] == 0)
        {
            swap(arr[low], arr[mid]);

            low++;
            mid++;
        }
        else if (arr[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(arr[mid], arr[high]);

            high--;
        }
    }
}


/*
============================================================
14. STOCK BUY AND SELL
============================================================

Problem:

You can buy a stock once and sell it once.

Find the maximum profit.

Example:

prices = {7,1,5,3,6,4}

Buy at 1
Sell at 6

Profit = 5


IDEA:

Maintain:

minimum price seen so far

For every price:

profit = price - minimumPrice

Update maximum profit.

Time:  O(n)
Space: O(1)
*/
int maxProfit(vector<int>& prices)
{
    int minPrice = INT_MAX;
    int profit = 0;

    for (int price : prices)
    {
        minPrice = min(minPrice, price);

        profit = max(profit,
                     price - minPrice);
    }

    return profit;
}


/*
============================================================
15. NEXT PERMUTATION
============================================================

Problem:

Find the next lexicographically greater permutation.

Example:

1 2 3

Next:
1 3 2

Another:

1 2 3 4

Next:
1 2 4 3


IDEA:

1. Find the first position from the RIGHT
   where:

   arr[i] < arr[i+1]

   This is called the pivot.

2. Find the smallest element from the right
   that is greater than arr[i].

3. Swap them.

4. Reverse everything after i.

Example:

1 2 3

Pivot = 2

Swap 2 and 3:

1 3 2

Reverse suffix.

Answer:

1 3 2


IMPORTANT:

C++ STL already provides:

next_permutation(arr.begin(), arr.end());

Time: O(n)
Space: O(1)
*/
void nextPermutation(vector<int>& arr)
{
    int n = arr.size();

    int i = n - 2;

    // Step 1: Find pivot
    while (i >= 0 && arr[i] >= arr[i + 1])
    {
        i--;
    }

    // If pivot exists
    if (i >= 0)
    {
        // Step 2: Find element just larger than pivot
        int j = n - 1;

        while (arr[j] <= arr[i])
        {
            j--;
        }

        // Step 3: Swap
        swap(arr[i], arr[j]);
    }

    // Step 4: Reverse suffix
    reverse(arr.begin() + i + 1,
            arr.end());
}


/*
============================================================
16. PASCAL'S TRIANGLE
============================================================

Problem:

Print:

        1
       1 1
      1 2 1
     1 3 3 1
    1 4 6 4 1


IMPORTANT PROPERTY:

Every inner element is:

previous row left
+
previous row right

Example:

       1 3 3 1
        \ /
         6

6 = 3 + 3


Simple approach:

Create each row.

First and last element = 1.

Middle element:

previous[j-1] + previous[j]


Time: O(n^2)
Space: O(n^2)
*/
vector<vector<int>> pascalsTriangle(int n)
{
    vector<vector<int>> triangle;

    for (int i = 0; i < n; i++)
    {
        vector<int> row(i + 1, 1);

        for (int j = 1; j < i; j++)
        {
            row[j] =
                triangle[i - 1][j - 1]
                +
                triangle[i - 1][j];
        }

        triangle.push_back(row);
    }

    return triangle;
}


/*
============================================================
MAIN
============================================================

This main demonstrates all the problems.

You can change the input arrays and values
to practice different cases.
*/
int main()
{
    vector<int> arr =
    {
        -2, 1, -3, 4, -1, 2, 1, -5, 4
    };

    // 1. Kadane's Algorithm
    cout << "Kadane Maximum Sum: "
         << kadane(arr) << endl;


    // 2. Reverse Array
    vector<int> a1 = {1, 2, 3, 4, 5};

    reverseArray(a1);

    cout << "Reversed Array: ";

    for (int x : a1)
        cout << x << " ";

    cout << endl;


    // 3. Min and Max
    vector<int> a2 = {5, 2, 9, 1, 7};

    findMinMax(a2);


    // 4. Second Largest
    vector<int> a3 = {10, 5, 8, 20, 15};

    cout << "Second Largest: "
         << secondLargest(a3)
         << endl;


    // 5. Check Sorted
    vector<int> a4 = {1, 2, 2, 4, 5};

    cout << "Sorted: "
         << (isSorted(a4) ? "Yes" : "No")
         << endl;


    // 6. Remove Duplicates
    vector<int> a5 = {1, 1, 2, 2, 3, 3, 4};

    int newSize = removeDuplicates(a5);

    cout << "After Removing Duplicates: ";

    for (int i = 0; i < newSize; i++)
        cout << a5[i] << " ";

    cout << endl;


    // 7. Rotation
    vector<int> a6 = {1, 2, 3, 4, 5};

    leftRotate(a6, 2);

    cout << "Left Rotated: ";

    for (int x : a6)
        cout << x << " ";

    cout << endl;


    // 8. Missing Number
    vector<int> a7 = {0, 1, 2, 4, 5};

    cout << "Missing Number: "
         << missingNumber(a7)
         << endl;


    // 9. Longest Subarray with Given Sum
    vector<int> a8 = {1, 2, 1, 1, 1, 3, 2};

    cout << "Longest Subarray Length: "
         << longestSubarrayPositive(a8, 3)
         << endl;


    // 10. Merge Without Extra Space
    vector<int> a9 = {1, 4, 7, 8};
    vector<int> a10 = {2, 3, 9};

    mergeWithoutExtraSpace(a9, a10);

    cout << "Merged Array 1: ";

    for (int x : a9)
        cout << x << " ";

    cout << endl;

    cout << "Merged Array 2: ";

    for (int x : a10)
        cout << x << " ";

    cout << endl;


    // 11. Two Sum
    vector<int> a11 = {2, 7, 11, 15};

    vector<int> answer = twoSum(a11, 9);

    cout << "Two Sum Indices: ";

    for (int x : answer)
        cout << x << " ";

    cout << endl;


    // 12. Sort 0, 1, 2
    vector<int> a12 = {2, 0, 2, 1, 1, 0};

    sort012(a12);

    cout << "Sorted 0,1,2: ";

    for (int x : a12)
        cout << x << " ";

    cout << endl;


    // 13. Stock Buy and Sell
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    cout << "Maximum Stock Profit: "
         << maxProfit(prices)
         << endl;


    // 14. Next Permutation
    vector<int> a13 = {1, 2, 3};

    nextPermutation(a13);

    cout << "Next Permutation: ";

    for (int x : a13)
        cout << x << " ";

    cout << endl;


    // 15. Pascal's Triangle
    vector<vector<int>> triangle =
        pascalsTriangle(5);

    cout << "Pascal's Triangle:\n";

    for (auto row : triangle)
    {
        for (int x : row)
            cout << x << " ";

        cout << endl;
    }


    return 0;
}