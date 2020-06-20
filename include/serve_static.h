#ifndef _serve_static
#define _serve_static

#include <string>
#include <vector>
#include <cstring>
#include "file_handler.h"

namespace serve_static
{
    class servestatic
    {

        std::vector<std::string> file_paths;
        file_handler::file _root_folder;

    public:
        servestatic() {}

        //int static(std::string folder)
        //@param : folder
        servestatic(std::string folder);

        //intialise public folder
        //@param : folder
        //@return : -1 if not successfull
        int create_directory(std::string folder);

        int serve(std::string response, int new_socket);
    };

} // namespace serve_static

#endif