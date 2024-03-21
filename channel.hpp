#pragma once


#include "server.hpp"
#include "client.hpp"


class Client;

class Channel
{
	public:
	std::vector <Client *>users;

	std::vector <Client *>admin;

	bool isTopic;
	std::string topic;

	std::string ChannelName;
	Channel(std::string, Client *, Client *);
	void createUser(Client *client);
	void setTopic(std::string topic);
	std::string getTopic();
};
