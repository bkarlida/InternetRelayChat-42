
#include "command.hpp"

void cap(std::vector<Client> clients, Client ite, Server &server)
{
	std::string buffer = ite.getPrefix() + " "  +  " CAP * LS :multi-refix sasl" + "\r\n";
    send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}
