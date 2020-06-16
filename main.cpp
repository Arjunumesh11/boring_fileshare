#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "chunkencoding.h"
#include "http_header.h"

#define PORT 3000
#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;

    int addrlen = sizeof(address);
    char buffer_recv[1024] = {0};
    int opt = 1, file_size;

    std::string header;
    std::string file_name;
    std::vector<char> content;
    std::vector<char> buffer(BUFFER_SIZE);

    file_name = "./test_input/text.txt";

    std::ifstream file(file_name.c_str(), std::ios::binary);
    if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        file_size = file.tellg();
        file.seekg(0, std::ios::beg);
    }
    else
    {
        perror("file not found");
        exit(0);
    }
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    header = http_header::make_header(file_name, file_size);
    valread = recv(new_socket, buffer_recv, 1024, 0);
    printf("%s\n", buffer_recv);

    write(new_socket, header.c_str(), header.length());

    std::streamsize s;
    while (file.read(&buffer[0], 1024))
    {
        s = file.gcount();
        content = chunk::make_chunk(buffer, s);
        write(new_socket, &content[0], content.size());
    }

    s = file.gcount();
    content = chunk::make_chunk(buffer, s);
    if (!content.empty())
    {
        write(new_socket, &content[0], content.size());
    }

    write(new_socket, chunk::END.c_str(), chunk::END.length());
    return 0;
}