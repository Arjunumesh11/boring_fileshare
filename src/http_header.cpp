#include "http_header.h"
using namespace http_header;

std::string http_header::get_contenttype(std::string filename)
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
std::string http_header::get_filename(std::string filename)
{
    std::string result = filename.substr(filename.find_last_of("/") + 1);
    return result;
}
std::string http_header::make_header(std::string filename, int file_size)
{
    std::ostringstream header;
    header << "HTTP/1.1 200 OK\r\n";
    header << "Content-Type: " << http_header::get_contenttype(filename) << "\r\n";
    header << "Content-Disposition: inline; filename =\"" << http_header::get_filename(filename) << "\"\r\n";
    header << "Connection: keep-alive\r\n";
    header << "Transfer-Encoding: chunked\r\n";
    header << "\r\n";
    return header.str();
}