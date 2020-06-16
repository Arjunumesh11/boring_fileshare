#include "chunkencoding.h"
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