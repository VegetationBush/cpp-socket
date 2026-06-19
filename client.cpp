#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr));

    const char* message = "Hello server!";
    send(sock, message, strlen(message), 0);

    char buffer[1024] = {0};
    read(sock, buffer, 1024);

    std::cout << "Server says: " << buffer << std::endl;

    close(sock);
    return 0;
}