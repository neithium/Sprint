"""
=============================================================
        PYTHON INTERVIEW REVISION - ONE COMPLETE PROGRAM
=============================================================

Goal:
A single file that demonstrates nearly every Python concept
commonly required in entry-level SDE interviews.

Concepts Covered:
✔ Variables
✔ Dynamic Typing
✔ None
✔ Truthy/Falsy
✔ Operators
✔ Strings
✔ Lists
✔ Tuples
✔ Dictionaries
✔ Sets
✔ Counter
✔ defaultdict
✔ deque
✔ heapq
✔ Loops
✔ enumerate
✔ zip
✔ range
✔ List/Dict/Set Comprehension
✔ Lambda
✔ Sorting
✔ Functions
✔ *args / **kwargs
✔ Exception Handling
✔ Classes
✔ Modules
✔ Useful Built-ins
✔ Membership
✔ Time Complexity Notes
✔ Common Interview Idioms

Run this file and read through it before interviews.
=============================================================
"""

import math
import heapq
from collections import Counter, defaultdict, deque


# ==========================================================
# VARIABLES
# ==========================================================

print("\n========== VARIABLES ==========")

x = 10
y = 5.5
name = "Alice"
flag = True

print(type(x))
print(type(y))
print(type(name))
print(type(flag))


# Dynamic Typing

x = "Now I'm a String"
print(x)

# Multiple Assignment

a, b = 10, 20
print(a, b)

# Swap

a, b = b, a
print("Swap:", a, b)

# None

temp = None
print(temp)

# Truthy / Falsy

if []:
    print("Never")

if not []:
    print("Empty list is False")

if "Python":
    print("Non-empty string is True")


# ==========================================================
# OPERATORS
# ==========================================================

print("\n========== OPERATORS ==========")

print(10 + 3)
print(10 - 3)
print(10 * 3)
print(10 / 3)
print(10 // 3)
print(10 % 3)
print(2 ** 5)

print(5 > 3)
print(5 == 5)
print(5 != 4)

print(True and False)
print(True or False)
print(not True)

print(3 in [1,2,3])
print(7 not in [1,2,3])

a = None
b = None

print(a is b)


# ==========================================================
# STRINGS
# ==========================================================

print("\n========== STRINGS ==========")

s = "Interview"

print(s.lower())
print(s.upper())

print(s.strip())

print(s.replace("view","VIEW"))

print(s.find("view"))

print(s.count("e"))

print(s.startswith("Int"))
print(s.endswith("iew"))

print(s[::-1])

print(s[:5])

print(s.split("e"))

words = ["Python","is","Awesome"]

print(" ".join(words))

print(ord('A'))
print(chr(66))


# ==========================================================
# LIST
# ==========================================================

print("\n========== LIST ==========")

nums = [5,3,8]

nums.append(10)
nums.extend([11,12])

nums.insert(1,100)

nums.remove(3)

nums.pop()

copy = nums.copy()

nums.sort()

nums.reverse()

print(nums)

print(nums[:])

print(nums[1:])

print(nums[:-1])

print(nums[::-1])


# ==========================================================
# TUPLES
# ==========================================================

print("\n========== TUPLE ==========")

point = (100,200)

x,y = point

print(x)
print(y)


# ==========================================================
# DICTIONARY
# ==========================================================

print("\n========== DICTIONARY ==========")

student = {
    "name":"Bob",
    "age":20
}

student["cgpa"]=9.8

print(student.get("marks",0))

student.setdefault("branch","CSE")

student.update({"college":"VVCE"})

for k,v in student.items():
    print(k,v)

print(student.keys())

print(student.values())

student.pop("age")

print(student)


# ==========================================================
# SET
# ==========================================================

print("\n========== SET ==========")

A = {1,2,3,4}
B = {3,4,5}

A.add(10)

A.discard(2)

print(A)

print(A.union(B))

print(A.intersection(B))

print(A.difference(B))

print(A.symmetric_difference(B))


# ==========================================================
# COUNTER
# ==========================================================

print("\n========== COUNTER ==========")

cnt = Counter("banana")

print(cnt)

print(cnt['a'])

print(cnt.most_common(2))


# ==========================================================
# DEFAULTDICT
# ==========================================================

print("\n========== DEFAULTDICT ==========")

graph = defaultdict(list)

graph[1].append(2)
graph[1].append(3)
graph[2].append(5)

print(graph)


# ==========================================================
# DEQUE
# ==========================================================

print("\n========== DEQUE ==========")

dq = deque()

dq.append(10)
dq.appendleft(5)

dq.append(20)

print(dq)

print(dq.pop())

print(dq.popleft())


# ==========================================================
# HEAP
# ==========================================================

print("\n========== HEAP ==========")

heap = []

for x in [5,2,8,1,7]:
    heapq.heappush(heap,x)

print(heap)

print(heapq.heappop(heap))

print(heapq.nlargest(2,heap))

print(heapq.nsmallest(2,heap))

# Max Heap

maxheap=[]

for x in [5,2,8]:
    heapq.heappush(maxheap,-x)

print(-heapq.heappop(maxheap))


# ==========================================================
# LOOPS
# ==========================================================

print("\n========== LOOPS ==========")

for i in range(5):
    print(i)

i=0

while i<3:
    print(i)
    i+=1

for i in range(10):

    if i==2:
        continue

    if i==6:
        break

    print(i)

pass


# ==========================================================
# ENUMERATE
# ==========================================================

print("\n========== ENUMERATE ==========")

nums=[10,20,30]

for index,value in enumerate(nums):
    print(index,value)


# ==========================================================
# ZIP
# ==========================================================

print("\n========== ZIP ==========")

names=["Alice","Bob","Charlie"]

marks=[90,80,95]

for n,m in zip(names,marks):
    print(n,m)


# ==========================================================
# RANGE
# ==========================================================

print("\n========== RANGE ==========")

print(list(range(5)))

print(list(range(3,8)))

print(list(range(0,20,5)))

print(list(range(10,-1,-1)))


# ==========================================================
# COMPREHENSIONS
# ==========================================================

print("\n========== COMPREHENSIONS ==========")

nums=[1,2,3,4,5]

square=[x*x for x in nums]

print(square)

even=[x for x in nums if x%2==0]

print(even)

dictionary={x:x*x for x in nums}

print(dictionary)

unique={x%3 for x in nums}

print(unique)


# ==========================================================
# LAMBDA
# ==========================================================

print("\n========== LAMBDA ==========")

pairs=[(3,"c"),(1,"a"),(2,"b")]

pairs.sort(key=lambda x:x[0])

print(pairs)

students=[
    ("Bob",20),
    ("Alice",19),
    ("John",20)
]

print(sorted(students,key=lambda x:(x[1],x[0])))


# ==========================================================
# FUNCTIONS
# ==========================================================

print("\n========== FUNCTIONS ==========")

def add(a,b=0):
    return a+b

print(add(5))
print(add(5,10))

def total(*args):
    return sum(args)

print(total(1,2,3,4))

def info(**kwargs):

    for k,v in kwargs.items():
        print(k,v)

info(name="Alice",cgpa=9.7)


# ==========================================================
# EXCEPTION HANDLING
# ==========================================================

print("\n========== EXCEPTION ==========")

try:

    print(10/0)

except ZeroDivisionError:

    print("Division by zero!")

finally:

    print("Finally always runs")


# ==========================================================
# CLASS
# ==========================================================

print("\n========== CLASS ==========")

class Node:

    def __init__(self,val):

        self.val=val
        self.next=None

head=Node(10)
head.next=Node(20)
head.next.next=Node(30)

temp=head

while temp:

    print(temp.val)

    temp=temp.next


# ==========================================================
# MODULES
# ==========================================================

print("\n========== MODULES ==========")

print(math.sqrt(81))
print(math.factorial(5))


# ==========================================================
# USEFUL BUILTINS
# ==========================================================

print("\n========== BUILTINS ==========")

nums=[5,1,8,2]

print(len(nums))
print(sum(nums))
print(max(nums))
print(min(nums))
print(abs(-10))
print(round(3.14159,2))

print(sorted(nums))

print(list(reversed(nums)))

print(any([0,0,1]))

print(all([1,2,3]))

print(list(map(lambda x:x*x,nums)))

print(list(filter(lambda x:x%2==0,nums)))

print(list(enumerate(nums)))

print(list(zip(nums,["a","b","c","d"])))


# ==========================================================
# MEMBERSHIP
# ==========================================================

print("\n========== MEMBERSHIP ==========")

print(2 in nums)

print(10 not in nums)

print("name" in student)

print(3 in A)


# ==========================================================
# COMMON INTERVIEW IDIOMS
# ==========================================================

print("\n========== INTERVIEW IDIOMS ==========")

s="python"

# Reverse

print(s[::-1])

# Frequency

freq=Counter(s)

print(freq)

# Visited

visited=set()

visited.add(1)

# Queue

queue=deque()

queue.append(100)

# Stack

stack=[]

stack.append(10)

stack.append(20)

print(stack.pop())

# Dictionary Default

print(student.get("salary",0))

# Infinite

INF=float("inf")

NEG_INF=float("-inf")

print(INF)
print(NEG_INF)

# Swap

a,b=1,2
a,b=b,a

print(a,b)


# ==========================================================
# MEMBERSHIP COMPLEXITIES
# ==========================================================

print("\n========== COMPLEXITIES ==========")

print("""
List Search          : O(n)

Dictionary Search    : O(1)

Set Search           : O(1)

Heap Push            : O(log n)

Heap Pop             : O(log n)

Append List          : O(1)

Deque Append         : O(1)

Deque Pop            : O(1)

Counter Lookup       : O(1)

DefaultDict Lookup   : O(1)
""")

print("\n================== END OF REVISION ==================")


# unpacking
a, *middle, b = [1, 2, 3, 4, 5]
print(a)       # 1
print(middle)  # [2, 3, 4]
print(b)       # 5

# iterable unpacking
x, y, z = range(3)

# swapping
a, b = b, a

float("inf")
float("-inf")

# Empty dictionary
d = {}

# Empty set (not {})
s = set()

# Empty list
l = []

# Empty tuple
t = ()