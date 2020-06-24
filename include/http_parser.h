#ifndef _http_parser
#define _http_parser
#include <string>

// GET / HTTP / 1.1
// Host : localhost : 3000
// User - Agent : Mozilla / 5.0(X11; Ubuntu; Linux x86_64; rv : 76.0)Gecko / 20100101 Firefox / 76.0
// Accept : text / html, application / xhtml + xml, application / xml; q = 0.9, image / webp, */*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Upgrade-Insecure-Requests: 1

namespace http_parser
{
    class http
    {
        std::string request;
        std::string path;
        /*
            more features;
        */
    public:
        http(){};

        //intialise with request
        http(std::string request);

        //parse request
        //@param : request
        //@return -1 if not successfull
        int parse(std::string request);

        //getpath from request
        //return -1 if path not set
        std::string getpath();
    };

} // namespace http_parser

#endif