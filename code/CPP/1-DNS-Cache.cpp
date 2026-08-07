/*
Implement a simple DNS Cache.

A DNS cache stores:

Domain Name  --->  IP Address

Example:
google.com  --->  142.250.183.206

Each entry also has a TTL (Time To Live).

TTL tells us how long the entry is valid.

Suppose:

google.com
IP = 142.250.183.206
TTL = 10 seconds

Inserted at time = 100

Expiry time = 110

If someone asks for google.com at:

time = 105
Return the IP.

time = 115
Return "Not Found" because TTL expired.

Operations:

1. put(domain, ip, ttl, currentTime)
   Insert/Update DNS entry.

2. get(domain, currentTime)
   Return IP if present and not expired.
   Otherwise return "Not Found".

Use HashMap for O(1) lookup.
*/


#include <iostream>
#include <unordered_map>
using namespace std;

struct DNSRecord
{
    string ip;
    int expiryTime;
};

class DNSCache
{
private:
    unordered_map<string, DNSRecord> cache;

public:

    // Insert or update a DNS entry
    void put(string domain, string ip, int ttl, int currentTime)
    {
        cache[domain] = {ip, currentTime + ttl};
    }

    // Get IP if entry exists and has not expired
    string get(string domain, int currentTime)
    {
        // Domain doesn't exist
        if (cache.find(domain) == cache.end())
            return "Not Found";

        // TTL expired
        if (currentTime > cache[domain].expiryTime)
        {
            cache.erase(domain);          // Remove expired entry
            return "Not Found";
        }

        return cache[domain].ip;
    }
};
int main()
{
    DNSCache dns;

    dns.put("google.com", "142.250.183.206", 10, 100);

    cout << dns.get("google.com", 105) << endl;

    cout << dns.get("google.com", 111) << endl;

    return 0;
}