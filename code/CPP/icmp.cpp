#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <sys/time.h>

using namespace std;

// Standard algorithm to calculate the ICMP checksum
unsigned short calculate_checksum(unsigned short *ptr, int nbytes) {
    long sum = 0;
    unsigned short oddbyte;
    short answer;

    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char*)&oddbyte) = *(u_char*)ptr;
        sum += oddbyte;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum = sum + (sum >> 16);
    answer = (short)~sum;
    return answer;
}

int main() {
    string target_ip;
    cout << "Enter IP address to ping: ";
    cin >> target_ip;

    // Create a raw socket for ICMP
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        cerr << "Error: Cannot create socket. Did you run with sudo?" << endl;
        return 1;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, target_ip.c_str(), &dest_addr.sin_addr);

    int pid = getpid() & 0xFFFF;
    char packet[64];
    char recv_buffer[1024];

    // Set a timeout for receiving packets
    struct timeval tv_out;
    tv_out.tv_sec = 2;
    tv_out.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out));

    cout << "\nPinging " << target_ip << " with custom C++ script:\n\n";

    for (int seq = 1; seq <= 4; seq++) {
        memset(packet, 0, sizeof(packet));

        // Construct the ICMP Header
        struct icmphdr *icmp = (struct icmphdr *)packet;
        icmp->type = ICMP_ECHO;
        icmp->code = 0;
        icmp->un.echo.id = pid;
        icmp->un.echo.sequence = seq; // Assigning sequence number
        icmp->checksum = 0;

        // Add some dummy payload data
        const char* data = "Hello_Server_Ping_Req";
        strcpy(packet + sizeof(struct icmphdr), data);

        int packet_size = sizeof(struct icmphdr) + strlen(data);
        icmp->checksum = calculate_checksum((unsigned short *)packet, packet_size);

        struct timeval start, end;
        gettimeofday(&start, NULL);

        // Send the packet
        if (sendto(sockfd, packet, packet_size, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) <= 0) {
            cerr << "Packet send failed!" << endl;
            continue;
        }

        // Receive the reply
        socklen_t addr_len = sizeof(dest_addr);
        if (recvfrom(sockfd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr*)&dest_addr, &addr_len) <= 0) {
            cout << "Request timed out for seq=" << seq << endl;
        } else {
            gettimeofday(&end, NULL);
            
            // The received buffer starts with the IP header
            struct iphdr *ip_reply = (struct iphdr*)recv_buffer;
            
            // Extract TTL directly from the IP header
            int ttl = ip_reply->ttl;
            
            // Calculate RTT
            double rtt = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            
            cout << "Reply from " << inet_ntoa(dest_addr.sin_addr) 
                 << ": seq=" << seq << " time=" << rtt << "ms TTL=" << ttl << endl;
        }
        sleep(1);
    }

    close(sockfd);
    return 0;
}