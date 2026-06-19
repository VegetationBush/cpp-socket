#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Waiting for connection...\n";

    int addrlen = sizeof(address);
    int client_socket = accept(server_fd, (sockaddr*)&address, (socklen_t*)&addrlen);

    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    std::cout << "Client says: " << buffer << std::endl;

    const char* reply = "Hello from server";
    send(client_socket, reply, strlen(reply), 0);

    close(client_socket);
    close(server_fd);

    return 0;
}