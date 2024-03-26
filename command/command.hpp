
#pragma once

# define RPL_PONG(user_id, token) (user_id + " PONG " + token + "\r\n")
# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost" + "\r\n")
# define RPL_WHOREPLY(nickname, channel, user, host, server, nick, status, hopcount, realname) "352 " + nickname + " " + channel + " " + user + " " + host + " " + server + " " + nick + " " + status + " " + hopcount + " : " + realname + "\r\n"
# define RPL_ENDOFWHO(nickname, channel) "315 " + nickname + " " + channel + " :End of /WHO list" + "\r\n"
# define ERR_NEEDMOREPARAMS(cmd) (std::string("461 ") + cmd + " :Not enough parameter" + "\r\n")
# define ERR_NONICKNAMEGIVEN() ("431 :No nickname given\r\n")
# define ERR_NICKNAMEINUSE(nick) ("433 * " + nick + " :Nickname is already in use" + "\r\n")
# define ERR_ERRONEUSNICKNAME(nick) ("432 " + nick + " :Erroneus nickname")

#include "../server.hpp"

class Client;
class Server;

void pass(Client * client, Server * server);
void user(std::vector<Client>& clients, Client& ite, Server& server);
void nick(std::vector<Client>& clients, Client& ite, Server& server, std::vector<Channel>& channels);


