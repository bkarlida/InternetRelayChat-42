
#include "command.hpp"

void	who(std::vector<Client> clients, Client ite, Server &server, std::vector <Channel> &channel)
{
	std::cout << "error:1"<< std::endl;


	std::string error;
	if (ite.commands.size() == 1)
	{
		error = ERR_NEEDMOREPARAMS("WHO");
		send(ite.socket_fd, error.c_str() , error.size(), 0);
		return;
	}
	int flag = 0;
	if (ite.commands[1][0] == '#')
	{
	std::cout << "error:2"<< std::endl;

		int counter = 0;
		for (std::vector<Channel>::iterator itChannels = server.channels.begin(); itChannels != server.channels.end(); itChannels++)
		{
	std::cout << "error:3"<< std::endl;

			if (itChannels->ChannelName == ite.commands[1])
				flag = 1;
			counter++;
		}
		if (counter == 0 || flag == 0)
		{
	std::cout << "error:4"<< std::endl;

			error = ERR_NOSUCHCHANNEL(ite.commands[1]);
			send(ite.socket_fd, error.c_str(), error.size(), 0);
			return ;
		}
	std::cout << "error:5"<< std::endl;

		std::vector<Channel>::iterator itChannels = server.channels.begin();
		while (itChannels != server.channels.end())
		{
			if (itChannels->ChannelName == ite.commands[1])
			{
	std::cout << "error:6"<< std::endl;

				for(std::vector<Client *>::iterator users = itChannels->users.begin(); users != itChannels->users.end(); users++)
				{
	std::cout << "error:7"<< std::endl;

					std::string message = RPL_WHOREPLY((*users)->get_nickname(), itChannels->ChannelName, (*users)->get_username(), server.hostnameHelper(), "localhost", (*users)->get_nickname(), "*", "0 ", (*users)->get_realname());
					send(ite.socket_fd, message.c_str() , message.size(), 0);
				}
				std::string message2= RPL_ENDOFWHO(ite.get_nickname(), itChannels->ChannelName);
				send(ite.socket_fd, message2.c_str() , message2.size(), 0);
			}
			itChannels++;
		}
	std::cout << "error:8"<< std::endl;

	}
	else
	{
		flag = 0;
		int flag2;
	std::cout << "error:9"<< std::endl;

		for (std::vector<Client>::iterator users = clients.begin(); users != clients.end(); users++)
		{
	std::cout << "error:10"<< std::endl;

			flag2 = 0;
			for(std::vector<Channel>::iterator c = users->isjoined.begin(); c != users->isjoined.end(); c++)
			{
				flag2 = 1;
				if (users->get_nickname() == ite.commands[1])
				{
					flag = 1;
					std::string message = RPL_WHOREPLY(users->get_nickname(), c->ChannelName, users->get_username(), server.hostnameHelper(), "localhost", users->get_nickname(), "*", "0 ", users->get_realname());
					send(ite.socket_fd, message.c_str() , message.size(), 0);
					message = RPL_ENDOFWHO(users->get_nickname(), c->ChannelName);
					send(ite.socket_fd, message.c_str() , message.size(), 0);
				}
			}
	std::cout << "error:11"<< std::endl;
			
			if (flag2 == 0)
			{
				if (users->get_nickname() == ite.commands[1])
				{
	std::cout << "error:12"<< std::endl;

					flag = 1;
					std::string message = RPL_WHOREPLY(users->get_nickname(),"*", users->get_username(), server.hostnameHelper(), "localhost", users->get_nickname(), "*", "0", users->get_realname());
					send(ite.socket_fd, message.c_str() , message.size(), 0);
					message = RPL_ENDOFWHO(users->get_nickname(), "channel");
					send(ite.socket_fd, message.c_str() , message.size(), 0);
					return ;
				}
			}

		}
		if (flag == 0)
		{
	std::cout << "error:13"<< std::endl;

			error = ERR_NOSUCHNICK(ite.commands[1]);
			send(ite.socket_fd, error.c_str(), error.size(), 0);
			return ;
		}
	}
}
