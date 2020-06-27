#include "html_template.h"
using namespace html_template;

int html_template::html_page::init_page(std::string title)
{
    std::ostringstream page;
    page << "<!DOCTYPE html>"
         << "<html lang = \"en\">"
         << "<head>"
         << "<meta charset = \" UTF - 8 \">"
         << "<meta name = \" viewport \" content = \" width = device - width, initial -scale = 1.0 \">"
         << "<title>" << title << "</ title>"
         << "<script src = \"./ script.js \"> </script>"
         << "</head>"
         << "<body>";
    html_template::html_page::page_beg = page.str();
    page.str("");
    page.clear();
    page << "</ body>"
         << "</ html>";
    html_template::html_page::page_end = page.str();
    return 0;
}

int html_template::html_page::add_link(std::string src, std::string name)
{
    std::ostringstream link;
    link << "<a href=\"" << src << "\" > " << name << " < / a > ";
    html_template::html_page::tags.push_back(link.str());
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