
#include "command.hpp"

void topic(std::vector<Client> &clients, Client &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	k++;
	for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
	{
		if(itChannels->ChannelName == *k)
		{
			if (k[1][0] == ':' && isalpha(k[1][1]))
			{
				itChannels->isTopic = true;
				itChannels->setTopic(k[1]);
				message_for_topic(ite, RPL_TOPIC(ite.get_nickname(), itChannels->ChannelName, itChannels->getTopic()));
				return ;
			}
			else if (k[1][0] == ':' && isalpha(k[1][1]))
			{
				itChannels->isTopic = true;
				itChannels->setTopic(k[1]);
				message_for_topic(ite, RPL_TOPIC(ite.get_nickname(), itChannels->ChannelName, itChannels->getTopic()));
				return ;
			}
			else
			{
				std::string buffer = RPL_NOTOPIC(ite.get_nickname(), itChannels->ChannelName);
				message_for_topic(ite, RPL_NOTOPIC(ite.get_nickname(), itChannels->ChannelName));
				return ;
			}
		}
	}
}

