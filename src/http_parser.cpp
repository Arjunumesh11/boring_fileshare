#include "http_parser.h"
using namespace http_parser;

http_parser::http::http(std::string request)
{
    http_parser::http::request = request;
    int end = request.find(" ", request.find_first_of(" ") + 1);
    int start = request.find_first_of(" ");
    http_parser::http::path = http_parser::http::request.substr(start, end - start);
}

int http_parser::http::parse(std::string request)
{
    if (request.empty())
        return -1;
    http_parser::http::request = request;
    int end = request.find(" ", request.find_first_of(" ") + 1);
    int start = request.find_first_of(" ");
    http_parser::http::path = http_parser::http::request.substr(start, end - start);
    if (path.empty())
        return -1;
    return 0;
}

std::string http_parser::http::getpath()
{
    return http_parser::http::path;
}