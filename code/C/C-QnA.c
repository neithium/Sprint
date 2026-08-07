/*
C INTERVIEW QUESTIONS & ANSWERS (100)
HPE Revision
*/
#include <stdio.h>

int main(){printf("Read the comments.\n");return 0;}

/*
Q1. What is C?
Answer: A procedural, compiled, general-purpose programming language.
*/

/*
Q2. Why is C fast?
Answer: Compiled to native machine code with minimal runtime overhead.
*/

/*
Q3. Difference between compiler and interpreter?
Answer: Compiler translates whole program before execution; interpreter executes line-by-line.
*/

/*
Q4. What is a variable?
Answer: A named memory location.
*/

/*
Q5. What is a pointer?
Answer: A variable that stores an address.
*/

/*
Q6. What is NULL?
Answer: A pointer that intentionally points to no valid object.
*/

/*
Q7. What is a wild pointer?
Answer: An uninitialized pointer.
*/

/*
Q8. What is a dangling pointer?
Answer: A pointer to freed/out-of-scope memory.
*/

/*
Q9. malloc vs calloc
Answer: malloc leaves memory uninitialized; calloc zero-initializes.
*/

/*
Q10. What does realloc do?
Answer: Resizes a dynamic allocation and may move it.
*/

/*
Q11. Why call free()?
Answer: To avoid memory leaks.
*/

/*
Q12. Is free(NULL) safe?
Answer: Yes.
*/

/*
Q13. What is a memory leak?
Answer: Allocated heap memory that is never freed.
*/

/*
Q14. Stack vs Heap
Answer: Stack: automatic; Heap: dynamic/manual.
*/

/*
Q15. Array vs Pointer
Answer: Arrays have fixed storage; pointers are variables holding addresses.
*/

/*
Q16. Why can't arr++?
Answer: Array name is not a modifiable lvalue.
*/

/*
Q17. sizeof(array) vs sizeof(pointer)
Answer: Array gives total bytes; pointer gives pointer size.
*/

/*
Q18. Pass by value?
Answer: C always passes by value.
*/

/*
Q19. How simulate pass by reference?
Answer: Pass a pointer.
*/

/*
Q20. Difference between ++i and i++
Answer: Pre vs post increment.
*/

/*
Q21. Undefined behavior?
Answer: Program behavior not defined by the C standard.
*/

/*
Q22. Segmentation fault?
Answer: Invalid memory access.
*/

/*
Q23. Structure?
Answer: Groups heterogeneous members.
*/

/*
Q24. Union?
Answer: Members share the same storage.
*/

/*
Q25. Structure vs Union
Answer: Separate memory vs shared memory.
*/

/*
Q26. typedef?
Answer: Creates an alias for a type.
*/

/*
Q27. enum?
Answer: Named integer constants.
*/

/*
Q28. const?
Answer: Prevents modification through that identifier.
*/

/*
Q29. volatile?
Answer: Prevents optimization of accesses.
*/

/*
Q30. static local variable
Answer: Retains value across function calls.
*/

/*
Q31. extern
Answer: References a global defined elsewhere.
*/

/*
Q32. register
Answer: Optimization hint to compiler.
*/

/*
Q33. Recursive function
Answer: Function calling itself.
*/

/*
Q34. Base case?
Answer: Condition that stops recursion.
*/

/*
Q35. Function prototype
Answer: Declaration before definition.
*/

/*
Q36. Function pointer
Answer: Stores address of a function.
*/

/*
Q37. Void pointer
Answer: Generic pointer; cast before dereference.
*/

/*
Q38. String literal
Answer: Typically stored in read-only memory.
*/

/*
Q39. char* vs char[]
Answer: Pointer to literal vs modifiable array copy.
*/

/*
Q40. strlen
Answer: Returns string length excluding '\0'.
*/

/*
Q41. strcmp
Answer: 0 if equal, negative/positive otherwise.
*/

/*
Q42. strcpy
Answer: Copies strings; beware overflow.
*/

/*
Q43. fgets vs gets
Answer: Use fgets; gets is unsafe.
*/

/*
Q44. scanf("%s") limitation
Answer: Stops at whitespace.
*/

/*
Q45. Header file
Answer: Contains declarations/macros.
*/

/*
Q46. Header guard
Answer: Prevents multiple inclusion.
*/

/*
Q47. #define
Answer: Preprocessor macro.
*/

/*
Q48. Macro vs function
Answer: Macros are text substitution.
*/

/*
Q49. Conditional compilation
Answer: #ifdef/#ifndef.
*/

/*
Q50. Bitwise AND
Answer: &
*/

/*
Q51. Logical AND
Answer: &&
*/

/*
Q52. Left shift
Answer: Shifts bits left.
*/

/*
Q53. Right shift
Answer: Shifts bits right.
*/

/*
Q54. Endianess
Answer: Byte order in memory.
*/

/*
Q55. Little endian
Answer: Least significant byte first.
*/

/*
Q56. Big endian
Answer: Most significant byte first.
*/

/*
Q57. Alignment
Answer: Objects aligned for efficient access.
*/

/*
Q58. Padding
Answer: Extra bytes in structs for alignment.
*/

/*
Q59. sizeof(char)
Answer: Always 1.
*/

/*
Q60. sizeof('A')
Answer: sizeof(int) in C.
*/

/*
Q61. Local variable
Answer: Lives until function returns.
*/

/*
Q62. Global variable
Answer: Exists for entire program.
*/

/*
Q63. Static global
Answer: Visible only within file.
*/

/*
Q64. Text segment
Answer: Program instructions.
*/

/*
Q65. Data segment
Answer: Initialized globals/statics.
*/

/*
Q66. BSS
Answer: Uninitialized globals/statics.
*/

/*
Q67. Heap
Answer: Dynamic memory region.
*/

/*
Q68. Stack
Answer: Function call frames.
*/

/*
Q69. Command-line arguments
Answer: argc and argv.
*/

/*
Q70. main signature
Answer: int main(void) or int main(int,char**).
*/

/*
Q71. Return 0
Answer: Indicates successful execution.
*/

/*
Q72. Binary search complexity
Answer: O(log n).
*/

/*
Q73. Linear search complexity
Answer: O(n).
*/

/*
Q74. Array access complexity
Answer: O(1).
*/

/*
Q75. Linked-list search
Answer: O(n).
*/

/*
Q76. Linked-list insertion at head
Answer: O(1).
*/

/*
Q77. Stack push/pop
Answer: O(1).
*/

/*
Q78. Queue enqueue/dequeue
Answer: O(1).
*/

/*
Q79. LIFO
Answer: Stack order.
*/

/*
Q80. FIFO
Answer: Queue order.
*/

/*
Q81. What is a node?
Answer: Basic linked-list element.
*/

/*
Q82. Why linked list?
Answer: Dynamic size, easy insert/delete.
*/

/*
Q83. Disadvantage of linked list
Answer: No O(1) random access.
*/

/*
Q84. Double free
Answer: Undefined behavior.
*/

/*
Q85. Returning local address
Answer: Invalid; local object no longer exists.
*/

/*
Q86. Can malloc fail?
Answer: Yes, returns NULL.
*/

/*
Q87. Check malloc?
Answer: Always compare against NULL.
*/

/*
Q88. Difference int and unsigned
Answer: Unsigned has no negative values.
*/

/*
Q89. Implicit type conversion
Answer: Automatic promotion/conversion.
*/

/*
Q90. Explicit type casting
Answer: (type)expression.
*/

/*
Q91. Infinite loop
Answer: Loop with no terminating condition.
*/

/*
Q92. break
Answer: Exit loop/switch.
*/

/*
Q93. continue
Answer: Skip current iteration.
*/

/*
Q94. switch fallthrough
Answer: Occurs without break.
*/

/*
Q95. Ternary operator
Answer: condition ? a : b.
*/

/*
Q96. Why initialize variables?
Answer: Avoid undefined values.
*/

/*
Q97. What is EOF?
Answer: End-of-file indicator.
*/

/*
Q98. File pointer
Answer: FILE* handle to file stream.
*/

/*
Q99. fopen modes
Answer: r,w,a,rb,etc.
*/

/*
Q100. Difference == and =
Answer: Comparison vs assignment.
*/
