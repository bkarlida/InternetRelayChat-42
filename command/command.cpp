#include "../server.hpp"
#include "command.hpp"

void message_join(Client *ite, std::string message)
{
    std::string buffer = ite->getPrefix() + " "  +  message + "\r\n";
    send(ite->socket_fd, buffer.c_str(), buffer.size(), 0);
}
void message_for_topic(Client &ite, std::string message)
{
    std::string buffer = ite.getPrefix() + " "  +  message + "\r\n";;
    send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}
void sendmessage(Client &ite, std::string message)
{
    std::string buffer = ite.getPrefix() + " "  +  message + "\r\n";
    int response = send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
    if (response < 0)
        std::cout << "sendMessage error occured!\n";
}

std::string setDefaultNick(Client & client, std::vector<Client> clients, std::string newNickName)
{
    std::string defaultNick = "default";
    std::string finalNick;
    int addition = 1;
    for( ; addition < INT_MAX; addition++)
    {
        int flag = 0;
        for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); i++)
        {
            std::string tempNick = std::to_string(addition);
            finalNick = defaultNick + tempNick;
            if (finalNick == i->get_nickname())
                flag = 1; break ;
        }
        if (flag == 0)
            break ;
    }
    return (finalNick);
}

int isNickValid(Client & client, std::vector<Client> clients, std::string newNickName)
{
    std::cout << "in isNickValid:" << newNickName << std::endl;
    // Check if the new nickname is valid
    for (size_t i = 0; i < newNickName.length(); i++) {
        if (!std::isprint(newNickName[i]) || (i == 0 && std::isdigit(newNickName[i]))) {
            std::string error = ERR_ERRONEUSNICKNAME(newNickName);
            std::cout << "ERROR: " << error << " on fd: " << client.socket_fd << std::endl;
            send(client.socket_fd, error.c_str(), error.size(), 0);
            return 0;
        }
    }

    // Check if the new nickname is already in use
    for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->get_nickname() == newNickName) {
            if (client.get_nickname().empty())
            {
                newNickName = setDefaultNick(client, clients, newNickName);
                std::string error = RPL_NICK(client.get_nickname(), newNickName);
                send(client.socket_fd, error.c_str(), error.size(), 0);
                std::cout << "New nick name is : " <<  newNickName << std::endl;
                client.set_nickname(newNickName);
                return 2;
            }
            std::string error = ERR_NICKNAMEINUSE(newNickName);
            std::cout << "ERROR: " << error << std::endl;
            send(client.socket_fd, error.c_str(), error.size(), 0);
            return 0;
        }
    }
    return 1;
}