
#include "command.hpp"

void	join_info(std::vector<Client> clients, Client &ite, Channel &channels)
{
	std::string names;
	std::vector <Client *> a= channels.users;
	for(std::vector <Client *>::iterator itera = a.begin() ; itera != a.end(); itera++)
	{
		if(itera == a.begin())
		{
			names = "@";
			names += (*itera)->get_nickname();
		}
		else
		{
			names += " ";
			names += (*itera)->get_nickname();
		}
	}
	for(std::vector <Client *>::iterator itera = a.begin() ; itera != a.end(); itera++)
	{
		message_join((*itera), RPL_NAMREPLY((*itera)->get_nickname(), channels.ChannelName, names));
		message_join((*itera), RPL_ENDOFNAMES((*itera)->get_nickname(), channels.ChannelName));
	}
}
int	join_check(std::vector <Channel>::iterator itChannels, Client &ite)
{
	for(std::vector <Client *>::iterator itera = itChannels->users.begin() ; itera != itChannels->users.end(); itera++)
	{
		if((*itera)->get_nickname() == ite.get_nickname())
			return (1);
	}
	return (0);
}
void	join(std::vector<Client> clients, Client &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	*k++;
	if(k[0][0] == '#')
	{annelName == *
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{
			std::cout << "in join: *k: " << *k << std::endl << "channelName: " << itChannels->ChannelName << std::endl;
			if(itChannels->Chk)
			{
				if(join_check(itChannels, ite) == 1)
					return ;
				Client *userPtr1 = &ite;
				itChannels->createUser(userPtr1);
				ite.isjoined.push_back(*itChannels);
				sendmessage(ite, "JOIN You are now in channel " + itChannels->ChannelName);
				join_info(clients, ite, *itChannels);
				return ;
			}
		}
		Client *userPtr = &ite;
		Channel newChannel = Channel((*k), userPtr, userPtr);
		ite.isjoined.push_back(newChannel);
		channels.push_back(newChannel);
		sendmessage(ite, " JOIN You are now in channel " + newChannel.ChannelName);
		std::string buffer = RPL_NOTOPIC(ite.get_nickname(), newChannel.ChannelName);
		message_for_topic(ite, RPL_NOTOPIC(ite.get_nickname(), newChannel.ChannelName));
		join_info(clients, ite, newChannel);
	}
}
