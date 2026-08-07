/*
Implement a Network Packet Buffer.

Imagine a router receiving packets from the internet.

Packets arrive in this order:

Packet 1
Packet 2
Packet 3
Packet 4

The router processes packets one by one.

Since the first packet that arrives should be processed first,
we use a Queue (FIFO).

Operations:

1. receivePacket(packet)
   Add packet to buffer.

2. processPacket()
   Remove and process oldest packet.

3. frontPacket()
   View next packet to be processed.

4. isEmpty()
   Check whether buffer is empty.

This is exactly how a queue works.

FIFO

First In
First Out
*/

#include <iostream>
#include <queue>
using namespace std;

class PacketBuffer
{
private:

    queue<string> buffer;

public:

    // Add packet into buffer
    void receivePacket(string packet)
    {
        buffer.push(packet);
    }

    // Process oldest packet
    void processPacket()
    {
        if(buffer.empty())
        {
            cout << "Buffer Empty\n";
            return;
        }

        cout << "Processing : "
             << buffer.front()
             << endl;

        buffer.pop();
    }

    // Show next packet
    string frontPacket()
    {
        if(buffer.empty())
            return "Buffer Empty";

        return buffer.front();
    }

    bool isEmpty()
    {
        return buffer.empty();
    }
};

int main()
{
    PacketBuffer router;

    router.receivePacket("Packet A");
    router.receivePacket("Packet B");
    router.receivePacket("Packet C");

    router.processPacket();

    cout << router.frontPacket() << endl;

    router.processPacket();

    router.processPacket();

    router.processPacket();

    return 0;
}
