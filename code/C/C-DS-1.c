
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PI 3.14159
#define MAX 100

/*-----------------------------------------------------------
FUNCTION PROTOTYPES
-----------------------------------------------------------*/
int add(int a,int b);
int factorial(int n);
void swapByValue(int a,int b);
void swapByReference(int *a,int *b);

/* Global variable (lifetime = entire program) */
int globalVar = 50;

int main()
{
    printf("\n================ PROGRAM START ================\n");

    /*-------------------------------------------------------
    VARIABLES & DATA TYPES
    -------------------------------------------------------*/
    /*
        char    -> 1 byte
        int     -> usually 4 bytes
        float   -> 4 bytes
        double  -> 8 bytes
    */

    char grade='A';
    int age=21;
    float cgpa=8.75f;
    double salary=75000.50;

    printf("\n--- Data Types ---\n");
    printf("%c %d %.2f %.2lf\n",grade,age,cgpa,salary);

    /*-------------------------------------------------------
    CONSTANTS
    -------------------------------------------------------*/

    const int DAYS=7;

    printf("\nPI = %.5f\n",PI);
    printf("Days = %d\n",DAYS);

    /*-------------------------------------------------------
    INPUT / OUTPUT
    -------------------------------------------------------

    Uncomment if practicing.

    int n;
    scanf("%d",&n);
    printf("%d",n);

    -------------------------------------------------------*/

    /*-------------------------------------------------------
    OPERATORS
    -------------------------------------------------------*/

    int a=20,b=7;

    printf("\nArithmetic\n");
    printf("%d\n",a+b);
    printf("%d\n",a-b);
    printf("%d\n",a*b);
    printf("%d\n",a/b);
    printf("%d\n",a%b);

    printf("\nRelational\n");
    printf("%d\n",a>b);
    printf("%d\n",a==b);

    printf("\nLogical\n");
    printf("%d\n",(a>b)&&(b>0));
    printf("%d\n",(a>b)||(b<0));
    printf("%d\n",!(a>b));

    printf("\nBitwise\n");
    printf("%d\n",a&b);
    printf("%d\n",a|b);
    printf("%d\n",a^b);
    printf("%d\n",a<<1);
    printf("%d\n",a>>1);

    /*-------------------------------------------------------
    TYPE CASTING
    -------------------------------------------------------*/

    int x=5,y=2;

    printf("\nInteger division = %d\n",x/y);
    printf("Float division   = %.2f\n",(float)x/y);

    /*-------------------------------------------------------
    sizeof
    -------------------------------------------------------*/

    printf("\nsizeof(int) = %zu\n",sizeof(int));
    printf("sizeof(double) = %zu\n",sizeof(double));

    /*-------------------------------------------------------
    if else
    -------------------------------------------------------*/

    printf("\nDecision Making\n");

    if(age>=18)
        printf("Adult\n");
    else
        printf("Minor\n");

    /*-------------------------------------------------------
    switch
    -------------------------------------------------------*/

    int day=2;

    switch(day)
    {
        case 1:
            printf("Monday\n");
            break;

        case 2:
            printf("Tuesday\n");
            break;

        default:
            printf("Other\n");
    }

    /*-------------------------------------------------------
    LOOPS
    -------------------------------------------------------*/

    printf("\nFor Loop\n");

    for(int i=1;i<=5;i++)
        printf("%d ",i);

    printf("\nWhile Loop\n");

    int i=1;

    while(i<=3)
    {
        printf("%d ",i);
        i++;
    }

    printf("\nDo While\n");

    i=1;

    do
    {
        printf("%d ",i);
        i++;
    }while(i<=3);

    printf("\n");

    /*-------------------------------------------------------
    break / continue
    -------------------------------------------------------*/

    printf("\nBreak / Continue\n");

    for(i=1;i<=10;i++)
    {
        if(i==3)
            continue;

        if(i==8)
            break;

        printf("%d ",i);
    }

    printf("\n");

    /*-------------------------------------------------------
    FUNCTIONS
    -------------------------------------------------------*/

    printf("\nFunctions\n");

    printf("20+30=%d\n",add(20,30));

    /*-------------------------------------------------------
    RECURSION
    -------------------------------------------------------*/

    printf("\nFactorial 5 = %d\n",factorial(5));

    /*-------------------------------------------------------
    SCOPE
    -------------------------------------------------------*/

    int localVar=100;

    printf("\nGlobal=%d\n",globalVar);
    printf("Local=%d\n",localVar);

    /*-------------------------------------------------------
    ARRAYS
    -------------------------------------------------------*/

    int arr[5]={10,20,30,40,50};

    printf("\nArray Traversal\n");

    for(i=0;i<5;i++)
        printf("%d ",arr[i]);

    printf("\n");

    /*-------------------------------------------------------
    2D ARRAY
    -------------------------------------------------------*/

    int matrix[2][3]={
        {1,2,3},
        {4,5,6}
    };

    printf("\n2D Array\n");

    for(i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
            printf("%d ",matrix[i][j]);

        printf("\n");
    }

    /*-------------------------------------------------------
    STRINGS
    -------------------------------------------------------*/

    char name[30]="Interview";

    printf("\nLength=%zu\n",strlen(name));

    printf("Copy\n");

    char copy[30];

    strcpy(copy,name);

    printf("%s\n",copy);

    printf("Compare=%d\n",strcmp(name,copy));

    strcat(copy," Prep");

    printf("%s\n",copy);

    printf("toupper(I)=%c\n",toupper('i'));

    /*-------------------------------------------------------
    POINTERS
    -------------------------------------------------------

    Pointer stores ADDRESS.

    x
    Address : 1000
    Value   : 10

    ptr=&x

    ptr stores 1000

    *ptr gives value 10

    -------------------------------------------------------*/

    int value=10;

    int *ptr=&value;

    printf("\nPointers\n");

    printf("value=%d\n",value);
    printf("address=%p\n",(void*)&value);
    printf("ptr=%p\n",(void*)ptr);
    printf("*ptr=%d\n",*ptr);

    *ptr=100;

    printf("After modification value=%d\n",value);

    /*-------------------------------------------------------
    POINTER ARITHMETIC
    -------------------------------------------------------*/

    printf("\nPointer Arithmetic\n");

    int nums[5]={1,2,3,4,5};

    int *p=nums;

    for(i=0;i<5;i++)
        printf("%d ",*(p+i));

    printf("\n");

    /*-------------------------------------------------------
    ARRAY VS POINTER
    -------------------------------------------------------*/

    /*
       arr      -> address of first element

       arr[i] == *(arr+i)
    */

    printf("\nArray vs Pointer\n");

    printf("%d %d\n",nums[2],*(nums+2));

    /*-------------------------------------------------------
    CALL BY VALUE
    -------------------------------------------------------*/

    int n1=5,n2=10;

    swapByValue(n1,n2);

    printf("\nAfter Value Swap\n");
    printf("%d %d\n",n1,n2);

    /*-------------------------------------------------------
    CALL BY REFERENCE
    -------------------------------------------------------*/

    swapByReference(&n1,&n2);

    printf("\nAfter Reference Swap\n");
    printf("%d %d\n",n1,n2);

    /*-------------------------------------------------------
    DYNAMIC MEMORY
    -------------------------------------------------------

    malloc()

    Heap Memory

    ptr
      |
      v

    +----+----+----+----+----+

    free(ptr)

    -------------------------------------------------------*/

    int *dynamic=(int*)malloc(5*sizeof(int));

    if(dynamic==NULL)
    {
        printf("Allocation Failed\n");
        return 0;
    }

    for(i=0;i<5;i++)
        dynamic[i]=i*i;

    printf("\nMalloc\n");

    for(i=0;i<5;i++)
        printf("%d ",dynamic[i]);

    printf("\n");

    dynamic=(int*)realloc(dynamic,8*sizeof(int));

    for(i=5;i<8;i++)
        dynamic[i]=i*i;

    printf("\nRealloc\n");

    for(i=0;i<8;i++)
        printf("%d ",dynamic[i]);

    printf("\n");

    free(dynamic);

    dynamic=NULL;

    /*-------------------------------------------------------
    COMMON INTERVIEW TRICKS
    -------------------------------------------------------*/

    printf("\nInterview Notes\n");

    printf("sizeof(arr) = %zu bytes\n",sizeof(arr));
    printf("Number of elements = %zu\n",
           sizeof(arr)/sizeof(arr[0]));

    printf("\nTernary Operator\n");

    int max=(10>20)?10:20;

    printf("%d\n",max);

    printf("\n================ CHEAT SHEET ================\n");

    printf(
    "int      : Whole Numbers\n"
    "float    : Decimal (4 bytes)\n"
    "double   : High Precision\n"
    "char     : Character\n"
    "Pointer  : Stores Address\n"
    "malloc   : Heap Allocation\n"
    "free     : Release Heap Memory\n"
    "Array[i] == *(Array+i)\n"
    "Call by Reference uses pointers\n"
    "sizeof() computed at compile time (for arrays in scope)\n"
    );

    printf("\n================ END ========================\n");

    return 0;
}

/*-----------------------------------------------------------*/

int add(int a,int b)
{
    return a+b;
}

/*-----------------------------------------------------------*/

int factorial(int n)
{
    if(n<=1)
        return 1;

    return n*factorial(n-1);
}

/*-----------------------------------------------------------*/

void swapByValue(int a,int b)
{
    int temp=a;
    a=b;
    b=temp;

    printf("\nInside Value Swap : %d %d\n",a,b);
}

/*-----------------------------------------------------------*/

void swapByReference(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
 
