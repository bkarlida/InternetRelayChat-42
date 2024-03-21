
#include "client.hpp"

Client::Client(int fd, sockaddr_in addr) : socket_fd(fd), address(addr)
{
    this->isRegistered = false;
    this->isPassed = false;
}

void    Client::set_password(std::string pass)
{
    password = pass;
}

void    Client::set_username(std::string user)
{
    username = user;
}

void    Client::set_nickname(std::string nick)
{
    nickname = nick;
}

void    Client::set_realname(std::string real)
{
    realname = real;
}

std::string  Client::get_password()
{
    return this->password;
}

std::string  Client::get_username()
{
    return this->username;
}

std::string  Client::get_nickname()
{
    return this->nickname;
}

std::string  Client::get_realname()
{
    return this->realname;
}

std::string Client::getPrefix()
{
    return ":" + this->get_nickname() + "!" + this->get_username() + "@" + this->hostname + ":";
}

int    Client::get_joined(Client *ite)
{
    for (std::vector<Channel>::iterator it = isjoined.begin(); it != isjoined.end(); it++)
    {
        if (it->ChannelName == ite->get_nickname())
            return 1;
    }
    return 0;
}
