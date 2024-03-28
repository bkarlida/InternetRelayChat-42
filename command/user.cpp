
#include "command.hpp"

void user(std::vector<Client>& clients, Client& ite, Server& server) {
    std::string message;
    if (!ite.isPassed)
    {
        std::string message = "462 :Client should enter the password correctly\r\n";
        send(ite.socket_fd, message.c_str(), message.size(), 0);
        return ;
    }
    else if (ite.commands.size() < 5) {
        message = ERR_NEEDMOREPARAMS();
        send(ite.socket_fd, message.c_str(), message.size(), 0);
        return;
    }

    if (ite.commands.size() != 5 && ite.commands[2][0] != '0' && ite.commands[3][0] != '*') {
        message = ite.getPrefix() + ERR_WRONGPARAM();
        send(ite.socket_fd, message.c_str(), message.size(), 0);
        return;
    }
    for (std::vector<std::string> ::iterator i = ite.commands.begin(); i != ite.commands.end(); i++)
        std::cout << *i << std::endl;
    ite.set_username(ite.commands[1]);
    ite.set_realname(ite.commands[4]);
    message = USERINFOADD();
    send(ite.socket_fd, message.c_str(), message.size(), 0);
	std::cout << "userName: " + ite.get_username() << "\nrealName" + ite.get_realname()<< std::endl;

}