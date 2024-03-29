
#pragma once

# define RPL_PONG(user_id, token) (user_id + " PONG " + token + "\r\n")
# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost" + "\r\n")
# define RPL_WHOREPLY(nickname, channel, user, host, server, nick, status, hopcount, realname) "352 " + nickname + " " + channel + " " + user + " " + host + " " + server + " " + nick + " " + status + " " + hopcount + " : " + realname + "\r\n"
# define RPL_ENDOFWHO(nickname, channel) "315 " + nickname + " " + channel + " :End of /WHO list" + "\r\n"
# define ERR_NEEDMOREPARAMS(cmd) (std::string("461 ") + cmd + " :Not enough parameter" + "\r\n")
# define ERR_NONICKNAMEGIVEN() ("431 :No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(nick) ("432 " + nick + " :Erroneus nickname")

#include "../server.hpp"
#include "command.hpp"

class Client;
class Server;

void pass(Client * client, Server * server);
void user(std::vector<Client>& clients, Client& ite, Server& server);
void nick(std::vector<Client>& clients, Client& ite, Server& server, std::vector<Channel>& channels);
int  isNickValid(Client & client, std::vector<Client> clients, std::string newNickName);
void sendmessage(Client &ite, std::string message);
void message_for_topic(Client &ite, std::string message);
void message_join(Client *ite, std::string message);
void join(std::vector<Client> clients, Client &ite, Server &server, std::vector <Channel> &channels);
void who(std::vector<Client> clients, Client ite, Server &server, std::vector <Channel> &channel);
void mode(std::vector<Client> clients, Client ite, Server &server, std::vector <Channel> channels);
void topic(std::vector<Client> &clients, Client &ite, Server &server, std::vector <Channel> &channels);



