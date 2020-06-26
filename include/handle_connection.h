#ifndef _handle_connection
#define _handle_connection

#include <string>
#include <utility>
#include <vector>
#include <errno.h>
#include <functional>

namespace handle_connection
{
    class handleconnection
    {
        std::vector<std::pair<void *, int (*)(void *, std::string, int)>> funclist;

    public:
        //adds function to the list of function to excecute
        //@param reference of the object
        //@param : int (*func)(void* ,std::string,int) function
        void use(void *object, int (*func)(void *context, std::string response, int new_socket))
        {
            funclist.push_back(std::make_pair(object, func));
            //need to store the type information of reference object( T)
            //code is incomplete
        }

        //call
        //@param : string response
        //@param : int socket
        int call(std::string response, int new_socket)
        {
            for (auto c : funclist)
            {
                //need to extract the type of the reference object T
                if (c.second(c.first, response, new_socket) == 0) //code is incomplete
                    return 0;
            }
            return -1;
        }
    };
} // namespace handle_connection

#endif