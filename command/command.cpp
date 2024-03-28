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
    send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}

int isNickValid(Client & client, std::vector<Client> clients, std::string newNickName)
{
    std::cout << "in isNickValid:" << newNickName << std::endl;
    // Check if the new nickname is valid
    for (size_t i = 0; i < newNickName.length(); i++) {
        if (!std::isprint(newNickName[i]) || (i == 0 && std::isdigit(newNickName[i]))) {
            std::string error = ERR_ERRONEUSNICKNAME(newNickName);
            std::cout << "ERROR: " << error << std::endl;
            send(client.socket_fd, error.c_str(), error.size(), 0);
            return 0;
        }
    }

    // Check if the new nickname is already in use
    for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->get_nickname() == newNickName) {
            std::string error = ERR_NICKNAMEINUSE(newNickName);
            std::cout << "ERROR: " << error << std::endl;
            send(client.socket_fd, error.c_str(), error.size(), 0);
            return 0;
        }
    }
    return 1;
}