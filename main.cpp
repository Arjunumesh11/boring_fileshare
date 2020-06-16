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

std::string get_contenttype(std::string filename)
{
    std::string type, extention;
    extention = filename.substr(filename.find_last_of("."));
    if (extention == ".jpg")
        type = "image/jpeg";
    else if (extention == ".png")
        type = "image/png";
    else if (extention == ".zip")
        type = "application/zip";
    else if (extention == ".txt")
        type = "text/plain";
    else if (extention == ".mp4")
        type = "video/mp4";
    else if (extention == ".mkv")
        type = "video/mp4";
    else
        type = "application/octet-stream";
    return type;
}

std::string make_header(std::string filename, int file_size)
{
    std::ostringstream header;
    header << "HTTP/1.1 200 OK\r\n";
    // header << "Content-Type: " << get_contenttype(filename) << "\r\n";
    header << "Content-Type: image/jpeg;\r\n";
    header << "Content-Disposition: attachment; filename =\"plain.jpg\"\r\n";
    header << "Transfer-Encoding: chunked\r\n";
    header << "\r\n";
    // header << "Connection: keep-alive\r\n";
    // header << "Content-Range: 1-1000\r\n\r\n";
    // header << "Content-Length: 1000\r\n\r\n";
    // header << "Content-Length: " << file_size << "\r\n\r\n";
    return header.str();
}
std::string make_msg()
{
    std::ostringstream header;
    header << "A\r\nhelloarjun\r\n";
    return header.str();
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1, file_size;
    std::string file_name;
    file_name = "./test_input/image.jpg";
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
    // std::cout << file_size;
    std::string header = http_header::make_header(file_name, file_size);
    // std::string content((std::istreambuf_iterator<char>(file)),
    //                     std::istreambuf_iterator<char>());
    // std::string response(header);
    // response.append(content);
    // file.close();
    // std::cout << content.length();

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
    char *client_address = new char[100];

    write(new_socket, header.c_str(), header.length());
    std::string tst;
    std::vector<char> content;
    // char *buffer1 = new char[1024];
    std::vector<char> buffer1(1024);
    while (file.read(&buffer1[0], 1024))
    {
        std::streamsize s = file.gcount();
        content = chunk::make_chunk(buffer1, s);
        std::cout << &content[0] << "|" << std::endl
                  << "s = " << s << std::endl;
        write(new_socket, &content[0], content.size());
    }
    std::streamsize s = file.gcount();
    content = chunk::make_chunk(buffer1, s);
    if (!content.empty())
    {
        std::cout << &content[0] << "|" << std::endl
                  << "s =af " << s << std::endl;
        write(new_socket, &content[0], content.size());
    }
    tst = chunk::END;
    write(new_socket, tst.c_str(), tst.length());
    return 0;
}