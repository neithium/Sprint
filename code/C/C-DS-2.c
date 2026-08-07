 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------
TYPEDEF
----------------------------------------------------------*/
typedef unsigned int uint;

typedef struct Node{
    int data;
    struct Node *next;
} Node;

/*----------------------------------------------------------
ENUM
----------------------------------------------------------*/
enum Day {MON,TUE,WED,THU,FRI,SAT,SUN};

/*----------------------------------------------------------
STRUCTURES
----------------------------------------------------------*/
struct Address{
    char city[30];
    int pin;
};

struct Student{
    char name[30];
    int age;
    struct Address addr;
};

/*----------------------------------------------------------
UNION

All members share the SAME memory.
Largest member determines union size.
----------------------------------------------------------*/
union Data{
    int i;
    float f;
    char str[20];
};

/*----------------------------------------------------------
FUNCTION POINTER TARGET
----------------------------------------------------------*/
int add(int a,int b){ return a+b; }

/*----------------------------------------------------------
LINKED LIST
----------------------------------------------------------*/
Node* createNode(int x){
    Node *n=(Node*)malloc(sizeof(Node));
    n->data=x;
    n->next=NULL;
    return n;
}

void insertEnd(Node **head,int x){
    Node *n=createNode(x);

    if(*head==NULL){
        *head=n;
        return;
    }

    Node *temp=*head;
    while(temp->next)
        temp=temp->next;

    temp->next=n;
}

void display(Node *head){
    while(head){
        printf("%d -> ",head->data);
        head=head->next;
    }
    printf("NULL\n");
}

void freeList(Node *head){
    while(head){
        Node *t=head;
        head=head->next;
        free(t);
    }
}

/*----------------------------------------------------------
STACK USING ARRAY
----------------------------------------------------------*/
#define SIZE 5

struct Stack{
    int arr[SIZE];
    int top;
};

void push(struct Stack *s,int x){
    if(s->top==SIZE-1){
        printf("Stack Overflow\n");
        return;
    }
    s->arr[++s->top]=x;
}

int pop(struct Stack *s){
    if(s->top==-1){
        printf("Stack Underflow\n");
        return -1;
    }
    return s->arr[s->top--];
}

/*----------------------------------------------------------
QUEUE USING ARRAY
----------------------------------------------------------*/
struct Queue{
    int arr[SIZE];
    int front,rear;
};

void enqueue(struct Queue *q,int x){
    if(q->rear==SIZE-1){
        printf("Queue Full\n");
        return;
    }

    if(q->front==-1)
        q->front=0;

    q->arr[++q->rear]=x;
}

int dequeue(struct Queue *q){
    if(q->front==-1 || q->front>q->rear){
        printf("Queue Empty\n");
        return -1;
    }

    return q->arr[q->front++];
}

int main(){

    printf("========== TYPEDEF ==========\n");
    uint x=100;
    printf("%u\n",x);

    printf("\n========== ENUM ==========\n");
    enum Day today=WED;
    printf("%d\n",today);

    printf("\n========== STRUCTURE ==========\n");
    struct Student s={"Alice",21,{"Mysuru",570001}};
    printf("%s %d %s %d\n",s.name,s.age,s.addr.city,s.addr.pin);

    printf("\n========== ARRAY OF STRUCTURES ==========\n");
    struct Student cls[2]={
        {"Bob",20,{"Bengaluru",560001}},
        {"John",22,{"Mysuru",570001}}
    };
    for(int i=0;i<2;i++)
        printf("%s %d\n",cls[i].name,cls[i].age);

    printf("\n========== UNION ==========\n");
    union Data d;
    d.i=100;
    printf("int=%d\n",d.i);
    d.f=3.14f;
    printf("float=%.2f\n",d.f);
    /* previous int overwritten */

    printf("\n========== POINTER TO POINTER ==========\n");
    int val=10;
    int *p=&val;
    int **pp=&p;
    printf("%d %d %d\n",val,*p,**pp);

    printf("\n========== FUNCTION POINTER ==========\n");
    int (*fp)(int,int)=add;
    printf("%d\n",fp(5,7));

    printf("\n========== LINKED LIST ==========\n");
    Node *head=NULL;
    insertEnd(&head,10);
    insertEnd(&head,20);
    insertEnd(&head,30);
    display(head);

    printf("\n========== STACK ==========\n");
    struct Stack st;
    st.top=-1;
    push(&st,5);
    push(&st,10);
    push(&st,15);
    printf("%d\n",pop(&st));

    printf("\n========== QUEUE ==========\n");
    struct Queue q;
    q.front=-1;
    q.rear=-1;
    enqueue(&q,100);
    enqueue(&q,200);
    enqueue(&q,300);
    printf("%d\n",dequeue(&q));

    printf("\n========== STORAGE CLASSES ==========\n");
    printf("auto     : default local variable\n");
    printf("static   : retains value between calls\n");
    printf("extern   : variable defined elsewhere\n");
    printf("register : request CPU register (hint)\n");

    printf("\n========== PREPROCESSOR ==========\n");
    printf("#define : macro\n");
    printf("#ifdef/#ifndef : conditional compilation\n");
    printf("Header guards prevent multiple inclusion.\n");

    printf("\n========== COMMAND LINE ==========\n");
    printf("int main(int argc,char *argv[])\n");
    printf("argc = number of arguments\n");
    printf("argv = argument array\n");

    printf("\n========== MEMORY LAYOUT ==========\n");
    printf(
        "Text Segment : Program Instructions\n"
        "Data Segment : Initialized Globals/Statics\n"
        "BSS          : Uninitialized Globals/Statics\n"
        "Heap         : malloc/calloc/realloc\n"
        "Stack        : Function Calls & Local Variables\n"
    );

    printf("\n========== COMMON INTERVIEW FACTS ==========\n");
    printf("Structure members have separate memory.\n");
    printf("Union members share memory.\n");
    printf("Linked List insertion at head : O(1)\n");
    printf("Stack Push/Pop : O(1)\n");
    printf("Queue Enqueue/Dequeue : O(1)\n");
    printf("Function pointers enable callbacks.\n");
    printf("Pointer to pointer stores address of pointer.\n");

    freeList(head);

    return 0;
}
 