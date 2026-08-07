# Python Solutions — P1 Reference

Reference implementations for **must-solve** problems. Use after attempting yourself. Matches pseudocode in `dsa-*.md` files.

---

## Strings

### 1. Valid Anagram

```python
def is_anagram(s: str, t: str) -> bool:
    if len(s) != len(t):
        return False
    count = [0] * 26
    for a, b in zip(s, t):
        count[ord(a) - ord('a')] += 1
        count[ord(b) - ord('a')] -= 1
    return all(c == 0 for c in count)
# Time O(n), Space O(1)
```

### 2. Group Anagrams

```python
from collections import defaultdict

def group_anagrams(strs):
    groups = defaultdict(list)
    for word in strs:
        key = tuple(sorted(word))
        groups[key].append(word)
    return list(groups.values())
# Time O(n * k log k), k = max word length
```

### 3. Longest Substring Without Repeating Characters

```python
def length_of_longest_substring(s: str) -> int:
    last = {}
    left = max_len = 0
    for right, ch in enumerate(s):
        if ch in last and last[ch] >= left:
            left = last[ch] + 1
        last[ch] = right
        max_len = max(max_len, right - left + 1)
    return max_len
# Time O(n), Space O(min(n, alphabet))
```

### 4. Valid Palindrome

```python
def is_palindrome(s: str) -> bool:
    left, right = 0, len(s) - 1
    while left < right:
        while left < right and not s[left].isalnum():
            left += 1
        while left < right and not s[right].isalnum():
            right -= 1
        if s[left].lower() != s[right].lower():
            return False
        left += 1
        right -= 1
    return True
```

### 5. First Unique Character

```python
def first_uniq_char(s: str) -> int:
    freq = {}
    for ch in s:
        freq[ch] = freq.get(ch, 0) + 1
    for i, ch in enumerate(s):
        if freq[ch] == 1:
            return i
    return -1
```

---

## Arrays & Hash Maps

### 6. Two Sum

```python
def two_sum(nums, target):
    seen = {}
    for i, num in enumerate(nums):
        complement = target - num
        if complement in seen:
            return [seen[complement], i]
        seen[num] = i
    return []
# Time O(n), Space O(n)
```

### 7. Contains Duplicate

```python
def contains_duplicate(nums):
    return len(set(nums)) < len(nums)
# Time O(n), Space O(n)
```

### 8. Best Time to Buy and Sell Stock

```python
def max_profit(prices):
    min_price = float('inf')
    best = 0
    for p in prices:
        min_price = min(min_price, p)
        best = max(best, p - min_price)
    return best
# Time O(n), Space O(1)
```

### 9. Product of Array Except Self

```python
def product_except_self(nums):
    n = len(nums)
    result = [1] * n
    prefix = 1
    for i in range(n):
        result[i] = prefix
        prefix *= nums[i]
    suffix = 1
    for i in range(n - 1, -1, -1):
        result[i] *= suffix
        suffix *= nums[i]
    return result
# Time O(n), Space O(1) excluding output
```

### 10. Merge Intervals

```python
def merge(intervals):
    if not intervals:
        return []
    intervals.sort(key=lambda x: x[0])
    merged = [intervals[0]]
    for start, end in intervals[1:]:
        if start <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])
    return merged
# Time O(n log n)
```

---

## Greedy

### 11. Assign Cookies

```python
def find_content_children(g, s):
    g.sort()
    s.sort()
    child = cookie = 0
    while child < len(g) and cookie < len(s):
        if s[cookie] >= g[child]:
            child += 1
        cookie += 1
    return child
```

### 12. Jump Game

```python
def can_jump(nums):
    farthest = 0
    for i, jump in enumerate(nums):
        if i > farthest:
            return False
        farthest = max(farthest, i + jump)
    return True
# Time O(n)
```

### 13. Non-overlapping Intervals

```python
def erase_overlap_intervals(intervals):
    intervals.sort(key=lambda x: x[1])
    count = 0
    end = float('-inf')
    for start, e in intervals:
        if start >= end:
            count += 1
            end = e
    return len(intervals) - count
```

### 14. Lemonade Change

```python
def lemonade_change(bills):
    five = ten = 0
    for bill in bills:
        if bill == 5:
            five += 1
        elif bill == 10:
            if five == 0:
                return False
            five -= 1
            ten += 1
        else:  # 20
            if ten > 0 and five > 0:
                ten -= 1
                five -= 1
            elif five >= 3:
                five -= 3
            else:
                return False
    return True
```

### 15. Task Scheduler

```python
from collections import Counter
import heapq

def least_interval(tasks, n):
    freq = Counter(tasks)
    max_heap = [-cnt for cnt in freq.values()]
    heapq.heapify(max_heap)
    time = 0
    while max_heap:
        cycle = []
        for _ in range(n + 1):
            if max_heap:
                cnt = heapq.heappop(max_heap)
                if cnt + 1:
                    cycle.append(cnt + 1)
            time += 1
            if not max_heap and not cycle:
                break
        for cnt in cycle:
            heapq.heappush(max_heap, cnt)
    return time
```

---

## Stacks & Queues

### 16. Valid Parentheses

```python
def is_valid(s: str) -> bool:
    stack = []
    match = {')': '(', '}': '{', ']': '['}
    for c in s:
        if c in match:
            if not stack or stack.pop() != match[c]:
                return False
        else:
            stack.append(c)
    return not stack
```

### 17. Min Stack

```python
class MinStack:
    def __init__(self):
        self.stack = []
        self.min_stack = []

    def push(self, val):
        self.stack.append(val)
        if not self.min_stack or val <= self.min_stack[-1]:
            self.min_stack.append(val)

    def pop(self):
        if self.stack.pop() == self.min_stack[-1]:
            self.min_stack.pop()

    def top(self):
        return self.stack[-1]

    def get_min(self):
        return self.min_stack[-1]
```

### 18. Evaluate Reverse Polish Notation

```python
def eval_rpn(tokens):
    stack = []
    ops = {'+': lambda a, b: a + b, '-': lambda a, b: a - b,
           '*': lambda a, b: a * b, '/': lambda a, b: int(a / b)}
    for t in tokens:
        if t in ops:
            b, a = stack.pop(), stack.pop()
            stack.append(ops[t](a, b))
        else:
            stack.append(int(t))
    return stack[0]
```

### 19. Daily Temperatures

```python
def daily_temperatures(temps):
    n = len(temps)
    answer = [0] * n
    stack = []
    for i, t in enumerate(temps):
        while stack and temps[stack[-1]] < t:
            j = stack.pop()
            answer[j] = i - j
        stack.append(i)
    return answer
```

### 20. Basic Calculator II

```python
def calculate(s: str) -> int:
    stack = []
    num = 0
    op = '+'
    for i, ch in enumerate(s):
        if ch.isdigit():
            num = num * 10 + int(ch)
        if ch in '+-*/' or i == len(s) - 1:
            if op == '+':
                stack.append(num)
            elif op == '-':
                stack.append(-num)
            elif op == '*':
                stack.append(stack.pop() * num)
            elif op == '/':
                stack.append(int(stack.pop() / num))
            op = ch
            num = 0
    return sum(stack)
```

---

## Linked Lists

```python
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
```

### 21. Reverse Linked List

```python
def reverse_list(head):
    prev, curr = None, head
    while curr:
        nxt = curr.next
        curr.next = prev
        prev = curr
        curr = nxt
    return prev
```

### 22. Merge Two Sorted Lists

```python
def merge_two_lists(l1, l2):
    dummy = ListNode(0)
    tail = dummy
    while l1 and l2:
        if l1.val <= l2.val:
            tail.next = l1
            l1 = l1.next
        else:
            tail.next = l2
            l2 = l2.next
        tail = tail.next
    tail.next = l1 or l2
    return dummy.next
```

### 23. Linked List Cycle

```python
def has_cycle(head):
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow is fast:
            return True
    return False
```

### 24. Remove Nth From End

```python
def remove_nth_from_end(head, n):
    dummy = ListNode(0, head)
    fast = slow = dummy
    for _ in range(n + 1):
        fast = fast.next
    while fast:
        fast = fast.next
        slow = slow.next
    slow.next = slow.next.next
    return dummy.next
```

### 25. Middle of Linked List

```python
def middle_node(head):
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    return slow
```

---

## Trees & Graphs

```python
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
```

### 26. Maximum Depth

```python
def max_depth(root):
    if not root:
        return 0
    return 1 + max(max_depth(root.left), max_depth(root.right))
```

### 27. Invert Binary Tree

```python
def invert_tree(root):
    if not root:
        return None
    root.left, root.right = invert_tree(root.right), invert_tree(root.left)
    return root
```

### 28. Level Order Traversal

```python
from collections import deque

def level_order(root):
    if not root:
        return []
    result = []
    queue = deque([root])
    while queue:
        level = []
        for _ in range(len(queue)):
            node = queue.popleft()
            level.append(node.val)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        result.append(level)
    return result
```

### 29. Validate BST

```python
def is_valid_bst(root, lo=float('-inf'), hi=float('inf')):
    if not root:
        return True
    if not (lo < root.val < hi):
        return False
    return (is_valid_bst(root.left, lo, root.val) and
            is_valid_bst(root.right, root.val, hi))
```

### 30. Number of Islands

```python
def num_islands(grid):
    if not grid:
        return 0
    rows, cols = len(grid), len(grid[0])
    count = 0

    def dfs(r, c):
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != '1':
            return
        grid[r][c] = '0'
        dfs(r + 1, c)
        dfs(r - 1, c)
        dfs(r, c + 1)
        dfs(r, c - 1)

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1':
                count += 1
                dfs(r, c)
    return count
```

---

## SQL Reference (Quick)

```sql
-- Second highest salary
SELECT MAX(salary) FROM employees
WHERE salary < (SELECT MAX(salary) FROM employees);

-- More than manager
SELECT e.name FROM employees e
JOIN employees m ON e.manager_id = m.id
WHERE e.salary > m.salary;

-- Dept with no employees
SELECT d.dept_name FROM departments d
LEFT JOIN employees e ON d.dept_id = e.dept_id
WHERE e.id IS NULL;
```

Full SQL: [dbms-sql.md](dbms-sql.md)

---

## Trainer Note

When student code differs but works — accept if correct complexity and edge cases handled. These are reference implementations, not the only valid approach.

[← Mock pack](mock-interview-pack.md) · [TRAINER.md](../TRAINER.md)
