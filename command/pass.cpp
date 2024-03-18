#include "server.hpp"
#include "command.hpp"

void pass(std::string buffer, Client & client, Server & server)
{
    if (client.isRegistered == true)
    {
        std::string err = ERR_ALREADYREGISTRED();
        size_t lenght = err.length();
        send(client.socket_fd, err.c_str(), lenght, 0);
        return ;
    }
    if (buffer.length() >! 6 || buffer.substr(6) != server.getPassword())
    {
        std::string err = ERR_PASSWDMISMATCH();
        size_t lenght = err.length();
        send(client.socket_fd, err.c_str(), lenght, 0);
        return ;
    }
    client.isRegistered = true;
}