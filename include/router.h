#ifndef _router
#define _router
#include <map>
#include <string>
#include <regex>

namespace router
{

    //std::map<std::string,std::string> get(std::string path,std::string url)
    //@param : path to be matched
    //@param : url
    //@return : map containing parameters
    std::map<std::string, std::string> get(std::string path, std::string url);
} // namespace router

#endif