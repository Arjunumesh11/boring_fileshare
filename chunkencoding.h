#ifndef _chunkencoding
#define _chunkencoding
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
namespace chunk
{
    const std::string CLRF = "\r\n";
    const std::string END = "0\r\n\r\n";

    std::vector<char> make_chunk(std::vector<char> chunk, int size = -1);
} // namespace chunk

#endif