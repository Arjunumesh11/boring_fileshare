#ifndef _handle_connection
#define _hanfle_connection

#include <string>
#include <vector>

namespace handle_connection
{
    class handleconnection
    {
        std::vector<int (*)(std::string, int)> funclist;

    public:
        //adds function to the list of function to excecute
        //@param : int (*func)(std::string,int) function
        void use(int (*func)(std::string response, int new_socket));

        //call the function in the specified by handleconnection.use()
        //@param : string response
        //@param : int socket
        void call(std::string response, int new_socket);
    };

} // namespace handle_connection

#endif