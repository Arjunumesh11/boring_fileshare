#ifndef _router
#define _router
#include <map>
#include <string>
#include <regex>
#include <vector>

namespace router
{

    //std::map<std::string,std::string> get(std::string path,std::string url)
    //@param : path to be matched
    //@param : url
    //@return : map containing parameters
    std::map<std::string, std::string> get(std::string path, std::string url);
    const std::string path_pattern = ":([^\\/]+)?";
    const std::string capture_pattern = "(?:([^\\/]+?))";
} // namespace router

#endif