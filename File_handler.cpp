#include "File_handler.h"
using namespace file_handler;

std::unordered_map<std::string, std::string> file_handler::file::_file_list;

int file_handler::file::create_directory(std::string root_folder)
{
    if (stat(root_folder.c_str(), &sb) == -1)
        return -1;
    ftw(root_folder.c_str(), parser, 16);
    return 0;
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
    if (file_list.empty())
    {
        for (auto kv : file_handler::file::_file_list)
        {
            file_list.push_back(kv.first);
        }
    }

    return file_list;
}
// std::string get_file(std::string filename);
int main()
{
    file_handler::file obj;
    std::cout << obj.create_directory("./test_input");
    std::vector<std::string> list = obj.get_filelist();
    std::cout << list[0];
    list = obj.get_filelist();
    std::cout << list[1];

    return 0;
}