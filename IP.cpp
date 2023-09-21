#include <iostream>
#include <cstdlib>
#include <cstring>
#include <winsock2.h>
#include <iphlpapi.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

int main() {
    // Initialize the Windows Sockets API
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return 1;
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        std::cerr << "Error getting hostname" << std::endl;
        WSACleanup();  // Clean up Winsock
        return 1;
    }

    std::cout << "Hostname: " << hostname << std::endl;

    // Get the local IP address
    struct hostent *host_entry = gethostbyname(hostname);

    if (host_entry == nullptr || host_entry->h_addr_list[0] == nullptr) {
        std::cerr << "Error getting IP address" << std::endl;
        WSACleanup();  // Clean up Winsock
        return 1;
    }

    char *IPbuffer = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0]));
    std::cout << "Your IP address is: " << IPbuffer << std::endl;

    WSACleanup();  // Clean up Winsock
    return 0;
}
