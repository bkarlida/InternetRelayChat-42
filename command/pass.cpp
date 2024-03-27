#include "command.hpp"

void pass(Client * client, Server * server)
{
    std::string pass;
    if (client->commands[1][0] == 58)
        pass = client->commands[1].substr(1, client->commands[1].size() - 1);
    else
        pass = client->commands[1];

    if (client->commands.size() != 2)
    {
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
    else if (pass != server->getPassword())
    {
        std::string err = ERR_PASSWDMISMATCH();
        size_t lenght = err.length();
        send(client->socket_fd, err.c_str(), lenght, 0);
        return ;
    }
    std::string message = "Server: Register completed!\r\n";
    if (!client->get_nickname().empty() && !client->get_realname().empty() && !client->get_username().empty())
        client->isRegistered = true, client->isPassed = true, send(client->socket_fd, message.c_str(), message.size(), 0);
    else
        client->isPassed = true, send(client->socket_fd, "Server: Password is correct.\r\n", 30, 0);
    std::cout << client->isPassed << client->isRegistered << std::endl;
}