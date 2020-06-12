#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
int main()
{
    std::string header = "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nConnection: close\r\nContent-Length: 201368\r\n\r\n";
    int file_size;
    // std::istringstream ina("sdf");
    // std::string a;
    // char *s = new char[2];
    // ina.read(s, 1);
    // ina.str(s);
    // std::cout << s;
    std::ifstream file("./text.txt", std::ios::binary);
    if (!file.is_open())
        std::cout << "file  not opened " << std::endl;
    file.seekg(0, std::ios::end);
    file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());

    std::string response(header);
    response.append(str);
    std::cout << response;
    // std::cout << str.length() << " " << file_size;
    return 0;
}