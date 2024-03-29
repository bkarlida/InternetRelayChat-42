
#include "command.hpp"

void	privmsg(std::vector<Client> clients, Client &ite, std::vector <Channel> &channel, std::string buffer)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	std::string buf;
	int pos = buffer.find(":");
	buf = buffer.substr(pos,(buffer.length() - pos - 2));
	std::cout << "buf:" << buf <<"#"<<std::endl;
	std::string message1 = "PRIVMSG " + ite.get_nickname()+ " "+ buf + "\r\n";
	if(ite.commands.size() >= 3)
	{
		if(k[1][0] == '#')
		{
			for(std::vector<Channel>::iterator itChannels = channel.begin(); itChannels != channel.end(); itChannels++)
			{
				if(itChannels->ChannelName == k[1])
				{
					for(std::vector<Client *>::iterator users = itChannels->users.begin(); users != itChannels->users.end(); users++)
					{
						if(ite.get_nickname() != (*users)->get_nickname())
						{
							std::cout << "buf:" << buf <<"%"<<std::endl;
							
							sendmessage_privmsg(ite, (*users), "PRIVMSG " + k[1] + " " + buf + "\r\n");
						}
					}
					return ;
				}
			}
			sendmessage2(ite,ite.socket_fd,"403"+ ite.get_nickname()+ " " + k[1] + " :No such channel\r\n");
		}
		else
		{
			for(std::vector<Client>::iterator itClients = clients.begin(); itClients != clients.end(); itClients++)
			{
				if(itClients->get_nickname() == k[1] && ite.get_nickname() != itClients->get_nickname())
				{
							std::cout << "buf:" << buf <<"?"<<std::endl;

					std::string buffer1 = ite.getPrefix() + " "  + message1 +"\r\n";
					send(itClients->socket_fd, buffer1.c_str(), buffer1.size(), 0);
					return ;
				}
			}
			sendmessage2(ite,ite.socket_fd,"401 " + ite.get_nickname() + " " + k[1] + " :No such nick/channel\r\n");
		}
	}
	else
		sendmessage2(ite,ite.socket_fd,"461 " + ite.get_nickname() + " PRIVMSG :Not enough parameters\r\n");
}

