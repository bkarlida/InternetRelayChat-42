#include "command.hpp"


void nick(std::vector<Client>& clients, Client& ite, Server& server, std::vector<Channel>& channels) {
    std::vector<Channel>::iterator channelIterator = channels.begin();
    std::vector<Client>::iterator clientIterator = clients.begin();
    std::vector<std::string>::iterator commandIterator = ite.commands.begin();

    commandIterator++;
    std::cout << "in nick function\n";

    std::string newNickname = *commandIterator;

    if (!isNickValid(ite, clients, newNickname))
        return ;

    // Change the nickname and notify the client and server
    std::string buffer = RPL_NICK(ite.get_nickname(), newNickname);
    ite.set_nickname(newNickname);
    send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
    std::cout << "NICK: Requesting the new nick " + ite.get_nickname() + "\r\n" << std::endl;
    // for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
    //     if (it->get_nickname() == ite.get_nickname()) {
    //         std::string buffer = RPL_NICK(ite.get_nickname(), ite.get_username(), newNickname);
    //         it->set_nickname(newNickname);
    //         ite.set_nickname(newNickname);
    //         std::cout << "NICK: Requesting the new nick " + it->get_nickname() + "\r\n" << std::endl;
            // Assuming the send function works properly
            // if (send(ite.socket_fd, buffer.c_str(), buffer.size(), 0) < 0)
            //     std::cout << "SEND ERROR" << std::endl;
    //         return;
    //     }
    // }
}