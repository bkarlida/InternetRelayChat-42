#include "channel.hpp"

Channel::Channel(std::string name, Client *user, Client *admin)
{
    this->isTopic = false;
    this->topic = "";
    this->ChannelName = name;
    users.push_back(user);
    this->admin.push_back(admin);
}

void Channel::createUser(Client *client)
{
    this->users.push_back(client);
}

std::string Channel::getTopic()
{
    return this->topic;
}

void Channel::setTopic(std::string topic)
{
    size_t position;
    position = topic.find(':');

    if (position != std::string::npos)
    {
        std::string result = topic.substr(position + 1);
        this->topic = result;
    }
    else
        std::cerr << "error ':' not found" << std::endl;
}