#include "client.hpp"
#include "server.hpp"

int	commandInterface(std::string buffer, Client *client, std::vector <Client> clients, Server &server)
{
	std::cout << "girdiii \n\n\n\n";
    std::string pass;
    std::string nick;
    std::string user;
    std::string real;
    
    std::stringstream stringStream(buffer);
    
    std::vector <std::string> splitStrings;

    for (std::string line; std::getline(stringStream, line, '\n'); )
        splitStrings.push_back(line);

    std::vector <std::string>::iterator iter = splitStrings.begin();

    if (iter->size() > 4 && iter->substr(0, 4) == "PASS")
        pass = iter->substr(6), iter++;

    if (iter->size() > 4 && iter->substr(0, 4) == "NICK")
        nick = iter->substr(5), iter++;
    else
        return 0;

    if (iter->size() > 4 && iter->substr(0, 4) == "USER")
    {
        user = iter->substr(5, iter->find(' ', 5) - 5);
        real = iter->substr(iter->find(':') + 5);
    }
    else
        return 0;

    if (pass.erase(pass.size() - 1) == server.getPassword())
		client->isRegistered = true;

	client->set_username(user);
	client->set_nickname(nick);
	client->set_realname(real);

	return 1;
}

void handleBuffer(std::string buffer, Client *client, std::vector <Client> clients, Server * server)
{
    if (commandInterface(buffer, client, clients, *server))
		std::cout << "isRegistered: " << client->isRegistered << std::endl; 
}
