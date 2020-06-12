#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#define PORT 8080
std::string get_contenttype(std::string filename)
{
    std::string type;
    if (filename.substr(filename.find_last_of(".")) == ".jpg")
        type = "image/jpeg";
    return type;
}

std::string make_header(std::string filename)
{
    std::ostringstream header;
    header << "HTTP/1.1 200 OK\r\n";
    header << "Content-Type: " << get_contenttype(filename) << "\r\n";
    header << "Content-Disposition: attachment; filename =\"" << filename << "\"\r\n";
    header << "Connection: close\r\n";
    header << "Content-Length: 201368\r\n\r\n";
    return header.str();
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1, file_size;

    std::string header = make_header("image.jpg");
    std::ifstream file("image.jpg", std::ios::binary);
    if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        file_size = file.tellg();
        file.seekg(0, std::ios::beg);
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    std::string response(header);
    response.append(content);
    file.close();

    int addrlen = sizeof(address);
    char buffer[1024] = {0};
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
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
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
    valread = recv(new_socket, buffer, 1024, 0);
    printf("%s\n", buffer);

    write(new_socket, response.c_str(), response.length());
    printf("Hello message sent\n");
    return 0;
}