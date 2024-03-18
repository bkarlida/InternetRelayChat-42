#include "server.hpp"
#include "client.hpp"
#include "irc.hpp"

Client * getClientByFd(std::vector <Client> clients, int fd)
{
    for(std::vector <Client>::iterator iter = clients.begin(); iter != clients.end(); iter++)
    {
        if (iter->socket_fd == fd)
            return &(*iter);
    }
    std::cout << " * getClientById: the client assigned on fd couldn't found.\n";
    return (nullptr);
}
