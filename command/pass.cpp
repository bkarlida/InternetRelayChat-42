#include "command.hpp"

void pass(Client * client, Server * server)
{
    std::cout << "commands size in pass:" << client->commands.size() << std::endl;
    if (client->commands.size() != 2)
    {
        std::cout << "in wrong param\n";
        std::string err = ERR_WRONGPARAM();
        size_t lenght = err.length();
        send(client->socket_fd, err.c_str(), lenght, 0);
        return ;
    }
    else if (client->isPassed == true)
    {
        if (client->isRegistered == true)
        {
            std::string err = ERR_ALREADYREGISTRED();
            size_t lenght = err.length();
            send(client->socket_fd, err.c_str(), lenght, 0);
        }
        return ;
    }
    else if (client->commands[1] != server->getPassword())
    {
        std::cout << "err pass match\n";
        std::string err = ERR_PASSWDMISMATCH();
        size_t lenght = err.length();
        send(client->socket_fd, err.c_str(), lenght, 0);
        return ;
    }
    std::string message = "this message is fuck\r\n";
    if (!client->get_nickname().empty() && !client->get_realname().empty() && !client->get_username().empty())
        client->isRegistered = true, client->isPassed = true, send(client->socket_fd, message.c_str(), message.size(), 0);
    else
        client->isPassed = true, send(client->socket_fd, "Server: Password is correct. USER informations needed to register.\r\n", 68, 0);
    std::cout << client->isPassed << client->isRegistered << std::endl;
}