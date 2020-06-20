#include "handle_connection.h"
using namespace handle_connection;

void handle_connection::handleconnection::use(int (*func)(std::string response, int new_socket))
{
    handle_connection::handleconnection::funclist.push_back(func);
}

void handle_connection::handleconnection::call(std::string response, int new_socket)
{
    for (auto c : handle_connection::handleconnection::funclist)
    {
        if (c(response, new_socket))
            return;
    }
}
