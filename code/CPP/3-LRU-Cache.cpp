/*
Implement an LRU (Least Recently Used) Cache.

Real-world examples:
- Browser Cache
- DNS Cache
- Proxy Cache

Suppose the cache capacity is 3.

Cache:

Google
YouTube
GitHub

Now user visits:

Google

Google becomes "Most Recently Used".

Now user visits:

LeetCode

Cache is full.

We remove the Least Recently Used page.

Result:

Google
GitHub
LeetCode

YouTube is removed because it was not used recently.

Operations:

1. get(key)
    If present:
        Return value.
        Move item to front (Most Recently Used).

    Else:
        Return -1.

2. put(key,value)

    If key exists:
        Update value.
        Move to front.

    Else:

        If cache is full:
            Remove Least Recently Used item.

        Insert new item at front.

Target:

Both get() and put() should be O(1).
*/
#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache
{
private:
    int capacity;

    list<pair<int,int>> dll;

    unordered_map<int, list<pair<int,int>>::iterator> mp;

public:

    LRUCache(int cap)
    {
        capacity = cap;
    }

    int get(int key)
    {
        if(mp.find(key) == mp.end())
            return -1;

        auto node = *(mp[key]);

        dll.erase(mp[key]);

        dll.push_front(node);

        mp[key] = dll.begin();

        return node.second;
    }

    void put(int key,int value)
    {
        if(mp.find(key) != mp.end())
        {
            dll.erase(mp[key]);
        }

        else if(dll.size() == capacity)
        {
            auto last = dll.back();

            mp.erase(last.first);

            dll.pop_back();
        }

        dll.push_front({key,value});

        mp[key] = dll.begin();
    }

    void display()
    {
        cout << "Cache : ";

        for(auto it : dll)
            cout << "(" << it.first << "," << it.second << ") ";

        cout << endl;
    }
};

int main()
{
    LRUCache cache(3);

    cache.put(1,10);
    cache.display();

    cache.put(2,20);
    cache.display();

    cache.put(3,30);
    cache.display();

    cout << "\nAccess Key 2\n";
    cout << cache.get(2) << endl;
    cache.display();

    cout << "\nInsert Key 4\n";
    cache.put(4,40);
    cache.display();

    cout << "\nGet Key 1 : ";
    cout << cache.get(1) << endl;

    cout << "Get Key 3 : ";
    cout << cache.get(3) << endl;

    cache.display();
}