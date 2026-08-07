# Sorting, Searching & Recursion — Quick Revision

---

## Part 1: Sorting Algorithms

| Algorithm | Time (avg) | Time (worst) | Space | Stable? |
|-----------|------------|--------------|-------|---------|
| Bubble Sort | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(1) | No |
| Insertion Sort | O(n²) | O(n²) | O(1) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n²) | O(log n) stack | No |
| Heap Sort | O(n log n) | O(n log n) | O(1) | No |
| Counting Sort | O(n + k) | O(n + k) | O(k) | Yes |

**Stable sort:** Equal elements keep original relative order.

**When to use which:**
- General purpose → Merge sort / Quick sort / built-in `sort()`
- Nearly sorted small array → Insertion sort
- Small integer range → Counting sort

---

### Merge Sort

```
ALGORITHM MergeSort(arr, lo, hi)
BEGIN
    IF lo ≥ hi THEN RETURN END IF

    mid ← lo + (hi − lo) / 2
    MergeSort(arr, lo, mid)
    MergeSort(arr, mid + 1, hi)
    Merge(arr, lo, mid, hi)
END

ALGORITHM Merge(arr, lo, mid, hi)
BEGIN
    temp ← copy of arr[lo..hi]
    i ← lo, j ← mid + 1, k ← lo

    WHILE i ≤ mid AND j ≤ hi DO
        IF temp[i] ≤ temp[j] THEN arr[k] ← temp[i]; i ← i + 1
        ELSE arr[k] ← temp[j]; j ← j + 1
        k ← k + 1
    END WHILE
    // copy remaining
END
```

**Time:** O(n log n) &nbsp; **Space:** O(n)

---

### Quick Sort

```
ALGORITHM QuickSort(arr, lo, hi)
BEGIN
    IF lo < hi THEN
        pivot ← Partition(arr, lo, hi)
        QuickSort(arr, lo, pivot − 1)
        QuickSort(arr, pivot + 1, hi)
    END IF
END

ALGORITHM Partition(arr, lo, hi)
BEGIN
    pivot ← arr[hi]
    i ← lo − 1
    FOR j ← lo TO hi − 1 DO
        IF arr[j] < pivot THEN
            i ← i + 1
            SWAP(arr[i], arr[j])
        END IF
    END FOR
    SWAP(arr[i + 1], arr[hi])
    RETURN i + 1
END
```

**Time:** O(n log n) avg, O(n²) worst (bad pivot) &nbsp; **Space:** O(log n) stack

---

## Part 2: Searching

| Algorithm | Precondition | Time |
|-----------|--------------|------|
| Linear search | None | O(n) |
| Binary search | Sorted array | O(log n) |
| Ternary search | Sorted unimodal | O(log n) |

### Binary Search

```
ALGORITHM BinarySearch(arr, target)
PRECONDITION: arr sorted ascending

BEGIN
    lo ← 0, hi ← LENGTH(arr) − 1

    WHILE lo ≤ hi DO
        mid ← lo + (hi − lo) / 2
        IF arr[mid] = target THEN RETURN mid
        ELSE IF arr[mid] < target THEN lo ← mid + 1
        ELSE hi ← mid − 1
        END IF
    END WHILE

    RETURN −1
END
```

See [advanced-dsa.md](advanced-dsa.md) for lower bound and binary search on answer.

---

## Part 3: Recursion

### Template

```
ALGORITHM Recurse(input)
BEGIN
    IF base_case(input) THEN
        RETURN base_value
    END IF

    result ← Recurse(smaller_subproblem)
    RETURN combine(input, result)
END
```

Every recursive function needs:
1. **Base case** — stops recursion
2. **Recursive case** — moves toward base case
3. **Progress** — input must shrink each call

```mermaid
flowchart TD
    A[Call f(n)] --> B{Base case?}
    B -->|Yes| C[Return direct answer]
    B -->|No| D[Call f(n-1) or smaller]
    D --> B
```

---

### Factorial / Fibonacci (Classic)

```
FACTORIAL(n):
    IF n ≤ 1 THEN RETURN 1
    RETURN n * FACTORIAL(n − 1)
Time: O(n), Space: O(n) stack

FIB(n) — naive:
    IF n ≤ 1 THEN RETURN n
    RETURN FIB(n−1) + FIB(n−2)
Time: O(2^n) — use DP for O(n)
```

---

### Recursion vs Iteration

| | Recursion | Iteration |
|-|-----------|-----------|
| Code | Cleaner for trees/graphs | Often faster |
| Space | Call stack O(depth) | Usually O(1) |
| Risk | Stack overflow on deep input | Infinite loop if wrong |

**Convert recursion → iteration:** Use explicit stack (DFS) or queue (BFS).

---

### Tail Recursion (Concept)

Last operation is recursive call — compiler *may* optimize to loop (not guaranteed in Python/Java).

```
// Tail recursive factorial
FACTORIAL(n, acc=1):
    IF n ≤ 1 THEN RETURN acc
    RETURN FACTORIAL(n − 1, n * acc)
```

---

## Common Interview Questions

1. Merge sort vs quick sort — when prefer each?
2. Why is merge sort O(n log n) in all cases?
3. What makes quicksort O(n²) worst case?
4. Write binary search iteratively.
5. What happens if recursion has no base case? → Stack overflow.
6. Convert recursive tree DFS to iterative with a stack.

[← Back to index](../README.md) · [Complexity →](complexity-analysis.md)
