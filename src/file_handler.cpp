#include "file_handler.h"
using namespace file_handler;
struct stat sb;
std::unordered_map<std::string, std::string> file_handler::file::_file_list;

int file_handler::file::create_directory(std::string root_folder)
{
    if (stat(root_folder.c_str(), &sb) == -1)
        return -1;
    ftw(root_folder.c_str(), parser, 16);
    return 0;
}

file_handler::file::file(std::string root_folder)
{
    if (stat(root_folder.c_str(), &sb) == -1)
    {
        fprintf(stderr, "NO DIRECTOR FOUND file() : %s\n", std::strerror(errno));
        exit(EXIT_FAILURE);
    }
    ftw(root_folder.c_str(), parser, 16);
}

int file_handler::file::parser(const char *fpath, const struct stat *sb, int typeflag)
{
    if (typeflag == FTW_F)
    {
        std::string filepath(fpath);
        std::string filename = filepath.substr(filepath.find_last_of("/") + 1);
        file_handler::file::_file_list[filename] = filepath;
    }
    return 0;
}

std::vector<std::string> file_handler::file::get_filelist()
{
    if (file_handler::file::file_list.empty())
    {
        for (auto kv : file_handler::file::_file_list)
        {
            file_handler::file::file_list.push_back(kv.first);
        }
    }

    return file_handler::file::file_list;
}

std::vector<std::string> file_handler::file::get_paths()
{
    if (file_handler::file::file_paths.empty())
    {
        for (auto kv : file_handler::file::_file_list)
        {
            file_handler::file::file_paths.push_back(kv.second);
        }
    }

    return file_handler::file::file_paths;
}

std::string file_handler::file::get_file(std::string filename)
{
    if (file_handler::file::_file_list.find(filename) == file_handler::file::_file_list.end())
    {
        fprintf(stderr, "File : %s Not found", filename.c_str());
        return "";
    }
    return file_handler::file::_file_list[filename];
}
