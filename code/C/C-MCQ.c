 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int square(int x){ return x*x; }

int main(void)
{
    printf("This file is meant for reading, not just executing.\n");
    return 0;
}

/*==========================================================
1. sizeof(char)
------------------------------------------------------------
Q: sizeof(char)?

A:
Always 1 byte.
==========================================================*/

/*==========================================================
2. sizeof('A')
------------------------------------------------------------
sizeof('A')

Answer:
sizeof(int)

Reason:
Character literals in C have type int.
==========================================================*/

/*==========================================================
3. sizeof(array) vs sizeof(pointer)

int arr[10];
int *p = arr;

sizeof(arr) -> 10*sizeof(int)
sizeof(p)   -> size of pointer (usually 8 bytes on 64-bit)
==========================================================*/

/*==========================================================
4. Array vs Pointer

arr[3] == *(arr+3)

BUT

arr++      // ERROR
p++        // VALID
==========================================================*/

/*==========================================================
5. String Literal vs Character Array

char s1[] = "Hello";
char *s2 = "Hello";

s1[0]='h';      // VALID
s2[0]='h';      // Undefined Behaviour

Reason:
String literals should be treated as read-only.
==========================================================*/

/*==========================================================
6. NULL Pointer

int *p = NULL;

Never dereference NULL.

*p    // Crash / Undefined Behaviour
==========================================================*/

/*==========================================================
7. Wild Pointer

int *p;

Uninitialized pointer.

Using it is Undefined Behaviour.
==========================================================*/

/*==========================================================
8. Dangling Pointer

int *p = malloc(sizeof(int));
free(p);

/* p is dangling */

p = NULL;   // Best practice
 

/*==========================================================
9. malloc vs calloc

malloc(n*sizeof(int))
- uninitialized memory

calloc(n,sizeof(int))
- zero initialized memory
==========================================================*/

/*==========================================================
10. realloc

May move memory.

Always assign carefully.

int *tmp = realloc(ptr,newSize);

if(tmp)
    ptr = tmp;
==========================================================*/

/*==========================================================
11. free(NULL)

Perfectly safe.

free(NULL);
==========================================================*/

/*==========================================================
12. Double Free

free(ptr);
free(ptr);

Undefined Behaviour.
==========================================================*/

/*==========================================================
13. Memory Leak

malloc(...)
No free()

Heap memory leaked.
==========================================================*/

/*==========================================================
14. Pass by Value

C ALWAYS passes arguments by value.

"Pass by reference" is simulated using pointers.
==========================================================*/

/*==========================================================
15. ++i vs i++

++i
Increment first.

i++
Use first, increment later.
==========================================================*/

/*==========================================================
16. Undefined Behaviour

printf("%d %d", i++, i++);

Never rely on evaluation order.
==========================================================*/

/*==========================================================
17. Short Circuit

if(ptr && ptr->next)

Safe.

if(ptr->next && ptr)

Wrong.
==========================================================*/

/*==========================================================
18. const

const int *p
Pointer to constant data.

int *const p
Constant pointer.

const int *const p
Both constant.
==========================================================*/

/*==========================================================
19. void *

Generic pointer.

Must cast before dereferencing.

void *vp;
int *ip = (int*)vp;
==========================================================*/

/*==========================================================
20. Pointer Arithmetic

int arr[5];

arr+1

Moves sizeof(int) bytes,
NOT one byte.
==========================================================*/

/*==========================================================
21. Function Pointer

int (*fp)(int)=square;

Useful for callbacks.
==========================================================*/

/*==========================================================
22. Structure vs Union

Structure
---------
Each member has separate storage.

Union
-----
Members share storage.

Only one valid at a time.
==========================================================*/

/*==========================================================
23. sizeof(struct)

Padding may increase size.

Don't assume sum of members.
==========================================================*/

/*==========================================================
24. Stack vs Heap

Stack
-----
Automatic
Fast
Limited

Heap
----
malloc
free
Manual management
==========================================================*/

/*==========================================================
25. Recursion

Each recursive call gets its own stack frame.

Too deep -> Stack Overflow.
==========================================================*/

/*==========================================================
26. gets()

Never use gets().

Use fgets().
==========================================================*/

/*==========================================================
27. scanf("%s")

Stops at whitespace.

Use fgets() for full lines.
==========================================================*/

/*==========================================================
28. strcpy()

No bounds checking.

Prefer strncpy() when appropriate.
==========================================================*/

/*==========================================================
29. strcmp()

Returns

0 -> equal

<0

>0

NOT true/false.
==========================================================*/

/*==========================================================
30. Assignment vs Comparison

if(a = 5)

Assignment.

if(a == 5)

Comparison.
==========================================================*/

/*==========================================================
31. ========== HPE FAVORITES ==========

Difference:

char *p = "abc";
char a[] = "abc";

---------------------------------------

malloc vs calloc

---------------------------------------

What happens after free(ptr)?

---------------------------------------

Difference:

sizeof(arr)

sizeof(ptr)

---------------------------------------

Why can't we return address
of a local variable?

---------------------------------------

Difference:

Stack
Heap

---------------------------------------

Difference:

Structure
Union

---------------------------------------

What is a dangling pointer?

---------------------------------------

What is a wild pointer?

---------------------------------------

Difference:

++i

i++

---------------------------------------

What is pointer arithmetic?

---------------------------------------

Explain

const int *p

int *const p

---------------------------------------

What is a function pointer?

---------------------------------------

Why is

printf("%d",i++ + ++i);

Undefined Behaviour?

==========================================================*/

/*==========================================================
QUICK CHEAT SHEET

sizeof(char)      -> 1

sizeof(pointer)   -> 8 (usually 64-bit)

Array name        -> First element address

malloc            -> Uninitialized

calloc            -> Zero initialized

free(NULL)        -> Safe

NULL dereference  -> UB

Double free       -> UB

Wild Pointer      -> Uninitialized pointer

Dangling Pointer  -> Freed pointer

Stack             -> Automatic

Heap              -> Dynamic

Structure         -> Separate memory

Union             -> Shared memory

==========================================================*/
 