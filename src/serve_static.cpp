#include "serve_static.h"
using namespace serve_static;
void check(int status, std::string error);
serve_static::servestatic::servestatic(std::string folder)
{
    serve_static::servestatic::servestatic::folder = folder;
    if (serve_static::servestatic::_root_folder.create_directory(folder) < 0)
    {
        fprintf(stderr, "NO DIRECTOR FOUND file() : %s\n", std::strerror(errno));
        exit(EXIT_FAILURE);
    }
    servestatic::file_paths = serve_static::servestatic::_root_folder.get_paths();
}

int serve_static::servestatic::create_directory(std::string folder)
{
    serve_static::servestatic::servestatic::folder = folder;
    if (serve_static::servestatic::_root_folder.create_directory(folder) < 0)
    {
        return -1;
    }
    servestatic::file_paths = serve_static::servestatic::_root_folder.get_paths();
    return 0;
}

int serve_static::servestatic::serve(std::string path, int new_socket)
{
    path = serve_static::servestatic::folder + path;
    fprintf(stderr, "\nGET %s %lu\n", path.c_str(), path.length());
    std::vector<std::string>::iterator it;
    it = std::find(serve_static::servestatic::file_paths.begin(), serve_static::servestatic::file_paths.end(), path);
    if (it == serve_static::servestatic::file_paths.end())
    {
        return -1;
    }
    check(chunk::send_chunk(new_socket, path), "send_chunk error");
    close(new_socket);
    return 0;
}