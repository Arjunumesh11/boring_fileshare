#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fstream>
#include <thread>
#include <errno.h>
#include "http_header.h"
#include "chunkencoding.h"

#define PORT 3000
#define SERVER_BACKLOG 10
#define THREAD_POOL_SIZE 10

void check(int status, std::string error) //function to check error
{
    if (status == -1)
    {
        fprintf(stderr, "%s : %i\n", error.c_str(), errno);
        exit(EXIT_FAILURE);
    }
}
void handle_connection(int new_socket)
{
    int file_size;
    std::vector<char> content;
    std::string header;
    std::string file_name;
    std::vector<char> buffer(1024);
    std::streamsize s;

    file_name = "./test_input/video.mp4";

    std::ifstream file(file_name.c_str(), std::ios::binary);
    if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        file_size = file.tellg();
        file.seekg(0, std::ios::beg);
    }
    else
    {
        perror("file not found ");
        exit(0);
    }

    header = http_header::make_header(file_name, file_size);

    write(new_socket, header.c_str(), header.length());

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
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    char buffer_recv[1024] = {0};
    std::thread T;

    // Creating socket file descriptor
    check((server_fd = socket(AF_INET, SOCK_STREAM, 0)), "Soket_failed");

    // Forcefully attaching socket to the port 8080
    check(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                     &opt, sizeof(opt)),
          "Set_socket_failed");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    check(bind(server_fd, (struct sockaddr *)&address,
               sizeof(address)),
          "Bind_failed");

    check(listen(server_fd, SERVER_BACKLOG), "Listen_failed");

    while (true)
    {
        check((new_socket = accept(server_fd, (struct sockaddr *)&address,

                                   (socklen_t *)&addrlen)),
              "accept_failed");

        printf("%s\n", buffer_recv);
        T = std::thread(handle_connection, new_socket);
        T.detach();
    }
    return 0;
}