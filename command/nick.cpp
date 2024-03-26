#include "command.hpp"


void NICK(std::vector<Client>& clients, Client& ite, Server& server, std::vector<Channel>& channels) {
    std::vector<Channel>::iterator channelIterator = channels.begin();
    std::vector<Client>::iterator clientIterator = clients.begin();
    std::vector<std::string>::iterator commandIterator = ite.commands.begin();

    commandIterator++;

    std::string newNickname = *commandIterator;

    // Check if the new nickname is valid
    for (size_t i = 0; i < newNickname.length(); i++) {
        if (!std::isprint(newNickname[i]) || (i == 0 && std::isdigit(newNickname[i]))) {
            std::string error = ERR_ERRONEUSNICKNAME(newNickname);
            std::cout << "ERROR: " << error << std::endl;
            return;
        }
    }

    // Check if the new nickname is already in use
    for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->get_nickname() == newNickname) {
            std::string error = ERR_NICKNAMEINUSE(newNickname);
            std::cout << "ERROR: " << error << std::endl;
            return;
        }
    }

    // Change the nickname and notify the client and server
    for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->get_nickname() == ite.get_nickname()) {
            std::string buffer = RPL_NICK(ite.get_nickname(), ite.get_username(), newNickname);
            it->set_nickname(newNickname);
            ite.set_nickname(newNickname);
            std::cout << "NICK: Requesting the new nick " + it->get_nickname() + "\r\n" << std::endl;
            // Assuming the send function works properly
            // if (send(ite.socket_fd, buffer.c_str(), buffer.size(), 0) < 0)
            //     std::cout << "SEND ERROR" << std::endl;
            return;
        }
    }
}