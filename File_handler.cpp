#include "File_handler.h"
using namespace file_handler;

std::unordered_map<std::string, std::string> file_handler::file::file_list;

int file_handler::file::create_directory(std::string root_folder)
{
    if (stat(root_folder.c_str(), &sb) == -1)
        return -1;
    ftw(root_folder.c_str(), parser, 16);
}
int file_handler::file::parser(const char *fpath, const struct stat *sb, int typeflag)
{
    if (typeflag == FTW_F)
    {
        std::string filepath(fpath);
        std::string filename = filepath.substr(filepath.find_last_of("/") + 1);
        file_handler::file::file_list[filename] = filepath;
    }
    return 0;
}
// std::list<std::string> get_filelist();
// std::string get_file(std::string filename);
int main()
{
    file_handler::file obj;
    obj.create_directory("./test_input");
    return 0;
}