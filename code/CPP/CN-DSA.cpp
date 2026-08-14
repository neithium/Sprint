#include<bits/stdc++.h>

/*
    Implement a simple DNS Cache using:

    unordered_map + TTL

    Real-world idea:

    DNS lookup:

        google.com
             |
             v
        DNS Server
             |
             v
        142.250.x.x

    Instead of asking the DNS server every time,
    we store the result temporarily.

    Example:

        google.com -> 142.250.x.x
        TTL = 10 seconds

    If the entry is still valid:
        return the cached IP.

    If TTL has expired:
        remove it and perform a new lookup.

    Operations:

        get(domain)
            -> Return cached IP if valid
            -> Return "" if missing/expired

        put(domain, ip, ttl)
            -> Store IP with expiry time

    Average:
        get() -> O(1)
        put() -> O(1)
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>

using namespace std;

class DNSCache
{
private:

    struct Entry
    {
        string ip;

        // Time at which this entry expires
        long long expiry;
    };

    unordered_map<string, Entry> cache;

    long long currentTime()
    {
        return chrono::duration_cast<chrono::seconds>(
            chrono::system_clock::now().time_since_epoch()
        ).count();
    }

public:

    void put(string domain, string ip, int ttl)
    {
        long long expiryTime = currentTime() + ttl;

        cache[domain] = {ip, expiryTime};
    }

    string get(string domain)
    {
        // Domain does not exist
        if (cache.find(domain) == cache.end())
        {
            return "";
        }

        Entry entry = cache[domain];

        // TTL expired
        if (currentTime() >= entry.expiry)
        {
            cache.erase(domain);
            return "";
        }

        // Valid cached entry
        return entry.ip;
    }
};


int main()
{
    DNSCache dns;

    // Store DNS result for 5 seconds
    dns.put("google.com", "142.250.190.14", 5);

    string ip = dns.get("google.com");

    if (ip != "")
        cout << "Cached IP: " << ip << endl;
    else
        cout << "DNS lookup required" << endl;

    return 0;
}

/*
===============================================================================
                    LRU CACHE — CN + DSA INTERVIEW PROBLEM
===============================================================================

PROBLEM:

Implement an LRU (Least Recently Used) Cache.

A cache stores frequently/recently accessed data so that we don't have to
retrieve it again from a slower source.

Real-world examples:

    - Browser cache
    - DNS cache
    - Web/proxy cache
    - Database cache

Suppose our cache capacity is 3:

    Google
    YouTube
    GitHub

Now the user accesses:

    Google

Google has now become the MOST RECENTLY USED item.

Cache order:

    Google
    YouTube
    GitHub

Now the user accesses:

    LeetCode

The cache is full, so we need to remove the LEAST RECENTLY USED item.

If YouTube was the least recently used:

    Google
    GitHub
    LeetCode

YouTube gets removed.


===============================================================================
                              REQUIREMENTS
===============================================================================

We need two operations:

1. get(key)

    If key exists:
        - return its value
        - mark it as MOST RECENTLY USED

    If key does not exist:
        - return -1


2. put(key, value)

    If key already exists:
        - update its value
        - mark it as MOST RECENTLY USED

    If key does not exist:
        - if cache is full:
              remove the LEAST RECENTLY USED item
        - insert the new item as MOST RECENTLY USED


IMPORTANT:

    Both get() and put() should ideally be O(1).


===============================================================================
                         WHY IS THIS A DSA PROBLEM?
===============================================================================

We need TWO things:

1. Fast lookup by key
2. Fast ordering based on "recently used"

An unordered_map gives us:

    key -> location of the item

Average lookup:

    O(1)


But a HashMap alone cannot efficiently tell us:

    "Which item was used least recently?"

So we need another data structure to maintain the order.


===============================================================================
                         DATA STRUCTURE WE USE
===============================================================================

We use:

    unordered_map
          +
    doubly linked list


The doubly linked list stores items in this order:

    FRONT                         BACK
      ↓                             ↓
    MRU                          LRU
    Most Recently Used           Least Recently Used

Example:

    FRONT
      ↓
    [Google] <-> [GitHub] <-> [YouTube]
                                  ↑
                                 BACK

Google = most recently used
YouTube = least recently used


WHY A DOUBLY LINKED LIST?

Suppose we know that YouTube is at some node.

We want to remove it in O(1).

A doubly linked list allows us to remove a known node in O(1):

    previous <-> node <-> next

We can reconnect:

    previous <-> next


WHY NOT A VECTOR?

If we remove an element from the middle of a vector:

    [A B C D E]
        ↑

Removing C requires shifting elements.

That is O(N).

A doubly linked list can remove a known node in O(1).


===============================================================================
                           WHY USE A HASHMAP?
===============================================================================

Suppose our linked list is:

    [Google] <-> [GitHub] <-> [YouTube]

If get("GitHub") comes in, we need to find GitHub quickly.

Searching the linked list would take O(N).

Instead:

    unordered_map<int, list<pair<int,int>>::iterator>

maps:

    key -> location of that key in the linked list


For example:

    map:
        1 -> iterator pointing to node 1
        2 -> iterator pointing to node 2
        3 -> iterator pointing to node 3


Therefore:

    HashMap lookup = O(1) average

    Linked List movement/removal = O(1)


Together:

    get() = O(1) average
    put() = O(1) average


===============================================================================
                         THE MAIN IDEA TO REMEMBER
===============================================================================

Think of the list as:

    FRONT = MOST RECENTLY USED
    BACK  = LEAST RECENTLY USED


Whenever an item is accessed:

    1. Remove it from its current position.
    2. Put it at the FRONT.


Whenever we insert a new item:

    Put it at the FRONT.


Whenever the cache is full:

    Remove the item from the BACK.


That is basically the entire LRU algorithm.


===============================================================================
                              DRY RUN
===============================================================================

Capacity = 3


put(1, 100)

    [1:100]


put(2, 200)

    [2:200] -> [1:100]

2 = MRU
1 = LRU


put(3, 300)

    [3:300] -> [2:200] -> [1:100]

3 = MRU
1 = LRU


get(1)

We found 1.

Move it to the FRONT:

    [1:100] -> [3:300] -> [2:200]

Now:

    1 = MRU
    2 = LRU


put(4, 400)

Cache is full.

Remove the BACK:

    2 is removed

Then insert 4 at the FRONT:

    [4:400] -> [1:100] -> [3:300]

So 2 was evicted.


===============================================================================
                              CODE
===============================================================================
*/

#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache
{
private:

    /*
        Capacity = maximum number of items the cache can hold.
    */
    int capacity;


    /*
        Doubly linked list.

        Each node contains:

            {key, value}

        FRONT = Most Recently Used
        BACK  = Least Recently Used
    */
    list<pair<int, int>> dll;


    /*
        HashMap:

            key -> iterator pointing to that key's node in dll

        This allows us to find an item in O(1) average time.

        Example:

            mp[10] -> iterator pointing to {10, 100}
    */
    unordered_map<int, list<pair<int, int>>::iterator> mp;


public:

    /*
        Constructor.

        Example:

            LRUCache cache(3);

        means the cache can store at most 3 items.
    */
    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }


    /*
        GET OPERATION
        -------------


        If key does not exist:

            return -1


        If key exists:

            1. Get its current node.
            2. Remove it from the current position.
            3. Insert it at the FRONT.
            4. Update the HashMap iterator.
            5. Return the value.


        Why move it to the front?

        Because accessing an item makes it the
        MOST RECENTLY USED item.


        Time Complexity:

            O(1) average
    */
    int get(int key)
    {
        /*
            Check whether key exists.

            find() is used instead of mp[key] because using
            mp[key] for a missing key would create a new entry.
        */
        if (mp.find(key) == mp.end())
        {
            return -1;
        }


        /*
            mp[key] contains an iterator pointing to the node.

            Example:

                mp[10]
                  |
                  v
                {10,100}
        */
        auto it = mp[key];


        /*
            Save the value before removing the node.
        */
        int value = it->second;


        /*
            Remove the node from its current position.

            Because we already have the iterator,
            list::erase() is O(1).
        */
        dll.erase(it);


        /*
            Put the item at the FRONT.

            FRONT = Most Recently Used.
        */
        dll.push_front({key, value});


        /*
            The old iterator is no longer valid.

            Therefore update the HashMap so that it points
            to the new node at the front.
        */
        mp[key] = dll.begin();


        /*
            Return the cached value.
        */
        return value;
    }


    /*
        PUT OPERATION
        -------------


        Case 1:
        Key already exists.

            Example:

                [3:300] -> [2:200] -> [1:100]

            put(2, 999)

            We should update 2:

                [2:999] -> [3:300] -> [1:100]


        Case 2:
        Key does not exist AND cache is full.

            Remove the BACK.

            BACK = Least Recently Used.


        Case 3:
        Key does not exist AND cache is not full.

            Simply insert at the FRONT.


        Time Complexity:

            O(1) average
    */
    void put(int key, int value)
    {
        /*
            CASE 1:

            Key already exists.
        */
        if (mp.find(key) != mp.end())
        {
            /*
                Remove the old node.

                We don't want two copies of the same key.
            */
            dll.erase(mp[key]);


            /*
                Insert the updated value at the FRONT.

                Updating an item also makes it
                MOST RECENTLY USED.
            */
            dll.push_front({key, value});


            /*
                Update the iterator in the HashMap.
            */
            mp[key] = dll.begin();

            return;
        }


        /*
            CASE 2:

            Key does not exist.

            Check whether cache is full.
        */
        if (dll.size() == capacity)
        {
            /*
                The BACK contains the Least Recently Used item.

                Example:

                    FRONT                    BACK
                      ↓                        ↓
                    [4] -> [1] -> [3] -> [2]

                    2 = LRU

                So remove 2.
            */

            auto last = dll.back();


            /*
                Remove the LRU key from the HashMap first.
            */
            mp.erase(last.first);


            /*
                Remove the LRU node from the list.
            */
            dll.pop_back();
        }


        /*
            Insert the new item at the FRONT.

            New items are considered
            MOST RECENTLY USED.
        */
        dll.push_front({key, value});


        /*
            Store its iterator in the HashMap.
        */
        mp[key] = dll.begin();
    }


    /*
        Optional helper function.

        This is NOT required for the LRU algorithm.

        It simply prints the cache from:

            MRU -> LRU

        Useful for understanding and testing the implementation.
    */
    void display()
    {
        cout << "Cache (MRU -> LRU): ";

        for (auto node : dll)
        {
            cout << "[" << node.first
                 << ":" << node.second << "] ";
        }

        cout << endl;
    }
};


/*
===============================================================================
                              DRIVER CODE
===============================================================================
*/

int main()
{
    /*
        Create an LRU cache with capacity 3.
    */
    LRUCache cache(3);


    /*
        Add three elements.

        Cache:

            3 -> 2 -> 1

        3 = MRU
        1 = LRU
    */
    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);

    cache.display();


    /*
        Access key 1.

        1 becomes the Most Recently Used.

        Before:

            3 -> 2 -> 1

        After:

            1 -> 3 -> 2
    */
    cout << "get(1): "
         << cache.get(1)
         << endl;

    cache.display();


    /*
        Insert key 4.

        Cache is full.

        Current:

            1 -> 3 -> 2

        2 is the Least Recently Used.

        Therefore:

            Remove 2

            Insert 4 at front

        Result:

            4 -> 1 -> 3
    */
    cache.put(4, 400);

    cache.display();


    /*
        key 2 was removed.

        Therefore get(2) returns -1.
    */
    cout << "get(2): "
         << cache.get(2)
         << endl;


    /*
        Access key 3.

        Current:

            4 -> 1 -> 3

        After get(3):

            3 -> 4 -> 1
    */
    cout << "get(3): "
         << cache.get(3)
         << endl;

    cache.display();


    /*
        Update key 1.

        Since key 1 already exists:

            - Update its value
            - Move it to the FRONT

        Before:

            3 -> 4 -> 1

        After:

            1 -> 3 -> 4
    */
    cache.put(1, 999);

    cache.display();


    return 0;
}


/*
===============================================================================
                           COMPLEXITY
===============================================================================

HASHMAP:

    Finding a key:
        Average O(1)

DOUBLY LINKED LIST:

    Insert at front:
        O(1)

    Remove from back:
        O(1)

    Remove a known node:
        O(1)

Therefore:

    get() → O(1) average
    put() → O(1) average

Space:

    O(capacity)


===============================================================================
                         INTERVIEW MEMORY TRICK
===============================================================================

Don't try to memorize the entire code.

Remember just this:

                HASHMAP
                   +
            DOUBLY LINKED LIST


HashMap:
    "Where is this key?"

Linked List:
    "Who is MRU and who is LRU?"


List:

    FRONT                         BACK
      ↓                             ↓
     MRU                           LRU


GET:

    Find using HashMap
          ↓
    Remove from list
          ↓
    Push to FRONT


PUT existing:

    Remove old node
          ↓
    Push updated node to FRONT


PUT new:

    If full → remove BACK
          ↓
    Push new node to FRONT


===============================================================================
                       MOST IMPORTANT INTERVIEW QUESTION
===============================================================================

Interviewer:

    "Why do you need BOTH a HashMap and a doubly linked list?"

Answer:

    "The HashMap gives O(1) average lookup by key, while the doubly
     linked list maintains the usage order and allows us to remove or
     move a known node in O(1). Together they give O(1) average get()
     and put()."


===============================================================================
                            COMMON MISTAKES
===============================================================================

1. Using only a HashMap

    Fast lookup, but finding the LRU item becomes difficult.


2. Using only a list

    Easy to maintain order, but searching for a key takes O(N).


3. Forgetting to update the HashMap iterator

    After moving a node, the old iterator is invalid.


4. Removing the FRONT when the cache is full

    WRONG.

    FRONT = MRU
    BACK  = LRU

    Always remove BACK.


5. Forgetting that get() changes the order

    get() is not just:

        return value

    It also makes that item MRU.


6. Forgetting that put() on an existing key changes its recency

    Updating an existing key also makes it MRU.


===============================================================================
                        FINAL MEMORY FORMULA
===============================================================================

                LRU CACHE

        HashMap + Doubly Linked List

        FRONT = MRU
        BACK  = LRU

        GET:
            find → remove → front

        PUT:
            existing → remove → front
            new/full → remove back → front

        Complexity:
            O(1) average
===============================================================================
*/
 
/*
===============================================================================
                  PACKET BUFFER / NETWORK QUEUE — CN + DSA
===============================================================================

PROBLEM:

Imagine a network device receiving packets faster than it can process them.

For example:

    Incoming packets:

        P1
        P2
        P3
        P4
        P5

The device cannot necessarily process everything immediately.

So it temporarily stores packets in a BUFFER.

The basic rule is:

        FIRST packet received
                 ↓
        FIRST packet processed

This is FIFO:

        First In → First Out


===============================================================================
                         REAL-WORLD EXAMPLE
===============================================================================

Suppose a router receives:

        Packet 1
        Packet 2
        Packet 3

They enter the buffer in that order:

        FRONT
          ↓
        [P1] [P2] [P3]
                    ↑
                   BACK


When the router processes a packet:

        P1 is removed first.

Then:

        [P2] [P3]


Then P2:

        [P3]


This is exactly what a QUEUE does.


===============================================================================
                              OPERATIONS
===============================================================================

We need:

    1. enqueue(packet)

        Add a packet to the BACK.

    2. dequeue()

        Remove the packet from the FRONT.

    3. peek()

        See which packet will be processed next.

    4. isEmpty()

        Check whether the buffer is empty.

    5. isFull()

        Check whether the buffer has reached its capacity.


===============================================================================
                         WHY A QUEUE?
===============================================================================

Because packets are normally processed in FIFO order.

Therefore:

        Network Packet Buffer
                 ↓
              Queue


The important mapping is:

        enqueue → packet arrives
        dequeue → packet gets processed


===============================================================================
                         THE BUFFER IS FINITE
===============================================================================

A real buffer cannot store infinite packets.

Suppose:

        Capacity = 3

Current buffer:

        [P1] [P2] [P3]

Now P4 arrives.

There are several possible policies:

    1. Drop the new packet
    2. Drop an existing packet
    3. Apply backpressure
    4. Use a different queueing policy


For this simple interview problem, we'll use:

        DROP the new packet when the buffer is full.


So:

        [P1] [P2] [P3]

        enqueue(P4)

        P4 is dropped.


===============================================================================
                      WHY CIRCULAR QUEUE?
===============================================================================

A normal array-based queue can waste space.

Suppose capacity = 5:

        [P1][P2][P3][P4][P5]
         ↑               ↑
       FRONT            BACK


Process P1 and P2:

        [ ][ ][P3][P4][P5]
             ↑       ↑
           FRONT    BACK


Now there is free space at the beginning.

But if BACK simply keeps moving right, we might incorrectly think
the array is full.

A CIRCULAR QUEUE solves this.

The indices wrap around:

        0 → 1 → 2 → 3 → 4
        ↑               ↓
        └───────────────┘


So after reaching index 4:

        next index = 0


This allows us to reuse freed spaces.


===============================================================================
                           DATA STRUCTURE
===============================================================================

We'll implement:

        vector<int> buffer

and maintain:

        front
        rear
        count
        capacity


Meaning:

        front → location of next packet to remove

        rear  → location where next packet will be inserted

        count → current number of packets

        capacity → maximum number of packets


===============================================================================
                              IMPORTANT
===============================================================================

We are deliberately using:

        count

instead of trying to determine full/empty only from front/rear.

Why?

Because in a circular queue:

        front == rear

can mean either:

        EMPTY

or:

        FULL

depending on the implementation.

Using count makes the logic extremely easy to remember.


===============================================================================
                         CIRCULAR QUEUE FORMULA
===============================================================================

When moving forward:

        index = (index + 1) % capacity


Example:

        capacity = 5

        index = 4

        next:

        (4 + 1) % 5
             = 0


This is the main trick behind circular queues.


===============================================================================
                              CODE
===============================================================================
*/

#include <iostream>
#include <vector>

using namespace std;


class PacketBuffer
{
private:

    /*
        Array used to store packets.

        Each integer represents a packet ID.
    */
    vector<int> buffer;


    /*
        Maximum number of packets the buffer can hold.
    */
    int capacity;


    /*
        Index of the FRONT.

        This points to the packet that will be processed next.
    */
    int front;


    /*
        Index where the NEXT packet will be inserted.
    */
    int rear;


    /*
        Number of packets currently in the buffer.
    */
    int count;


public:

    /*
        Constructor.
    */
    PacketBuffer(int capacity)
    {
        this->capacity = capacity;

        buffer.resize(capacity);

        front = 0;
        rear = 0;
        count = 0;
    }


    /*
        Check whether the buffer is empty.
    */
    bool isEmpty()
    {
        return count == 0;
    }


    /*
        Check whether the buffer is full.
    */
    bool isFull()
    {
        return count == capacity;
    }


    /*
        ENQUEUE

        A packet arrives.

        Add it at REAR.

        Example:

            [P1] [P2]

                     ↑
                    rear

        New packet P3 goes here.


        Time Complexity:

            O(1)
    */
    void enqueue(int packet)
    {
        /*
            If buffer is full, we cannot accept
            another packet.

            For this simple implementation,
            we DROP the new packet.
        */
        if (isFull())
        {
            cout << "Buffer full. Packet "
                 << packet
                 << " dropped."
                 << endl;

            return;
        }


        /*
            Store packet at the current rear position.
        */
        buffer[rear] = packet;


        /*
            Move rear forward.

            The % capacity makes the queue circular.
        */
        rear = (rear + 1) % capacity;


        /*
            One more packet is now stored.
        */
        count++;


        cout << "Packet "
             << packet
             << " added."
             << endl;
    }


    /*
        DEQUEUE

        Process/remove the packet at FRONT.

        Example:

            FRONT
              ↓
            [P1] [P2] [P3]

        P1 is removed.

        P2 becomes the next packet.


        Time Complexity:

            O(1)
    */
    int dequeue()
    {
        /*
            Nothing to remove.
        */
        if (isEmpty())
        {
            cout << "Buffer empty."
                 << endl;

            return -1;
        }


        /*
            Save the packet at FRONT.
        */
        int packet = buffer[front];


        /*
            Move FRONT forward.

            Again, modulo makes it circular.
        */
        front = (front + 1) % capacity;


        /*
            One packet has been removed.
        */
        count--;


        return packet;
    }


    /*
        PEEK

        Look at the next packet without removing it.

        Time Complexity:

            O(1)
    */
    int peek()
    {
        if (isEmpty())
        {
            return -1;
        }

        return buffer[front];
    }


    /*
        DISPLAY

        This is only for demonstration.

        We print packets from FRONT to BACK
        in their logical queue order.
    */
    void display()
    {
        if (isEmpty())
        {
            cout << "Buffer is empty."
                 << endl;

            return;
        }


        cout << "Buffer (FRONT -> BACK): ";


        /*
            Start at FRONT.

            Print exactly 'count' packets.

            This is important because the physical
            array may have wrapped around.
        */
        for (int i = 0; i < count; i++)
        {
            int index = (front + i) % capacity;

            cout << buffer[index] << " ";
        }

        cout << endl;
    }
};


/*
===============================================================================
                              DRIVER CODE
===============================================================================
*/

int main()
{
    /*
        Create a packet buffer with capacity 3.

            Maximum = 3 packets
    */
    PacketBuffer buffer(3);


    /*
        Three packets arrive.

            P1
            P2
            P3

        Buffer:

            [1] [2] [3]
             ↑
           FRONT
    */
    buffer.enqueue(1);
    buffer.enqueue(2);
    buffer.enqueue(3);

    buffer.display();


    /*
        Buffer is now full.

        Packet 4 arrives.

        Since our policy is:

            DROP NEW PACKET

        packet 4 will be dropped.
    */
    buffer.enqueue(4);


    /*
        Process the first packet.

        FIFO means:

            Packet 1 leaves first.
    */
    cout << "Processed packet: "
         << buffer.dequeue()
         << endl;

    buffer.display();


    /*
        Now there is one free position.

        Because this is a circular queue,
        the new packet can reuse that position.
    */
    buffer.enqueue(4);

    buffer.display();


    /*
        Process next packet.

        Packet 2 should leave.
    */
    cout << "Processed packet: "
         << buffer.dequeue()
         << endl;

    buffer.display();


    /*
        Peek at the next packet.

        Important:

            peek() does NOT remove the packet.
    */
    cout << "Next packet: "
         << buffer.peek()
         << endl;


    return 0;
}


/*
===============================================================================
                              DRY RUN
===============================================================================

Capacity = 3


Initially:

    buffer = [ ][ ][ ]

    front = 0
    rear  = 0
    count = 0


enqueue(1):

    [1][ ][ ]

    front = 0
    rear  = 1
    count = 1


enqueue(2):

    [1][2][ ]

    front = 0
    rear  = 2
    count = 2


enqueue(3):

    [1][2][3]

    front = 0
    rear  = 0

    Why rear = 0?

        (2 + 1) % 3
              = 0

    count = 3


The queue is FULL.


dequeue():

    Remove buffer[front]

    Remove 1.

    front:

        (0 + 1) % 3
              = 1

    count = 2


Logical queue:

    [2][3]


Now enqueue(4):

    rear is currently 0.

    Put 4 at index 0:

        [4][2][3]

    But logically the queue is:

        FRONT
          ↓
        [2][3][4]
             ↑
            BACK

The physical array order and logical queue order
are different.

This is exactly why we use:

        (index + 1) % capacity


===============================================================================
                            COMPLEXITY
===============================================================================

enqueue():

    O(1)


dequeue():

    O(1)


peek():

    O(1)


isEmpty():

    O(1)


isFull():

    O(1)


Space:

    O(capacity)


===============================================================================
                       INTERVIEW MEMORY TRICK
===============================================================================

Packet arrives:

        ENQUEUE
           ↓
         REAR


Packet gets processed:

        DEQUEUE
           ↓
         FRONT


Remember:

        enqueue → rear
        dequeue → front


For circular queue:

        next = (index + 1) % capacity


That's the only formula you really need to remember.


===============================================================================
                         CN → DSA MAPPING
===============================================================================

Networking concept:

        Packet Buffer

DSA concept:

        Queue


Networking:

        Packet arrives
              ↓
        enqueue()


Networking:

        Packet processed
              ↓
        dequeue()


Networking:

        Buffer has limited capacity
              ↓
        Queue can become FULL


Networking:

        Packets wait in FIFO order
              ↓
        Queue


===============================================================================
                         INTERVIEW FOLLOW-UPS
===============================================================================

Q1. Why use a queue for a packet buffer?

    Because a basic FIFO packet-processing policy processes
    packets in the order they arrive.


Q2. Why use a circular queue?

    To reuse the empty positions at the beginning of an
    array after elements have been removed.


Q3. What happens if the buffer is full?

    It depends on the system's queue-management policy.

    Possible approaches include:

        - Drop the new packet
        - Drop an existing packet
        - Backpressure
        - Priority-based dropping

    Our simple implementation drops the new packet.


Q4. Why not use a normal array?

    We can, but after dequeuing elements, space at the beginning
    may become unused.

    A circular queue allows us to reuse that space.


Q5. What happens to packets if they arrive faster than
   they can be processed?

    The queue grows until the buffer is full.

    After that, the system must apply some congestion/queue
    management policy such as packet dropping or backpressure.


Q6. Is a real network buffer always FIFO?

    No.

    Real systems can use more sophisticated queueing policies,
    including priority queues and fair queueing.

    FIFO is the simplest model.


===============================================================================
                            FINAL MEMORY
===============================================================================

                PACKET BUFFER

                    ↓

                  QUEUE

                    ↓

          ┌─────────────────┐
          │                 │
       ENQUEUE           DEQUEUE
          │                 │
        REAR              FRONT
          │                 │
      Packet enters    Packet leaves


        CIRCULAR QUEUE:

        next = (index + 1) % capacity


        Time:

        enqueue → O(1)
        dequeue → O(1)
        peek    → O(1)

===============================================================================
*/
 
/*
===============================================================================
                 ROUND-ROBIN LOAD BALANCER — CN + DSA
===============================================================================

PROBLEM:

Suppose we have multiple backend servers:

    Server 1
    Server 2
    Server 3

And clients send requests:

    Request 1
    Request 2
    Request 3
    Request 4
    Request 5
    ...

We don't want every request to go to the same server.

A LOAD BALANCER distributes incoming requests across multiple
backend servers.


===============================================================================
                         ROUND-ROBIN ALGORITHM
===============================================================================

The simplest load-balancing strategy is:

                    ROUND ROBIN

Requests are assigned sequentially.

Example:

    Servers:

        S1
        S2
        S3


    Requests:

        R1 → S1
        R2 → S2
        R3 → S3
        R4 → S1
        R5 → S2
        R6 → S3
        R7 → S1
        ...


The pattern is:

        S1 → S2 → S3 → S1 → S2 → S3 → ...


This is similar to a circular queue.


===============================================================================
                              WHY USE IT?
===============================================================================

Imagine one server handling everything:

        Requests
            |
            v
        Server 1

Server 1 can become overloaded.

Instead:

                    Load Balancer
                    /     |      \
                   /      |       \
                  v       v        v
                S1       S2       S3


The load is distributed.


===============================================================================
                         DSA CONNECTION
===============================================================================

We need:

    1. Store the list of servers.

        vector<string>

    2. Keep track of which server should receive
       the next request.

        int index

    3. After selecting a server, move to the next server.

        index = (index + 1) % number_of_servers


The same circular indexing idea appeared in our
Packet Buffer problem.


===============================================================================
                         CIRCULAR INDEXING
===============================================================================

Suppose:

    servers = 3


    index = 0
        → Server 1

    index = 1
        → Server 2

    index = 2
        → Server 3


Next:

    (2 + 1) % 3
          = 0


So we return to Server 1.


The important formula:

        index = (index + 1) % n


This gives:

        0 → 1 → 2 → 0 → 1 → 2 → ...


===============================================================================
                         SIMPLE ASSUMPTIONS
===============================================================================

For this basic implementation:

    - Every server has equal capacity.
    - Every server is healthy.
    - Every request has roughly similar cost.
    - We use simple round-robin distribution.


Real load balancers can be much more sophisticated.

They may use:

    - Weighted Round Robin
    - Least Connections
    - IP Hash
    - Consistent Hashing
    - Health Checks


We will discuss these after the basic implementation.


===============================================================================
                              CODE
===============================================================================
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class LoadBalancer
{
private:

    /*
        Stores the backend servers.

        Example:

            servers = {
                "Server-1",
                "Server-2",
                "Server-3"
            }
    */
    vector<string> servers;


    /*
        Index of the server that should receive
        the NEXT request.

        Initially:

            0 → Server-1
    */
    int nextServer;


public:

    /*
        Constructor.

        Store the list of backend servers.

        Initially the first server receives the first request.
    */
    LoadBalancer(vector<string> serverList)
    {
        servers = serverList;

        nextServer = 0;
    }


    /*
        GET NEXT SERVER

        Select the server that should handle the next request.

        Then move the index forward.

        Time Complexity:

            O(1)
    */
    string getNextServer()
    {
        /*
            Safety check.

            If there are no servers,
            no request can be handled.
        */
        if (servers.empty())
        {
            return "No server available";
        }


        /*
            Select the current server.
        */
        string selectedServer = servers[nextServer];


        /*
            Move to the next server.

            Example:

                0 → 1
                1 → 2
                2 → 0
        */
        nextServer =
            (nextServer + 1) % servers.size();


        /*
            Return the selected backend server.
        */
        return selectedServer;
    }


    /*
        DISPLAY SERVERS

        Only used for demonstration.
    */
    void displayServers()
    {
        cout << "Backend Servers: ";

        for (string server : servers)
        {
            cout << server << " ";
        }

        cout << endl;
    }
};


/*
===============================================================================
                              DRIVER CODE
===============================================================================
*/

int main()
{
    /*
        Create three backend servers.
    */
    vector<string> servers =
    {
        "Server-1",
        "Server-2",
        "Server-3"
    };


    /*
        Create the load balancer.
    */
    LoadBalancer lb(servers);


    lb.displayServers();


    /*
        Simulate incoming requests.

        We send 9 requests.

        Expected distribution:

            Request 1 → Server-1
            Request 2 → Server-2
            Request 3 → Server-3
            Request 4 → Server-1
            Request 5 → Server-2
            Request 6 → Server-3
            Request 7 → Server-1
            Request 8 → Server-2
            Request 9 → Server-3
    */

    for (int request = 1; request <= 9; request++)
    {
        string server = lb.getNextServer();

        cout << "Request "
             << request
             << " -> "
             << server
             << endl;
    }


    return 0;
}


/*
===============================================================================
                              DRY RUN
===============================================================================

Servers:

    S1
    S2
    S3


Initially:

    nextServer = 0


Request 1:

    selected = servers[0]

    → S1

    nextServer:

        (0 + 1) % 3
              = 1


Request 2:

    selected = servers[1]

    → S2

    nextServer:

        (1 + 1) % 3
              = 2


Request 3:

    selected = servers[2]

    → S3

    nextServer:

        (2 + 1) % 3
              = 0


Request 4:

    selected = servers[0]

    → S1


Therefore:

    S1 → S2 → S3 → S1 → S2 → S3 ...


===============================================================================
                              COMPLEXITY
===============================================================================

getNextServer():

    O(1)


Why?

We directly access:

    servers[nextServer]

No searching is required.


Space:

    O(N)

where N = number of backend servers.


===============================================================================
                    IMPORTANT INTERVIEW FOLLOW-UP #1
===============================================================================

INTERVIEWER:

    "What if the servers don't have equal capacity?"


Simple Round Robin assumes:

    S1 = S2 = S3


But imagine:

    S1 → powerful server
    S2 → medium server
    S3 → weak server


Sending equal traffic isn't ideal.


Solution:

    WEIGHTED ROUND ROBIN


Example:

    S1 → weight 3
    S2 → weight 2
    S3 → weight 1


Approximate distribution:

    S1 → 3 requests
    S2 → 2 requests
    S3 → 1 request


Then repeat.


===============================================================================
                    IMPORTANT INTERVIEW FOLLOW-UP #2
===============================================================================

INTERVIEWER:

    "What if one server goes down?"


Simple round-robin doesn't know.

Example:

    S1 → healthy
    S2 → DOWN
    S3 → healthy


Naive algorithm:

    S1 → S2 → S3 → S1 → S2 → S3

Some requests will be sent to S2 and fail.


Solution:

    HEALTH CHECKS


The load balancer periodically checks servers:

        S1 → healthy
        S2 → unhealthy
        S3 → healthy


Then temporarily remove S2 from the rotation:

        S1 → S3 → S1 → S3 ...


===============================================================================
                    IMPORTANT INTERVIEW FOLLOW-UP #3
===============================================================================

INTERVIEWER:

    "What if requests take very different amounts of time?"


Round Robin only considers:

    Number of requests


It doesn't know:

    How busy each server currently is.


Example:

    S1 → 100 active requests
    S2 → 2 active requests
    S3 → 10 active requests


Round Robin might still send the next request to S1.


A better algorithm could be:

    LEAST CONNECTIONS


Send the next request to the server with
the fewest active connections.


===============================================================================
                    IMPORTANT INTERVIEW FOLLOW-UP #4
===============================================================================

INTERVIEWER:

    "What is IP Hash?"


Use the client's IP address to determine
which server receives the request.

Conceptually:

        hash(clientIP) % numberOfServers


Example:

        Client IP
            |
            v
          Hash
            |
            v
        Server index


This can provide a degree of session affinity.

Meaning:

    The same client tends to reach the same server.


===============================================================================
                    IMPORTANT INTERVIEW FOLLOW-UP #5
===============================================================================

INTERVIEWER:

    "What is a load balancer actually doing?"


At a high level:

        Client
           |
           v
      Load Balancer
           |
      ┌────┼────┐
      v    v    v
     S1   S2   S3


It:

    1. Receives incoming traffic.
    2. Chooses an appropriate backend.
    3. Forwards the request.
    4. Returns/forwards the response appropriately.


Depending on its layer, it may make decisions using:

    Layer 4:
        IP
        Port
        TCP/UDP

    Layer 7:
        HTTP path
        Host
        Headers
        Cookies


===============================================================================
                      L4 vs L7 LOAD BALANCER
===============================================================================

LAYER 4:

        Client
           |
           v
        L4 LB
           |
           v
        Backend


The LB primarily works with:

        IP
        Port
        TCP
        UDP


LAYER 7:

        Client
           |
           v
        L7 LB
           |
        /api/*
           |
           v
       API Servers


The LB can understand:

        HTTP
        URL paths
        Headers
        Cookies


Example:

        /api/users
              ↓
        API Server

        /images
              ↓
        Image Server


===============================================================================
                         CN → DSA MAPPING
===============================================================================

NETWORKING CONCEPT:

        Load Balancer

              ↓

ALGORITHM:

        Round Robin

              ↓

DSA:

        Array / Vector
        +
        Circular Index


The key line:

        index = (index + 1) % n


===============================================================================
                         MEMORY TRICK
===============================================================================

Round Robin:

        Pick current server
                ↓
        Move to next server
                ↓
        Wrap around


        0 → 1 → 2 → 0 → 1 → 2 ...


Formula:

        (index + 1) % n


That's it.


===============================================================================
                         INTERVIEW ANSWER
===============================================================================

If asked:

    "Explain Round Robin load balancing."


Answer:

    "Round Robin distributes requests sequentially across the available
     backend servers. We maintain an index pointing to the next server,
     select that server, and increment the index modulo the number of
     servers. It is simple and provides O(1) selection, but it assumes
     servers have similar capacity and request workloads. In production,
     health checks, weighted round robin, least connections, or other
     strategies may be more appropriate."


===============================================================================
*/
/*
===============================================================================
                SHORTEST NETWORK PATH — DIJKSTRA'S ALGORITHM
===============================================================================

PROBLEM:

Imagine a computer network where routers are connected by links.

Each link has a "cost".

The cost could represent:

    - Latency
    - Distance
    - Network cost
    - Bandwidth-related metric
    - Administrative routing cost

Example:

        Router A
        /      \
      5          2
      /          \
 Router B ----1---- Router C

There are two ways to reach C from A:

    A → C

        Cost = 2


    A → B → C

        Cost = 5 + 1
              = 6


So the shortest path is:

        A → C

This is a WEIGHTED GRAPH problem.


===============================================================================
                    WHY NOT JUST USE BFS?
===============================================================================

BFS is excellent when every edge has the same cost.

Example:

        A -- B -- C -- D

Every connection has equal cost.

BFS finds:

        A → B → C → D


But consider:

        A --10-- B
        |        |
        1        1
        |        |
        C --1--- D


BFS primarily counts EDGES.

It might consider:

        A → B → D

and:

        A → C → D

both to have 2 edges.


But their actual costs are:

        A → B → D
        = 10 + 1
        = 11


        A → C → D
        = 1 + 1
        = 2


Therefore BFS is not enough.

We need an algorithm that considers the WEIGHT of each edge.

For graphs with NON-NEGATIVE edge weights:

                    DIJKSTRA


===============================================================================
                         CORE IDEA OF DIJKSTRA
===============================================================================

We maintain:

        dist[i]

which represents:

        Shortest known distance from the source
        to node i.


Initially:

        Source = 0

        Every other node = INFINITY


Example:

        A
       / \
      4   2
     /     \
    B       C


Starting from A:

        dist[A] = 0
        dist[B] = INF
        dist[C] = INF


We process A.

From A:

        B can be reached with cost 4.

        C can be reached with cost 2.


So:

        dist[B] = 4
        dist[C] = 2


Now we process the node with the smallest
known distance:

        C = 2


If C can improve some other node,
we update that distance.


This process continues until we find
the shortest paths.


===============================================================================
                         THE KEY OPERATION:
                             RELAXATION
===============================================================================

Suppose:

        A → B

and:

        dist[A] = 5

Edge:

        A --3--> B


Then going from source to B through A costs:

        dist[A] + edgeWeight

        = 5 + 3
        = 8


If:

        dist[B] > 8

we update:

        dist[B] = 8


This is called:

                    RELAXATION


The basic rule:

        if (dist[u] + weight < dist[v])

                dist[v] =
                    dist[u] + weight


This is THE most important line in Dijkstra.


===============================================================================
                        WHY A PRIORITY QUEUE?
===============================================================================

At every step, Dijkstra wants:

        The unprocessed node with the SMALLEST
        known distance.


Searching through all nodes every time would be slow.

So we use:

                    MIN-HEAP


In C++:

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;


We store:

        {distance, node}


Example:

        {2, C}
        {4, B}
        {7, D}


The priority queue gives us:

        {2, C}

first.


Therefore:

        Graph
          ↓
        Dijkstra
          ↓
        Priority Queue / Min Heap


===============================================================================
                              IMPORTANT
===============================================================================

Dijkstra works correctly when edge weights are:

                    NON-NEGATIVE


Example:

        A --(-5)-- B

Negative edges can break Dijkstra's greedy assumption.

For graphs containing negative edge weights,
other algorithms such as Bellman-Ford may be needed.


For your HPE SDE interview:

        Dijkstra → non-negative weights

is the important thing to remember.


===============================================================================
                        PROBLEM WE IMPLEMENT
===============================================================================

Given:

    N routers

    M network connections

    Each connection has a non-negative cost.

Find the shortest distance from a given
source router to every other router.


Example:

        0 --4-- 1
        |      / \
        2     1   5
        |   /     \
        2 --3------ 4


We want:

        Shortest path from router 0.


We'll use:

        Adjacency List
        +
        Min Heap


===============================================================================
                              CODE
===============================================================================
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


class Network
{
private:

    /*
        Each edge stores:

            destination node
            edge weight

        Example:

            adj[0] = {
                {1, 4},
                {2, 2}
            }

        means:

            0 → 1 with cost 4
            0 → 2 with cost 2
    */
    vector<vector<pair<int, int>>> adj;


public:

    /*
        Constructor.

        n = number of routers.
    */
    Network(int n)
    {
        adj.resize(n);
    }


    /*
        ADD EDGE

        We're treating the network as UNDIRECTED.

        So:

            addEdge(u, v, weight)

        creates:

            u → v
            v → u


        Example:

            addEdge(0, 1, 4)

        means:

            0 ----4---- 1
    */
    void addEdge(int u, int v, int weight)
    {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }


    /*
        DIJKSTRA

        Find the shortest distance from 'source'
        to every other router.


        Returns:

            vector<int>

        where:

            dist[i] = shortest distance from source to i.


        Time Complexity with adjacency list + binary min heap:

            O((V + E) log V)

        Commonly simplified to:

            O(E log V)

        for connected/sparse graph analysis.
    */
    vector<int> dijkstra(int source)
    {
        int n = adj.size();


        /*
            dist[i]:

                shortest known distance from source
                to node i.


            Initially:

                source = 0
                everything else = infinity
        */
        vector<int> dist(
            n,
            INT_MAX
        );


        /*
            MIN-HEAP.

            Each element:

                {distance, node}


            Example:

                {2, 3}

            means:

                Current known distance to node 3 = 2.
        */
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;


        /*
            Distance from source to itself is 0.
        */
        dist[source] = 0;


        /*
            Start Dijkstra from source.
        */
        pq.push({0, source});


        /*
            Continue while there are nodes
            waiting to be processed.
        */
        while (!pq.empty())
        {
            /*
                Get the node with the smallest
                known distance.

                pq.top() gives:

                    {distance, node}
            */
            auto current = pq.top();

            pq.pop();


            int currentDistance = current.first;

            int currentNode = current.second;


            /*
                IMPORTANT:

                We may have multiple entries for the
                same node in the priority queue.

                Example:

                    First:
                        node 3 with distance 10

                    Later:
                        node 3 with distance 5

                We don't need the old {10, 3} entry.

                If the distance stored in the queue is
                not equal to our current best distance,
                skip it.
            */
            if (currentDistance != dist[currentNode])
            {
                continue;
            }


            /*
                Explore every neighbour of currentNode.
            */
            for (auto edge : adj[currentNode])
            {
                int neighbour = edge.first;

                int weight = edge.second;


                /*
                    Calculate the distance to neighbour
                    if we travel through currentNode.

                        newDistance =
                            currentDistance + weight
                */
                int newDistance =
                    currentDistance + weight;


                /*
                    RELAXATION

                    If going through currentNode gives
                    us a shorter path:

                        update dist[neighbour]
                    */
                if (newDistance < dist[neighbour])
                {
                    /*
                        Found a better path.
                    */
                    dist[neighbour] = newDistance;


                    /*
                        Add the updated distance to
                        the priority queue.

                        The smallest distance will be
                        processed first.
                    */
                    pq.push({
                        newDistance,
                        neighbour
                    });
                }
            }
        }


        /*
            Return shortest distances.
        */
        return dist;
    }
};


/*
===============================================================================
                              DRIVER CODE
===============================================================================
*/

int main()
{
    /*
        Create a network with 5 routers:

            0
            1
            2
            3
            4
    */
    Network network(5);


    /*
        Create the following weighted network:

                4
            0 ------- 1
            |         |
          2 |         | 1
            |         |
            2 ------- 3
             \       /
              \ 5   /
               \   /
                 4


        Connections:

            0 --4-- 1
            0 --2-- 2
            1 --1-- 3
            2 --1-- 3
            3 --5-- 4
            1 --7-- 4


        Starting from 0.

        Possible paths to 3:

            0 → 1 → 3
              = 4 + 1
              = 5


            0 → 2 → 3
              = 2 + 1
              = 3


        Therefore shortest path to 3:

            0 → 2 → 3

        Cost:

            3
    */

    network.addEdge(0, 1, 4);
    network.addEdge(0, 2, 2);
    network.addEdge(1, 3, 1);
    network.addEdge(2, 3, 1);
    network.addEdge(3, 4, 5);
    network.addEdge(1, 4, 7);


    /*
        Run Dijkstra starting from router 0.
    */
    vector<int> distance =
        network.dijkstra(0);


    /*
        Display shortest distances.
    */
    cout << "Shortest distances from Router 0:\n";

    for (int i = 0; i < distance.size(); i++)
    {
        cout << "Router 0 -> Router "
             << i
             << " = "
             << distance[i]
             << endl;
    }


    return 0;
}


/*
/*
===============================================================================
                     RATE LIMITER — CN + DSA
===============================================================================

PROBLEM:

Suppose an API server receives requests:

    Client A
       |
       |--- Request
       |--- Request
       |--- Request
       |--- Request
       |--- Request
       v
    API Server


If one client sends too many requests too quickly, it can:

    - Overload the server
    - Consume too many resources
    - Affect other users
    - Potentially be used for abuse/DDoS-like traffic


A RATE LIMITER controls how many requests a client is
allowed to make within a certain period.


===============================================================================
                         SIMPLE REQUIREMENT
===============================================================================

Let's implement:

        "Allow at most 3 requests
         from a client within 10 seconds."


Example:

    Client A:

        t = 1
        t = 2
        t = 3

    These 3 requests are allowed.


    Fourth request:

        t = 4

    Only 3 requests are allowed in the last 10 seconds.

    Therefore:

        REJECT


===============================================================================
                       SLIDING WINDOW IDEA
===============================================================================

We'll use a simple SLIDING WINDOW.

For every client, maintain the timestamps
of their recent requests.

Example:

    Client A:

        [2, 5, 8]

Suppose:

        current time = 9
        window = 10 seconds


All three timestamps are still inside the
last 10 seconds.

If another request arrives:

        [2, 5, 8, 9]

We now have 4 requests.

If the limit is 3:

        REJECT


===============================================================================
                     WHY DO WE NEED A QUEUE?
===============================================================================

For each client, timestamps arrive in chronological order.

Example:

        2 → 5 → 8 → 9 → 12


The oldest timestamp is always at the FRONT.

The newest timestamp is always at the BACK.


Therefore:

        Queue / Deque


is a natural fit.


Example:

        FRONT                         BACK
          ↓                             ↓
        [2] [5] [8] [9]
         ↑                 ↑
       oldest            newest


When timestamps expire:

        Remove from FRONT.


When a new request arrives:

        Add to BACK.


This gives efficient removal of expired timestamps.


===============================================================================
                      WHY DO WE NEED A HASHMAP?
===============================================================================

We need a separate queue for EVERY client.

Example:

        Client A → [2, 5, 8]

        Client B → [1, 4]

        Client C → [3, 7, 9]


We need to quickly find the queue belonging
to a particular client.

Therefore:

        unordered_map


We can have:

        unordered_map<
            string,
            deque<int>
        >


Conceptually:

        client ID
             ↓
        request timestamps


===============================================================================
                       DATA STRUCTURE MAPPING
===============================================================================

                    RATE LIMITER

                         ↓

                    HashMap
                         +
                       Deque


HashMap:

    client → timestamps


Deque:

    timestamps ordered from oldest → newest


When request arrives:

        1. Find client's deque.
        2. Remove expired timestamps from FRONT.
        3. Check how many timestamps remain.
        4. If count >= limit:
               reject
           else:
               add current timestamp to BACK
               allow


===============================================================================
                         WHY DEQUE INSTEAD OF VECTOR?
===============================================================================

We frequently remove timestamps from the FRONT.

Vector:

        erase(begin())

would require shifting elements.

That can be O(N).


Deque:

        pop_front()

is O(1).


Therefore:

        Deque is a better fit.


===============================================================================
                        PROBLEM WE IMPLEMENT
===============================================================================

Rules:

        Maximum requests:
            3

        Time window:
            10 seconds


Function:

        allowRequest(client, timestamp)


Return:

        true
            → request allowed

        false
            → request rejected


Important assumption:

    Timestamps for a given client arrive in
    non-decreasing order.

This keeps the deque naturally ordered.


===============================================================================
                              CODE
===============================================================================
*/

#include <iostream>
#include <unordered_map>
#include <deque>
#include <string>

using namespace std;


class RateLimiter
{
private:

    /*
        Maximum number of requests allowed
        inside the time window.
    */
    int limit;


    /*
        Size of the sliding time window.

        Example:

            10 seconds
    */
    int window;


    /*
        For every client, store the timestamps
        of their recent requests.

        Example:

            "Alice" → [2, 5, 8]

            "Bob"   → [1, 4]


        HashMap gives approximately O(1)
        average lookup by client ID.
    */
    unordered_map<string, deque<int>> requests;


public:

    /*
        Constructor.
    */
    RateLimiter(int limit, int window)
    {
        this->limit = limit;
        this->window = window;
    }


    /*
===============================================================================
                         ALLOW REQUEST
===============================================================================

    Input:

        client
        currentTime


    Example:

        allowRequest("Alice", 15)


    Steps:

        1. Find Alice's timestamp deque.

        2. Remove timestamps that are outside
           the sliding window.

        3. Check whether Alice has already reached
           the request limit.

        4. If limit reached:
               reject request.

        5. Otherwise:
               add current timestamp
               allow request.


    Time Complexity:

        Amortized O(1)


    Why?

        Each timestamp is:

            inserted once

        and:

            removed at most once.


===============================================================================
    */
    bool allowRequest(
        string client,
        int currentTime
    )
    {
        /*
            Get the deque belonging to this client.

            If the client doesn't exist, unordered_map
            automatically creates an empty deque.
        */
        deque<int>& q = requests[client];


        /*
            Remove timestamps that are outside
            the sliding window.


            Suppose:

                currentTime = 20
                window = 10

            We care about requests from:

                time > 10

            So timestamps <= 10 are expired.


            Because timestamps are ordered, the oldest
            timestamp is always at the FRONT.
        */
        while (!q.empty() &&
               q.front() <= currentTime - window)
        {
            q.pop_front();
        }


        /*
            Now q contains only requests inside
            the current sliding window.


            If we already have 'limit' requests,
            reject the new request.
        */
        if (q.size() >= limit)
        {
            return false;
        }


        /*
            Request is allowed.

            Add its timestamp to the BACK.

            Newest timestamp always goes at the BACK.
        */
        q.push_back(currentTime);


        return true;
    }
};


/*
===============================================================================
                              DRIVER CODE
===============================================================================
*/

int main()
{
    /*
        Create a rate limiter:

            Maximum:
                3 requests

            Window:
                10 seconds
    */
    RateLimiter limiter(3, 10);


    /*
        Client A sends requests.

        t = 1

        Allowed.
    */
    cout << "A @ 1: "
         << (limiter.allowRequest("A", 1)
             ? "Allowed"
             : "Rejected")
         << endl;


    /*
        t = 2

        Allowed.
    */
    cout << "A @ 2: "
         << (limiter.allowRequest("A", 2)
             ? "Allowed"
             : "Rejected")
         << endl;


    /*
        t = 3

        Allowed.

        A has now made:

            3 requests

        inside the current window.
    */
    cout << "A @ 3: "
         << (limiter.allowRequest("A", 3)
             ? "Allowed"
             : "Rejected")
         << endl;


    /*
        t = 4

        Still inside the 10-second window.

        A already has:

            3 requests

        Therefore:

            REJECT
    */
    cout << "A @ 4: "
         << (limiter.allowRequest("A", 4)
             ? "Allowed"
             : "Rejected")
         << endl;


    /*
        t = 12

        Current window is approximately:

            (2, 12]

        Timestamp 1 and 2 are expired depending
        on the exact boundary definition.

        Our implementation removes timestamps <=:

            currentTime - window

            = 12 - 10
            = 2

        So timestamps 1 and 2 are removed.


        Remaining:

            [3]


        Therefore the request is allowed.
    */
    cout << "A @ 12: "
         << (limiter.allowRequest("A", 12)
             ? "Allowed"
             : "Rejected")
         << endl;


    /*
        Client B has its OWN independent rate limit.

        Client A's requests do not affect Client B.
    */
    cout << "B @ 1: "
         << (limiter.allowRequest("B", 1)
             ? "Allowed"
             : "Rejected")
         << endl;


    return 0;
}


/*
===============================================================================
                              DRY RUN
===============================================================================

Rules:

        Limit  = 3
        Window = 10 seconds


-------------------------------------------------------------------------------
REQUEST 1
-------------------------------------------------------------------------------

Client:

        A

Time:

        1


Current queue:

        []


No expired requests.

Count:

        0


0 < 3

Therefore:

        ALLOW


Queue:

        [1]


-------------------------------------------------------------------------------
REQUEST 2
-------------------------------------------------------------------------------

A @ 2


Queue:

        [1]


No expiration.

Count:

        1


1 < 3


ALLOW


Queue:

        [1, 2]


-------------------------------------------------------------------------------
REQUEST 3
-------------------------------------------------------------------------------

A @ 3


Queue:

        [1, 2]


Count:

        2


2 < 3


ALLOW


Queue:

        [1, 2, 3]


-------------------------------------------------------------------------------
REQUEST 4
-------------------------------------------------------------------------------

A @ 4


Queue:

        [1, 2, 3]


No timestamps have expired.


Count:

        3


3 >= 3


REJECT


Queue remains:

        [1, 2, 3]


-------------------------------------------------------------------------------
REQUEST 5
-------------------------------------------------------------------------------

A @ 12


Window:

        12 - 10
        = 2


Remove timestamps <= 2.


Remove:

        1
        2


Queue becomes:

        [3]


Count:

        1


1 < 3


ALLOW


Queue:

        [3, 12]


===============================================================================
                         WHY IS THIS A "SLIDING WINDOW"?
===============================================================================

The window moves with the current request.

At time 4:

        Relevant period:

            [ -6, 4 ]


At time 12:

        Relevant period:

            [ 2, 12 ]


At time 20:

        Relevant period:

            [ 10, 20 ]


The window continuously moves forward.

That's why it is called:

                    SLIDING WINDOW


===============================================================================
                     IMPORTANT INTERVIEW QUESTION #1
===============================================================================

Q:

    "Why use a HashMap?"


Answer:

    "Because we need a separate request history for each client.
     The HashMap maps a client ID to that client's timestamp deque,
     giving us O(1) average lookup."


===============================================================================
                     IMPORTANT INTERVIEW QUESTION #2
===============================================================================

Q:

    "Why use a deque?"


Answer:

    "Requests arrive chronologically, so the oldest timestamp is
     at the front and the newest is at the back. We frequently
     remove expired timestamps from the front and add new timestamps
     to the back, which deque supports in O(1)."


===============================================================================
                     IMPORTANT INTERVIEW QUESTION #3
===============================================================================

Q:

    "Why not use a vector?"


Answer:

    "We frequently remove expired timestamps from the front.
     Removing from the front of a vector requires shifting elements
     and can take O(N), whereas deque supports pop_front() in O(1)."


===============================================================================
                     IMPORTANT INTERVIEW QUESTION #4
===============================================================================

Q:

    "What is the complexity?"


Answer:

    HashMap lookup:

        O(1) average


    Removing expired timestamps:

        Each timestamp is inserted once and removed once,
        so the amortized cost per request is O(1).


    Therefore:

        O(1) amortized per request.


    Space:

        O(N)

    where N is the number of timestamps currently stored.


===============================================================================
                     IMPORTANT INTERVIEW QUESTION #5
===============================================================================

Q:

    "What happens if timestamps aren't ordered?"


Answer:

    "The simple deque approach assumes requests for a client arrive
     in non-decreasing timestamp order. If requests can arrive out
     of order, we'd need a different data structure or preprocessing
     strategy."


===============================================================================
                     IMPORTANT INTERVIEW QUESTION #6
===============================================================================

Q:

    "What is a fixed-window rate limiter?"


Example:

        Limit:

            3 requests per minute


Fixed windows might be:

        12:00:00 → 12:00:59
        12:01:00 → 12:01:59


A client could potentially send:

        3 requests at 12:00:59

and:

        3 requests at 12:01:00


That's 6 requests within approximately 2 seconds.


This is one weakness of a simple fixed-window approach.


The sliding-window approach gives a more precise
rolling limit.


===============================================================================
                     IMPORTANT INTERVIEW QUESTION #7
===============================================================================

Q:

    "What is a token bucket?"


Another popular rate-limiting algorithm.

Imagine a bucket that holds tokens.

Example:

        Bucket capacity = 5 tokens

Tokens are added at a fixed rate.

Each request consumes:

        1 token


If there are no tokens:

        REJECT


Token Bucket is useful because it can allow
controlled bursts while maintaining an average rate.


You don't need to implement it yet unless asked.


===============================================================================
                     IMPORTANT INTERVIEW QUESTION #8
===============================================================================

Q:

    "What if we have 10 million clients?"


A single in-memory HashMap may not be enough,
especially in a distributed system.


A production architecture might use:

        Multiple API servers
                ↓
          Shared rate-limit
             storage
                ↓
          Redis / distributed
             mechanism


The important system-design idea is:

    The rate-limit state must be consistently shared
    if requests for the same client can hit different servers.


===============================================================================
                     IMPORTANT INTERVIEW QUESTION #9
===============================================================================

Q:

    "Why can a local rate limiter be incorrect
     behind a load balancer?"


Suppose:

        Client A
           |
           v
       Load Balancer
        /        \
       /          \
    Server 1    Server 2


If each server independently allows:

        3 requests


Client A could effectively make:

        3 + 3 = 6 requests


even though the intended global limit was:

        3


Therefore distributed rate limiting requires
shared/coordinated state.


===============================================================================
                         CN → DSA MAPPING
===============================================================================

NETWORKING:

        API traffic

             ↓

NETWORKING:

        Rate limiting

             ↓

DSA:

        HashMap + Deque


HashMap:

        client → request history


Deque:

        oldest request → newest request


When request arrives:

        Remove expired
             ↓
        Check count
             ↓
        Allow / Reject
             ↓
        Add timestamp


===============================================================================
                         MEMORY TRICK
===============================================================================

Rate Limiter:

        WHO?
         ↓
      HashMap
         ↓
      client


        WHEN?
         ↓
       Deque
         ↓
    timestamps


Request:

        Remove old
             ↓
        Count remaining
             ↓
        limit reached?
          /       \
        YES       NO
         ↓         ↓
      REJECT     ALLOW
                    ↓
              push_back(time)


===============================================================================
                    ONE-LINE INTERVIEW ANSWER
===============================================================================

If asked:

    "How would you implement a simple per-user sliding-window
     rate limiter?"


Answer:

    "I'd maintain a HashMap from client ID to a deque of request
     timestamps. For each request I'd remove timestamps outside the
     sliding window, check whether the remaining count has reached
     the limit, and if not, append the new timestamp. This gives
     amortized O(1) processing per request."


===============================================================================
*//*
===============================================================================
                    FIREWALL RULES — CN + DSA
===============================================================================

PROBLEM:

A firewall controls which network traffic is allowed or blocked.

A simplified firewall might contain rules such as:

    10.0.0.0  - 10.0.0.100   → ALLOW
    10.0.0.101 - 10.0.0.200  → BLOCK
    192.168.1.0 - 192.168.1.50 → ALLOW


For this DSA problem, we'll simplify IP addresses into integers.

Example:

    IP range:

        10 → 20

    means:

        IPs 10, 11, 12, ..., 20


Our firewall contains BLOCKED IP ranges.

We need to answer:

    "Is this IP blocked?"


===============================================================================
                         EXAMPLE
===============================================================================

Blocked ranges:

        [10, 20]
        [30, 40]
        [50, 60]


Query:

        15

Result:

        BLOCKED


Query:

        25

Result:

        ALLOWED


Query:

        35

Result:

        BLOCKED


===============================================================================
                         WHY IS THIS AN INTERVAL PROBLEM?
===============================================================================

Each firewall rule can be represented as:

        [start, end]


Example:

        Block 10 to 20

becomes:

        [10, 20]


So the firewall rules are simply:

        intervals


This is a very common DSA pattern.

Whenever you see:

    - IP ranges
    - Time ranges
    - Memory ranges
    - Port ranges
    - Coordinate ranges

you should consider:

        INTERVALS


===============================================================================
                     PROBLEM WE WILL SOLVE
===============================================================================

Implement a simple firewall.

Operations:

    1. addBlockedRange(start, end)

    2. isBlocked(ip)

Example:

    addBlockedRange(10, 20)
    addBlockedRange(30, 40)

    isBlocked(15)
        → true

    isBlocked(25)
        → false


===============================================================================
                         FIRST SIMPLE SOLUTION
===============================================================================

We could simply store every range:

        [10,20]
        [30,40]
        [50,60]


For every IP query:

        Check every interval.


If there are N ranges:

        Query = O(N)


This is acceptable for a simple implementation.

But we can improve it.


===============================================================================
                     MERGE OVERLAPPING RANGES
===============================================================================

Suppose the firewall has:

        [10,20]
        [15,30]
        [25,40]


These ranges overlap.

Together they cover:

        [10,40]


So we can merge them.

Instead of storing:

        [10,20]
        [15,30]
        [25,40]


we store:

        [10,40]


This reduces redundant intervals.


===============================================================================
                         SORTING FIRST
===============================================================================

Suppose we have:

        [30,40]
        [10,20]
        [15,25]


Sort by starting point:

        [10,20]
        [15,25]
        [30,40]


Now merging becomes easy.


If:

        current.start <= previous.end


then the intervals overlap.

Merge:

        previous.end =
            max(previous.end, current.end)


Example:

        [10,20]
        [15,25]


Because:

        15 <= 20


merge into:

        [10,25]


===============================================================================
                     AFTER MERGING
===============================================================================

Suppose:

        [10,20]
        [15,25]
        [30,40]
        [35,50]


After merging:

        [10,25]
        [30,50]


Now checking an IP is easier.


===============================================================================
                      BINARY SEARCH FOR IP
===============================================================================

Once the intervals are sorted and non-overlapping:

        [10,25]
        [30,50]
        [70,90]


Suppose query:

        40


We can use binary search to find whether
40 belongs to one of the intervals.


This gives:

        O(log N)


query time.


===============================================================================
                    DATA STRUCTURES
===============================================================================

We'll use:

        vector<pair<int,int>>


Each pair:

        {start, end}


Example:

        {
            {10, 20},
            {30, 40}
        }


Then:

        sort()

and:

        merge()


Finally:

        binary search


===============================================================================
                              CODE
===============================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Firewall
{
private:

    /*
        Stores blocked IP ranges.

        Each pair is:

            {startIP, endIP}
    */
    vector<pair<int, int>> ranges;


public:

    /*
===============================================================================
                         ADD BLOCKED RANGE
===============================================================================

    Add a new blocked interval.

    Example:

        addBlockedRange(10, 20)

    stores:

        [10,20]


    We don't immediately merge here.

    We'll merge all ranges after all rules are added.


    Time:

        O(1) amortized for insertion into vector

        (Ignoring vector resizing details.)
===============================================================================
    */
    void addBlockedRange(int start, int end)
    {
        ranges.push_back({start, end});
    }


    /*
===============================================================================
                              MERGE RANGES
===============================================================================

    Steps:

        1. Sort ranges by start.

        2. Traverse them.

        3. If current range overlaps previous range,
           merge them.

        4. Otherwise start a new interval.


    Example:

        [10,20]
        [15,30]

        overlap

        ↓

        [10,30]


    Time:

        O(N log N)

    because sorting dominates.


    Space:

        O(N)
===============================================================================
    */
    void mergeRanges()
    {
        /*
            Nothing to merge.
        */
        if (ranges.empty())
        {
            return;
        }


        /*
            Sort by:

                start first

            and then:

                end
        */
        sort(
            ranges.begin(),
            ranges.end()
        );


        /*
            This will contain the merged ranges.
        */
        vector<pair<int, int>> merged;


        /*
            Start with the first interval.
        */
        merged.push_back(ranges[0]);


        /*
            Process remaining intervals.
        */
        for (int i = 1; i < ranges.size(); i++)
        {
            /*
                Reference the last merged interval.

                Example:

                    [10,20]

                current:

                    [15,30]
            */
            pair<int, int>& last =
                merged.back();


            pair<int, int> current =
                ranges[i];


            /*
                Check for overlap.

                Example:

                    last    = [10,20]
                    current = [15,30]

                    current.first = 15
                    last.second   = 20

                    15 <= 20

                Therefore they overlap.
            */
            if (current.first <= last.second)
            {
                /*
                    Extend the ending point if necessary.

                    [10,20]
                    [15,30]

                    becomes:

                    [10,30]
                */
                last.second =
                    max(
                        last.second,
                        current.second
                    );
            }
            else
            {
                /*
                    No overlap.

                    Example:

                        [10,20]
                        [30,40]

                    Keep both separately.
                */
                merged.push_back(current);
            }
        }


        /*
            Replace original ranges
            with merged ranges.
        */
        ranges = merged;
    }


    /*
===============================================================================
                              IS BLOCKED?
===============================================================================

    Determine whether an IP belongs to any blocked range.

    Because ranges are:

        - sorted
        - non-overlapping


    we can use binary search.


    For an interval:

        [start, end]


    An IP is inside it when:

        start <= ip <= end


    We use binary search to find the interval
    whose start is the closest start <= ip.


    Time:

        O(log N)
===============================================================================
    */
    bool isBlocked(int ip)
    {
        /*
            Binary search manually.

            We want the LAST interval whose:

                start <= ip
        */
        int left = 0;

        int right = ranges.size() - 1;


        /*
            Stores the candidate interval.
        */
        int candidate = -1;


        while (left <= right)
        {
            int mid =
                left + (right - left) / 2;


            /*
                If this interval starts before or
                exactly at the IP, it could contain it.
            */
            if (ranges[mid].first <= ip)
            {
                candidate = mid;

                /*
                    Try to find an even later interval
                    whose start is still <= ip.
                */
                left = mid + 1;
            }
            else
            {
                /*
                    This interval starts too late.

                    Search left.
                */
                right = mid - 1;
            }
        }


        /*
            No interval starts before the IP.

            Therefore IP cannot be blocked.
        */
        if (candidate == -1)
        {
            return false;
        }


        /*
            Check whether the IP falls inside
            the candidate interval.
        */
        return ip <= ranges[candidate].second;
    }


    /*
        Display the merged firewall rules.
    */
    void display()
    {
        cout << "\nBlocked ranges:\n";

        for (auto range : ranges)
        {
            cout << "[" << range.first
                 << ", "
                 << range.second
                 << "]"
                 << endl;
        }
    }
};


/*
===============================================================================
                              DRIVER CODE
===============================================================================
*/

int main()
{
    Firewall firewall;


    /*
        Add firewall rules.

        We intentionally add overlapping ranges
        in an unsorted order.
    */

    firewall.addBlockedRange(30, 40);

    firewall.addBlockedRange(10, 20);

    firewall.addBlockedRange(15, 25);

    firewall.addBlockedRange(50, 60);

    firewall.addBlockedRange(55, 70);


    /*
        Merge overlapping ranges.

        Before:

            [30,40]
            [10,20]
            [15,25]
            [50,60]
            [55,70]


        After sorting:

            [10,20]
            [15,25]
            [30,40]
            [50,60]
            [55,70]


        After merging:

            [10,25]
            [30,40]
            [50,70]
    */
    firewall.mergeRanges();


    firewall.display();


    /*
        Test IP = 15.

        15 belongs to:

            [10,25]

        Therefore:

            BLOCKED
    */
    cout << "\nIP 15: "
         << (firewall.isBlocked(15)
             ? "BLOCKED"
             : "ALLOWED")
         << endl;


    /*
        Test IP = 27.

        27 belongs to no blocked range.

        Therefore:

            ALLOWED
    */
    cout << "IP 27: "
         << (firewall.isBlocked(27)
             ? "BLOCKED"
             : "ALLOWED")
         << endl;


    /*
        Test IP = 35.

        35 belongs to:

            [30,40]

        Therefore:

            BLOCKED
    */
    cout << "IP 35: "
         << (firewall.isBlocked(35)
             ? "BLOCKED"
             : "ALLOWED")
         << endl;


    /*
        Test IP = 65.

        65 belongs to:

            [50,70]

        Therefore:

            BLOCKED
    */
    cout << "IP 65: "
         << (firewall.isBlocked(65)
             ? "BLOCKED"
             : "ALLOWED")
         << endl;


    /*
        Test IP = 80.

        No blocked interval contains 80.

        Therefore:

            ALLOWED
    */
    cout << "IP 80: "
         << (firewall.isBlocked(80)
             ? "BLOCKED"
             : "ALLOWED")
         << endl;


    return 0;
}


/*
===============================================================================
                              DRY RUN
===============================================================================

Initial firewall rules:

        [30,40]
        [10,20]
        [15,25]
        [50,60]
        [55,70]


-------------------------------------------------------------------------------
STEP 1 — SORT
-------------------------------------------------------------------------------

After sorting by start:

        [10,20]
        [15,25]
        [30,40]
        [50,60]
        [55,70]


-------------------------------------------------------------------------------
STEP 2 — MERGE
-------------------------------------------------------------------------------

Start:

        [10,20]


Next:

        [15,25]


Check:

        15 <= 20

Yes.

Overlap.

Merge:

        [10,25]


Next:

        [30,40]


Check:

        30 <= 25

No.

Keep separately:

        [10,25]
        [30,40]


Next:

        [50,60]


Check:

        50 <= 40

No.

Keep separately:

        [10,25]
        [30,40]
        [50,60]


Next:

        [55,70]


Check:

        55 <= 60

Yes.

Merge:

        [50,70]


Final:

        [10,25]
        [30,40]
        [50,70]


===============================================================================
                          QUERY: IP = 35
===============================================================================

Intervals:

        [10,25]
        [30,40]
        [50,70]


Binary search.


We want the last interval whose:

        start <= 35


Check:

        [30,40]

Its start:

        30 <= 35

So it is a candidate.


Could there be a later interval?

        [50,70]

50 > 35

No.


Candidate:

        [30,40]


Check:

        30 <= 35 <= 40


True.


Therefore:

        35 = BLOCKED


===============================================================================
                          QUERY: IP = 27
===============================================================================

Intervals:

        [10,25]
        [30,40]
        [50,70]


Find last interval with:

        start <= 27


Candidate:

        [10,25]


Check:

        27 <= 25


False.


Therefore:

        27 = ALLOWED


===============================================================================
                       WHY MERGING HELPS
===============================================================================

Without merging:

        [10,20]
        [15,25]
        [18,30]
        [25,40]


We have many overlapping rules.


After merging:

        [10,40]


Now we have a single interval.


Benefits:

        - Less redundant data
        - Faster searching
        - Simpler representation


===============================================================================
                    IMPORTANT INTERVIEW QUESTION #1
===============================================================================

Q:

    "Why sort the firewall rules?"


Answer:

    "Sorting by the starting IP lets us process intervals in order,
     which makes detecting and merging overlapping ranges simple."


===============================================================================
                    IMPORTANT INTERVIEW QUESTION #2
===============================================================================

Q:

    "What is the complexity of merging intervals?"


Answer:

        Sorting:
            O(N log N)

        Merge traversal:
            O(N)

        Overall:
            O(N log N)


===============================================================================
                    IMPORTANT INTERVIEW QUESTION #3
===============================================================================

Q:

    "What is the complexity of checking an IP?"


After merging and sorting:

        Binary Search

Therefore:

        O(log N)


Without binary search, scanning every interval would be:

        O(N)


===============================================================================
                    IMPORTANT INTERVIEW QUESTION #4
===============================================================================

Q:

    "Why not just check every range?"


Answer:

    "We can, and that would be simpler with O(N) lookup. But if the
     firewall has many rules and receives many queries, sorting and
     merging the ranges lets us answer each query using binary search
     in O(log N)."


===============================================================================
                    IMPORTANT INTERVIEW QUESTION #5
===============================================================================

Q:

    "What if two intervals only touch?"

Example:

        [10,20]
        [21,30]


With integer IPs, these do NOT overlap because:

        21 > 20


So they remain separate.


If we instead had:

        [10,20]
        [20,30]


They overlap at 20.

Our condition:

        current.start <= last.end

merges them.


===============================================================================
                    IMPORTANT INTERVIEW QUESTION #6
===============================================================================

Q:

    "What if the firewall supports ALLOW and BLOCK rules?"


Now things become more interesting.

For example:

        BLOCK 10-100

        ALLOW 50-60


Now the answer depends on the firewall's rule semantics.

Possible policies include:

        - First matching rule wins
        - Last matching rule wins
        - Explicit priority
        - Allow overrides block
        - Block overrides allow


This is important:

    Don't blindly apply interval merging when rules have
    different actions or priorities.

The simple interval solution assumes ALL stored ranges
represent the same action:

        BLOCK.


===============================================================================
                    IMPORTANT INTERVIEW QUESTION #7
===============================================================================

Q:

    "Can this represent ports as well?"


Yes.

Instead of:

        IP range

we could have:

        Port range


Example:

        [20,21]    → FTP
        [80,80]    → HTTP
        [443,443]  → HTTPS


The same interval concepts can apply.


===============================================================================
                    IMPORTANT INTERVIEW QUESTION #8
===============================================================================

Q:

    "Can this be used for IPv4 addresses?"


Yes, conceptually.

But our implementation represents IP addresses
as integers for simplicity.


Real IPv4 addresses are:

        32-bit values


For example:

        192.168.1.10


can be converted into a 32-bit integer.

Then ranges can be represented as:

        [startIP, endIP]


The DSA logic remains:

        sort
        merge
        binary search


===============================================================================
                         CN → DSA MAPPING
===============================================================================

NETWORKING:

        Firewall

             ↓

NETWORKING:

        IP rules / IP ranges

             ↓

DSA:

        Intervals


NETWORKING:

        Overlapping firewall ranges

             ↓

DSA:

        Merge Intervals


NETWORKING:

        Many IP queries

             ↓

DSA:

        Binary Search


NETWORKING:

        Sorted blocked ranges

             ↓

DSA:

        Vector + Sorting


===============================================================================
                         MEMORY TRICK
===============================================================================

When you hear:

        "IP range"

think:

        INTERVAL


When you hear:

        "overlapping ranges"

think:

        SORT + MERGE


When you hear:

        "many queries after preprocessing"

think:

        BINARY SEARCH


So:

        Firewall
            ↓
        IP ranges
            ↓
        Intervals
            ↓
        Sort + Merge
            ↓
        Binary Search


===============================================================================
                         INTERVIEW ANSWER
===============================================================================

If asked:

    "How would you efficiently check whether an IP belongs to a
     large set of blocked IP ranges?"


Answer:

    "I'd represent each blocked range as an interval. I'd sort the
     intervals by their start address and merge overlapping ranges.
     Then, because the resulting ranges are sorted and non-overlapping,
     I can use binary search to determine whether an IP belongs to a
     blocked interval. Preprocessing takes O(N log N), and each lookup
     takes O(log N)."


===============================================================================
*/