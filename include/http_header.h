#ifndef _http_header
#define _http_header

#include <string>
#include <sstream>

namespace http_header
{
    std::string get_contenttype(std::string filename);
    std::string get_filename(std::string filename);
    std::string make_header(std::string filename, int file_size);

} // namespace http_header

#endif