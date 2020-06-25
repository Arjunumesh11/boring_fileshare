#ifndef _serve_static
#define _serve_static

#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include "file_handler.h"
#include "chunkencoding.h"

namespace serve_static
{
    class servestatic
    {
        std::string folder;
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

        //handle static files
        //@param : file_path
        //@param : socket
        //@return : -1 if not successfull else 0
        int serve(std::string path, int new_socket);
    };

} // namespace serve_static

#endif