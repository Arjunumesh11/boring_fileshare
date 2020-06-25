#include "chunkencoding.h"
void check(int status, std::string error); //function to check error

using namespace chunk;

std::vector<char> chunk::make_chunk(std::vector<char> chunk, int size)
{
    std::ostringstream temp;
    std::vector<char> result;
    std::string temp_result;
    if (size == -1)
        size = chunk.size();
    temp << std::hex << size;
    temp << chunk::CLRF;
    temp_result = temp.str();
    std::copy(temp_result.begin(), temp_result.end(), std::back_inserter(result));
    std::copy(chunk.begin(), chunk.begin() + size, std::back_inserter(result));
    std::copy(chunk::CLRF.begin(), chunk::CLRF.end(), std::back_inserter(result));
    return result;
}

int chunk::send_chunk(int new_socket, std::string file_path)
{
    int file_size, flag = 1;
    std::vector<char> content;
    std::string header;
    std::vector<char> buffer(BUFFER_SIZE);
    std::streamsize s;

    std::ifstream file(file_path.c_str(), std::ios::binary);
    if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        file_size = file.tellg();
        file.seekg(0, std::ios::beg);
    }
    else
    {
        perror("file not found ");
        return -1;
    }

    header = http_header::make_header(file_path, file_size);

    send(new_socket, header.c_str(), header.length(), MSG_NOSIGNAL);

    while (file.read(&buffer[0], BUFFER_SIZE) && flag)
    {
        s = file.gcount();
        content = chunk::make_chunk(buffer, s);
        // check(send(new_socket, &content[0], content.size(), MSG_NOSIGNAL), "Write_error");
        if (send(new_socket, &content[0], content.size(), MSG_NOSIGNAL) < 0)
        {
            flag = 0;
            return -1;
        }
    }
    s = file.gcount();
    content = chunk::make_chunk(buffer, s);
    if (!content.empty())
    {
        send(new_socket, &content[0], content.size(), MSG_NOSIGNAL);
    }

    send(new_socket, chunk::END.c_str(), chunk::END.length(), MSG_NOSIGNAL);
    fprintf(stderr, "\nterminated\n");
    return 0;
}