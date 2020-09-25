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
#include "html_template.h"
#include "http_header.h"
#include "chunkencoding.h"
#include "serve_static.h"
#include "handle_connection.h"
#include "http_parser.h"
#include <iostream>

#define PORT 3000
#define SERVER_BACKLOG 10
#define THREAD_POOL_SIZE 10

using namespace std;
void check(int status, string error) //function to check error
{
    if (status == -1)
    {
        fprintf(stderr, "%s : %s\n", error.c_str(), strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    string request;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    char buffer_recv[BUFFER_SIZE] = {0};
    thread T;

    html_template::html_page index_page;
    http_parser::http server;
    handle_connection::handleconnection connections;
    serve_static::servestatic public_folder;
    serve_static::servestatic test_folder;
    file_handler::file video_folder("./test_input");
    vector<string> path = video_folder.get_paths();

    ofstream index_public("./public/index.html");

    vector<string> paths = video_folder.get_filelist();
    index_page.init_page();
    for (auto c : paths)
    {
        index_page.add_link("./" + c, c);
    }
    cout << index_page.get_page();
    index_public << index_page.get_page();
    index_public.close();
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
    handle_connection::handleconnection routes;
    routes.use(&public_folder, serve_static::servestatic::serve);
    routes.use(&test_folder, serve_static::servestatic::serve);
    while (true)
    {
        check((new_socket = accept(server_fd, (struct sockaddr *)&address,

                                   (socklen_t *)&addrlen)),
              "accept_failed");
        read(new_socket, buffer_recv, 1024);
        request = buffer_recv;
        T = thread([&routes, &server](string request, int new_socket) {server.parse(request); routes.call(server.getpath(), new_socket); }, request, new_socket);
        T.detach();
    }
    return 0;
}
