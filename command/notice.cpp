
#include "command.hpp"

void	notice(std::vector<Client> clients, Client &ite, std::vector <Channel> &channel)
{
	std::vector<std::string>::iterator itArgs = ite.commands.begin();
	std::string message1 = "PRIVMSG " + ite.get_nickname()+ " "+ itArgs[2] +"\r\n";
	if(ite.commands.size() >= 3)
	{
		if(itArgs[1][0] == '#')
		{
			for(std::vector<Channel>::iterator itChannels = channel.begin(); itChannels != channel.end(); itChannels++)
			{
				if(itChannels->ChannelName == itArgs[1])
				{
					for(std::vector<Client *>::iterator users = itChannels->users.begin(); users != itChannels->users.end(); users++)
					{
						if(ite.get_nickname() != (*users)->get_nickname())
							sendmessage((**users), "PRIVMSG " + itArgs[1] + " " + itArgs[2] + "\r\n");
					}
				}
			}
		}
		else
		{
			for(std::vector<Client>::iterator itClients = clients.begin(); itClients != clients.end(); itClients++)
			{
				if(itClients->get_nickname() == itArgs[1] && ite.get_nickname() != itClients->get_nickname())
				{
					std::string buffer1 = ite.getPrefix() + " "  + message1 +"\r\n";
					send(itClients->socket_fd, buffer1.c_str(), buffer1.size(), 0);
					break;
				}
			}
		}
	}
}

