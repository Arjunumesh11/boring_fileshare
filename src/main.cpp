#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fstream>
#include <thread>
#include <errno.h>
#include <cstring>
#include "http_header.h"
#include "chunkencoding.h"
#include "serve_static.h"
#include "handle_connection.h"
#include "http_parser.h"
#include <iostream>

#define PORT 3000
#define SERVER_BACKLOG 10
#define THREAD_POOL_SIZE 10

void check(int status, std::string error) //function to check error
{
    if (status == -1)
    {
        fprintf(stderr, "%s : %s\n", error.c_str(), std::strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    std::string request;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    char buffer_recv[BUFFER_SIZE] = {0};
    std::thread T;

    http_parser::http server;
    handle_connection::handleconnection connections;
    serve_static::servestatic public_folder;
    serve_static::servestatic test_folder;

    check(public_folder.create_directory("./public"), "create public folder");
    check(test_folder.create_directory("./test_input"), "create test folder");
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
        read(new_socket, buffer_recv, 1024);
        request = buffer_recv;
        fprintf(stderr, "%s", request.c_str());
        T = std::thread([&server, &public_folder, &test_folder](std::string request, int new_socket) {
            server.parse(request);
            if (public_folder.serve(server.getpath(), new_socket) < 0)
                if (test_folder.serve(server.getpath(), new_socket) < 0)
                {
                    close(new_socket);
                    return -1;
                }
            close(new_socket);
            return 0;
        },
                        request, new_socket);
        // read(new_socket, buffer_recv, 1024);
        // std::cout << server.getpath();
        // T = std::thread(send_video, new_socket);
        T.detach();
    }
    return 0;
}