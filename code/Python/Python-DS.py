"""
===========================================================
        PYTHON DATA STRUCTURES - INTERVIEW REVISION
===========================================================

Included:
1. Variables
2. List
3. Tuple
4. String
5. Set
6. Dictionary
7. Stack
8. Queue
9. Deque
10. Heap (Priority Queue)
11. Counter
12. defaultdict
13. OrderedDict
14. NamedTuple
15. Dataclass
16. Array
17. Linked List
18. Binary Tree
19. Graph (Adjacency List)
20. Trie
21. Disjoint Set (Union Find)

Collections Module:
- deque
- Counter
- defaultdict
- OrderedDict
- namedtuple

Heap:
- heapq

===========================================================
"""

from collections import deque, Counter, defaultdict, OrderedDict, namedtuple
from dataclasses import dataclass
import heapq
from array import array


# ===========================================================
# LIST
# ===========================================================

nums = [10, 20, 30]

nums.append(40)
nums.insert(1, 15)
nums.extend([50, 60])

nums.remove(20)
x = nums.pop()
nums.reverse()
nums.sort()

print("List:", nums)

# Traversal
for item in nums:
    print(item)

# List Comprehension
squares = [x*x for x in range(5)]
print(squares)


# ===========================================================
# TUPLE
# ===========================================================

point = (2, 5)

print(point[0])
print(len(point))

x, y = point

print(x, y)


# ===========================================================
# STRING
# ===========================================================

s = "Interview"

print(s.lower())
print(s.upper())
print(s[::-1])

print(s[:4])

print(s.replace("view", "VIEW"))

print(s.split("e"))

print("Python" + "3")

print("abc" * 3)


# ===========================================================
# SET
# ===========================================================

A = {1,2,3,4}
B = {3,4,5,6}

print(A | B)      # Union
print(A & B)      # Intersection
print(A - B)      # Difference
print(A ^ B)      # Symmetric Difference

A.add(10)
A.remove(2)

print(3 in A)


# ===========================================================
# DICTIONARY
# ===========================================================

student = {
    "name":"Alice",
    "age":20
}

student["cgpa"] = 9.5

print(student["name"])

print(student.get("marks",0))

for k,v in student.items():
    print(k,v)

del student["age"]


# ===========================================================
# STACK
# ===========================================================

stack = []

stack.append(10)
stack.append(20)
stack.append(30)

print(stack.pop())

print(stack[-1])


# ===========================================================
# QUEUE
# ===========================================================

queue = deque()

queue.append(1)
queue.append(2)
queue.append(3)

print(queue.popleft())

print(queue)


# ===========================================================
# DEQUE
# ===========================================================

dq = deque()

dq.append(10)
dq.appendleft(5)

dq.pop()
dq.append(20)

dq.popleft()

print(dq)


 
# ===========================================================
# COUNTER
# ===========================================================

cnt = Counter("banana")

print(cnt)

print(cnt['a'])

print(cnt.most_common(2))


# ===========================================================
# DEFAULTDICT
# ===========================================================

graph = defaultdict(list)

graph[1].append(2)
graph[1].append(3)
graph[2].append(4)

print(graph)


# ===========================================================
# ORDEREDDICT
# ===========================================================

od = OrderedDict()

od["A"]=1
od["B"]=2
od["C"]=3

print(od)


# ===========================================================
# NAMEDTUPLE
# ===========================================================

Student = namedtuple("Student",["name","cgpa"])

s = Student("Bob",9.2)

print(s.name)
print(s.cgpa)


# ===========================================================
# DATACLASS
# ===========================================================

@dataclass
class Employee:
    name:str
    salary:int

e = Employee("John",50000)

print(e)


# ===========================================================
# ARRAY
# ===========================================================

arr = array('i',[1,2,3,4])

arr.append(5)

print(arr)


# ===========================================================
# LINKED LIST
# ===========================================================

class Node:

    def __init__(self,data):
        self.data=data
        self.next=None

head = Node(10)
head.next = Node(20)
head.next.next = Node(30)

temp=head

while temp:
    print(temp.data,end=" ")
    temp=temp.next

print()


# ===========================================================
# BINARY TREE
# ===========================================================

class TreeNode:

    def __init__(self,val):
        self.val=val
        self.left=None
        self.right=None

root = TreeNode(1)
root.left = TreeNode(2)
root.right = TreeNode(3)
root.left.left = TreeNode(4)

def inorder(node):

    if not node:
        return

    inorder(node.left)
    print(node.val,end=" ")
    inorder(node.right)

print("Inorder:")
inorder(root)
print()

 

# ===========================================================
# COMMON BUILT-IN FUNCTIONS
# ===========================================================

nums=[4,8,1,7]

print(len(nums))
print(sum(nums))
print(max(nums))
print(min(nums))
print(sorted(nums))
print(reversed(nums))

print(any([0,0,1]))
print(all([1,2,3]))

print(enumerate(nums))

print(list(enumerate(nums)))

print(zip([1,2,3],['a','b','c']))


# ===========================================================
# TIME COMPLEXITIES
# ===========================================================

"""
LIST
Append                O(1)
Pop End               O(1)
Insert Middle         O(n)
Delete Middle         O(n)
Search                O(n)

SET
Insert                O(1)
Delete                O(1)
Search                O(1)

DICT
Insert                O(1)
Delete                O(1)
Search                O(1)

HEAP
Push                  O(log n)
Pop                   O(log n)
Peek                  O(1)

DEQUE
Append Left           O(1)
Append Right          O(1)
Pop Left              O(1)
Pop Right             O(1)

QUEUE
Enqueue               O(1)
Dequeue               O(1)

STACK
Push                  O(1)
Pop                   O(1)

UNION FIND
Find                  O(α(n))
Union                 O(α(n))
"""