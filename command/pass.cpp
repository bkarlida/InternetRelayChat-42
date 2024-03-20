#include "command.hpp"

void pass(Client & client, Server & server)
{
    std::cout << "#######\n" << client.get_nickname() << client.get_realname() << client.get_username() << std::endl;
    std:: cout << "command substr: " << client.commands[1] << "command size: " << client.commands.size() << std::endl;
    if (client.isPassed == true)
    {
        std::string err = ERR_ALREADYREGISTRED();
        size_t lenght = err.length();
        send(client.socket_fd, err.c_str(), lenght, 0);
        return ;
    }
    if (client.commands.size() != 2 || client.commands[1] != server.getPassword())
    {
        std::cout << "err pass match\n";
        std::string err = ERR_PASSWDMISMATCH();
        size_t lenght = err.length();
        send(client.socket_fd, err.c_str(), lenght, 0);
        return ;
    }
    if (!client.get_nickname().empty() && !client.get_realname().empty() && !client.get_username().empty())
        client.isRegistered = true, client.isPassed = true, send(client.socket_fd, " *Server: Register completed.\r\n", 31, 0);
    else
        client.isPassed = true, send(client.socket_fd, "Server: Password is correct. USER informations needed to register.\r\n", 68, 0);
    std::cout << client.isPassed << client.isRegistered << std::endl;
}