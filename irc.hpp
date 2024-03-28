#pragma once

#define RPL_WELCOME(nickname, username) (":irc.example.com 001 " + nickname + " :Welcome to the IRC Network " + nickname + "!" + username + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) "332 " + nickname + " " + channel + " " + topic
#define RPL_NOTOPIC(nickname, channel) "331 " + nickname + " " + channel + " :No topic is set"
# define RPL_PONG(user_id, token) (user_id + " PONG " + token + "\r\n")
# define RPL_PRIVMSG(nick, username, target, message) (":" + nick + "!" + username + "@localhost PRIVMSG " + target + " " + message + "\r\n")
#define RPL_NAMREPLY(nickname, channel, nicknames) "353 " + nickname + " = " + channel + " :" + nicknames + "\r\n"
#define RPL_ENDOFNAMES(nickname, channel) "366 " + nickname + " " + channel + " :End of /NAMES list" + "\r\n"
# define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel" + "\r\n"
# define ERR_NOSUCHNICK(nickname) "401 " + nickname + " :No such nick/channel" + "\r\n"
# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost" + "\r\n")
# define RPL_NICK(oldnick, newnick) (":" + oldnick + " NICK " + newnick + "\r\n")
# define RPL_WHOREPLY(nickname, channel, user, host, server, nick, status, hopcount, realname) "352 " + nickname + " " + channel + " " + user + " " + host + " " + server + " " + nick + " " + status + " " + hopcount + " : " + realname + "\r\n"
# define RPL_ENDOFWHO(nickname, channel) "315 " + nickname + " " + channel + " :End of /WHO list" + "\r\n"
# define ERR_NEEDMOREPARAMS(cmd) (std::string("461 ") + cmd + " :Not enough parameter" + "\r\n")
# define ERR_NONICKNAMEGIVEN() ("431 :No nickname given\r\n")
# define ERR_NICKNAMEINUSE(nick) ("462 " + nick + " :Nickname is already in use" + "\r\n")
# define ERR_ERRONEUSNICKNAME(nick) ("432 " + nick + " :Erroneus nickname")
# define ERR_ALREADYREGISTRED() ("462 :The client is already registered\r\n")
# define ERR_NEEDREGISTER() ("462 :The client need to register. Use PASS and USER commands.\r\n")
# define ERR_PASSWDMISMATCH() ("462 :Password incorrect\r\n")
# define ERR_PASSWREQUIRED() ("462 :Password required to login\r\n")
# define ERR_WRONGPARAM() ("462 :Wrong amount parameters entered\r\n")
# define USERINFOADD() ("Server :Client informations updated\r\n")



class Client;
class Server;
class Channel;

# include <iostream>
# include <netinet/in.h>
# include <cstring>
# include <sys/socket.h> 
# include <arpa/inet.h>
# include <fstream>
# include <unistd.h>
# include <poll.h>
# include <vector>
# include <sstream>
# include "client.hpp"
# include <string>
# include "./command/command.hpp"

Client * getClientByFd(std::vector <Client> clients, int fd);
int 	commandInterface(std::string buffer, Client *client, std::vector <Client> clients);
void    handleBuffer(std::string buffer, Client *client, std::vector <Client> clients, Server * server, std::vector <Channel> *channels);