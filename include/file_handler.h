#ifndef _file_handler
#define _file_handler

#include <errno.h>
#include <cstring>
#include <ftw.h>
#include <dirent.h>
#include <fnmatch.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <unordered_map>
extern struct stat sb;

namespace file_handler
{
    class file
    {
    public:
        file(){};

        //intialise wiht root directory
        //@param : std::string root_folder
        file(std::string root_folder);

        //create directory
        //      @param : std::string root_folder
        //      @return :-1 if not successfull
        int create_directory(std::string root_folder);

        //get file_list
        //     @param : none
        //     @return : std::list<string> filelist
        std::vector<std::string> get_filelist();

        //get file name,path
        //    @param : std::string filename
        //    @return : std::string filepath
        std::string get_file(std::string filename);

        //get path list
        //    @return : std::string filepaths
        std::vector<std::string> get_paths();

    private:
        static int parser(const char *fpath, const struct stat *sb, int typeflag);
        static std::unordered_map<std::string, std::string> _file_list;
        std::unordered_map<std::string, std::string> file_list;
        std::vector<std::string> file_names;
        std::vector<std::string> file_paths;
        int a;
    };
} // namespace file_handler

#endif