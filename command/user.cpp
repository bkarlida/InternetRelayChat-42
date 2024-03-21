
#include "command.hpp"

void user(std::vector<Client>& clients, Client& ite, Server& server) {
    std::string message;

    if (ite.isRegistered == true) {
        message = ERR_ALREADYREGISTRED();
        send(ite.socket_fd, message.c_str(), message.size(), 0);
        return;
    }

    if (ite.commands.size() < 5) {
        message = ERR_NEEDMOREPARAMS();
        send(ite.socket_fd, message.c_str(), message.size(), 0);
        return;
    }

    std::string buffer;
    for (int i = 0; i < ite.commands.size(); i++) {
        if (ite.commands[i][0] == ':' && i == 4) {
            buffer += (&ite.commands[i][1]);
            while (++i < ite.commands.size()) {
                buffer += " ";
                buffer += ite.commands[i];
            }
            break;
        } else {
            buffer += ite.commands[i];
            buffer += " ";
        }
    }

    std::vector<std::string> userService;
    size_t pos = 0;
    while ((pos = buffer.find(' ')) != std::string::npos) {
        userService.push_back(buffer.substr(0, pos));
        buffer.erase(0, pos + 1);
    }

    if (userService.size() != 5 && userService[2][0] != '0' && userService[3][0] != '*') {
        message = ite.getPrefix() + ": Error: Wrong userparameters\r\n";
        send(ite.socket_fd, message.c_str(), message.size(), 0);
        return;
    }

    ite.set_username(userService[1]);
    ite.set_realname(userService[4]);

	std::cout << "userName: " + ite.get_username() << "\nrealName" + ite.get_realname()<< std::endl;

}