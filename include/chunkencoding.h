#ifndef _chunkencoding
#define _chunkencoding
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "http_header.h"
#include <sys/socket.h>
#include <errno.h>
#include <cstring>
#include <iomanip>
namespace chunk
{
    const std::string CLRF = "\r\n";
    const std::string END = "0\r\n\r\n";
    // make chunk
    //@param : data
    //@param : size
    //return : chunked data
    std::vector<char> make_chunk(std::vector<char> chunk, int size = -1);
    //send chunk
    //@param sockek
    //@param file name
    //return -1 if failed
    int send_chunk(int new_socket, std::string file_name);
} // namespace chunk

#endif