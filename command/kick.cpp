

#include "command.hpp"

void kick(std::vector<Client> clients, Client &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	if(ite.commands.size() == 3 || ite.commands.size() == 4)
	{
		std::string ChannelName = k[1];
		std::string kick_name = k[2];
		std::string reason = "";
		if(k->size() == 4)
			reason = k[3];
		for(std::vector <Channel>::iterator itera = channels.begin() ; itera != channels.end(); itera++)
		{
			if(itera->ChannelName == ChannelName)
			{
				std::vector <Client *>::iterator it = itera->users.begin();
				if(kick_name != (*it)->get_nickname() && kick_name != ite.get_nickname())
				{
					for(std::vector <Client *>::iterator it1 = itera->users.begin() ; it1 != itera->users.end(); it1++)
							sendmessage2(ite, (*it1)->socket_fd, "KICK " + ChannelName + " " + kick_name + " :" + ite.get_nickname()+ "\r\n");
					for(std::vector <Client *>::iterator it1 = itera->users.begin() ; it1 != itera->users.end(); it1++)
					{
						if((*it1)->get_nickname() == kick_name)
						{
							itera->users.erase(it1);
							(*it)->isjoined.erase(itera);
							break ;
						}
					}
				}
			}
		}
	}
}
