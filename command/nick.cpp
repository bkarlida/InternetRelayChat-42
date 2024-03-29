#include "command.hpp"


void nick(std::vector<Client>& clients, Client& ite, Server& server, std::vector<Channel>& channels) {
    std::vector<std::string>::iterator commandIterator = ite.commands.begin();

    commandIterator++;
    std::cout << "in nick function\n";
    std::string error;
    if (ite.commands.size() == 1)
	{
		error = ERR_NONICKNAMEGIVEN();
		send(ite.socket_fd, error.c_str() , error.size(), 0);
        return;
	}

    std::string newNickname = *commandIterator;
    int isNickValidFlag = isNickValid(ite, clients, newNickname);
    if (isNickValidFlag == 0)
        return ;

    // Change the nickname and notify the client and server
    std::string buffer = RPL_NICK(ite.get_nickname(), newNickname);
    if (isNickValidFlag == 1)
    {
        ite.set_nickname(newNickname);
        send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
    }
    std::cout << "NICK: Requesting the new nick " + ite.get_nickname() + "\r\n" << std::endl;
}