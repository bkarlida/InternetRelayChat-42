
#include "command.hpp"


void topic(std::vector<Client> &clients, Client &ite, Server &server, std::vector <Channel> &channels)
{
	int flag = 0;
	std::vector<std::string>::iterator k = ite.commands.begin();
	k++;
	for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
	{
		if(itChannels->ChannelName == *k)
		{
			std::cout <<  "topic is active" << std::endl;
			if (k[1][0] == ':')
			{
				itChannels->isTopic = true;
				itChannels->setTopic(k[1]);
				message_for_topic(ite, RPL_TOPIC(ite.get_nickname(), itChannels->ChannelName, itChannels->getTopic()));
				return ;
			}

			else
			{
				message_for_topic(ite, RPL_NOTOPIC(ite.get_nickname(), itChannels->ChannelName));
				return ;
			}
		}
	}
}

