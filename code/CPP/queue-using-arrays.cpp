#include <iostream>
using namespace std;


// ============================================================
// 1. LINEAR QUEUE
// ============================================================

class Queue
{
private:
    int arr[5];
    int front;
    int rear;

public:

    Queue()
    {
        front = -1;
        rear = -1;
    }

    bool isEmpty()
    {
        return front == -1;
    }

    bool isFull()
    {
        return rear == 4;
    }

    void enqueue(int value)
    {
        if(isFull())
        {
            cout << "Queue Overflow\n";
            return;
        }

        if(isEmpty())
            front = 0;

        rear++;
        arr[rear] = value;
    }

    void dequeue()
    {
        if(isEmpty())
        {
            cout << "Queue Underflow\n";
            return;
        }

        if(front == rear)
        {
            front = -1;
            rear = -1;
            return;
        }

        front++;
    }

    int getFront()
    {
        if(isEmpty())
            return -1;

        return arr[front];
    }

    int getRear()
    {
        if(isEmpty())
            return -1;

        return arr[rear];
    }
};


// ============================================================
// 2. CIRCULAR QUEUE
// ============================================================

class CircularQueue
{
private:
    int arr[5];
    int front;
    int rear;
    int capacity;

public:

    CircularQueue()
    {
        front = -1;
        rear = -1;
        capacity = 5;
    }

    bool isEmpty()
    {
        return front == -1;
    }

    bool isFull()
    {
        return (rear + 1) % capacity == front;
    }

    void enqueue(int value)
    {
        if(isFull())
        {
            cout << "Circular Queue Overflow\n";
            return;
        }

        if(isEmpty())
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % capacity;
        }

        arr[rear] = value;
    }

    void dequeue()
    {
        if(isEmpty())
        {
            cout << "Circular Queue Underflow\n";
            return;
        }

        if(front == rear)
        {
            front = -1;
            rear = -1;
            return;
        }

        front = (front + 1) % capacity;
    }

    int getFront()
    {
        if(isEmpty())
            return -1;

        return arr[front];
    }

    int getRear()
    {
        if(isEmpty())
            return -1;

        return arr[rear];
    }
};


// ============================================================
// 3. LINEAR DEQUE
// ============================================================

class Deque
{
private:
    int arr[5];
    int front;
    int rear;

public:

    Deque()
    {
        front = -1;
        rear = -1;
    }

    bool isEmpty()
    {
        return front == -1;
    }

    bool isFull()
    {
        return (front == 0 && rear == 4);
    }

    void pushFront(int value)
    {
        if(isFull())
        {
            cout << "Deque Overflow\n";
            return;
        }

        if(isEmpty())
        {
            front = 0;
            rear = 0;
            arr[front] = value;
            return;
        }

        if(front == 0)
        {
            cout << "No space at front\n";
            return;
        }

        front--;
        arr[front] = value;
    }

    void pushBack(int value)
    {
        if(isFull())
        {
            cout << "Deque Overflow\n";
            return;
        }

        if(isEmpty())
        {
            front = 0;
            rear = 0;
            arr[rear] = value;
            return;
        }

        if(rear == 4)
        {
            cout << "No space at back\n";
            return;
        }

        rear++;
        arr[rear] = value;
    }

    void popFront()
    {
        if(isEmpty())
        {
            cout << "Deque Underflow\n";
            return;
        }

        if(front == rear)
        {
            front = -1;
            rear = -1;
            return;
        }

        front++;
    }

    void popBack()
    {
        if(isEmpty())
        {
            cout << "Deque Underflow\n";
            return;
        }

        if(front == rear)
        {
            front = -1;
            rear = -1;
            return;
        }

        rear--;
    }

    int getFront()
    {
        if(isEmpty())
            return -1;

        return arr[front];
    }

    int getRear()
    {
        if(isEmpty())
            return -1;

        return arr[rear];
    }
};


// ============================================================
// 4. CIRCULAR DEQUE
// ============================================================

class CircularDeque
{
private:
    int arr[5];
    int front;
    int rear;
    int capacity;

public:

    CircularDeque()
    {
        front = -1;
        rear = -1;
        capacity = 5;
    }

    bool isEmpty()
    {
        return front == -1;
    }

    bool isFull()
    {
        return (rear + 1) % capacity == front;
    }

    void pushFront(int value)
    {
        if(isFull())
        {
            cout << "Circular Deque Overflow\n";
            return;
        }

        if(isEmpty())
        {
            front = 0;
            rear = 0;
        }
        else
        {
            front = (front - 1 + capacity) % capacity;
        }

        arr[front] = value;
    }

    void pushBack(int value)
    {
        if(isFull())
        {
            cout << "Circular Deque Overflow\n";
            return;
        }

        if(isEmpty())
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % capacity;
        }

        arr[rear] = value;
    }

    void popFront()
    {
        if(isEmpty())
        {
            cout << "Circular Deque Underflow\n";
            return;
        }

        if(front == rear)
        {
            front = -1;
            rear = -1;
            return;
        }

        front = (front + 1) % capacity;
    }

    void popBack()
    {
        if(isEmpty())
        {
            cout << "Circular Deque Underflow\n";
            return;
        }

        if(front == rear)
        {
            front = -1;
            rear = -1;
            return;
        }

        rear = (rear - 1 + capacity) % capacity;
    }

    int getFront()
    {
        if(isEmpty())
            return -1;

        return arr[front];
    }

    int getRear()
    {
        if(isEmpty())
            return -1;

        return arr[rear];
    }
};


// ============================================================
// MAIN
// ============================================================

int main()
{
    // -------------------------
    // Linear Queue
    // -------------------------

    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Linear Queue Front: "
         << q.getFront() << endl;

    cout << "Linear Queue Rear: "
         << q.getRear() << endl;

    q.dequeue();

    cout << "After dequeue, Front: "
         << q.getFront() << endl;


    // -------------------------
    // Circular Queue
    // -------------------------

    CircularQueue cq;

    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);

    cq.dequeue();
    cq.dequeue();

    // Reuses positions at the beginning
    cq.enqueue(40);
    cq.enqueue(50);

    cout << "\nCircular Queue Front: "
         << cq.getFront() << endl;

    cout << "Circular Queue Rear: "
         << cq.getRear() << endl;


    // -------------------------
    // Linear Deque
    // -------------------------

    Deque d;

    d.pushBack(20);
    d.pushBack(30);
    d.pushFront(10);

    cout << "\nLinear Deque Front: "
         << d.getFront() << endl;

    cout << "Linear Deque Rear: "
         << d.getRear() << endl;

    d.popFront();
    d.popBack();

    cout << "After pop operations:\n";
    cout << "Front: " << d.getFront() << endl;
    cout << "Rear: " << d.getRear() << endl;


    // -------------------------
    // Circular Deque
    // -------------------------

    CircularDeque cd;

    cd.pushBack(20);
    cd.pushBack(30);
    cd.pushFront(10);
    cd.pushFront(5);

    cout << "\nCircular Deque Front: "
         << cd.getFront() << endl;

    cout << "Circular Deque Rear: "
         << cd.getRear() << endl;

    cd.popFront();
    cd.popBack();

    cout << "After pop operations:\n";
    cout << "Front: " << cd.getFront() << endl;
    cout << "Rear: " << cd.getRear() << endl;

    return 0;
}