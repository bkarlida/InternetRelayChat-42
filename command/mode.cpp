
#include "command.hpp"

void mode(std::vector<Client> clients, Client ite, Server &server, std::vector <Channel> channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	std::string names;

	if(k[2] == "+o")
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{

			if(itChannels->ChannelName == k[1])
			{
				names = '@' + k[3];
				sendmessage(ite, "Mode " + itChannels->ChannelName + " +o " +k[3]);
				for(std::vector <Client *>::iterator itera = itChannels->users.begin() ; itera != itChannels->users.end(); itera++)
				{
					(*itera)->set_nickname(names);
					message_join((*itera), RPL_NAMREPLY((*itera)->get_nickname(), k[1], names));
				}
			}
		}
	}
	else if(k[2] == "-o")
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{
			if(itChannels->ChannelName == k[1])
			{
				sendmessage(ite, "Mode " + itChannels->ChannelName + " -o " + k[3]);
				for(std::vector <Client *>::iterator itera = itChannels->users.begin() ; itera != itChannels->users.end(); itera++)
				{
					message_join((*itera), RPL_NAMREPLY((*itera)->get_nickname(), k[1], k[3]));
				}
			}
		}
	}
}
