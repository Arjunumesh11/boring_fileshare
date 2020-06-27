#ifndef _html_template
#define _html_template

#include <string>
#include <sstream>
#include <vector>

namespace html_template
{

    class html_page
    {
        std::vector<std::string> tags;
        std::string page_beg;
        std::string page_end;

    public:
        int init_page(std::string title = "Document");
        int add_link(std::string src, std::string name);
        std::string get_page();
    };
} // namespace html_template

#endif