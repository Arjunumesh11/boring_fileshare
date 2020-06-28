#include "html_template.h"
using namespace html_template;

int html_template::html_page::init_page(std::string title)
{
    std::ostringstream page;
    page << "<!DOCTYPE html>\n"
         << "<html lang = \"en\">\n"
         << "<head>\n"
         << "<meta charset = \" UTF - 8 \">\n"
         << "<meta name = \" viewport \" content = \" width = device - width, initial -scale = 1.0 \">\n"
         << "<title>" << title << "</title>\n"
         << "<script src = \"./ script.js \"> </script>\n"
         << "</head>\n"
         << "<body>\n"
         << "<ul>\n";
    html_template::html_page::page_beg = page.str();
    page.str("");
    page.clear();
    page << "</ul>"
         << "</body>\n"
         << "</html>\n";
    html_template::html_page::page_end = page.str();
    return 0;
}

int html_template::html_page::add_link(std::string src, std::string name)
{
    std::ostringstream link;
    link << "<li><a href=\"" << src << "\" > " << name << " </a></li>\n";
    html_template::html_page::tags.push_back(link.str());
    return 0;
}

std::string html_template::html_page::get_page()
{
    std::ostringstream page;
    page << html_template::html_page::page_beg;
    for (auto c : html_template::html_page::tags)
    {
        page << c;
    }
    page << html_template::html_page::page_end;
    return page.str();
}