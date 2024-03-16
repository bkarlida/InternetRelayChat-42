
#ifndef CLIENT_HPP
#define CLIENT_HPP


#include "server.hpp"
//#include "Channel.hpp"
#include "Client.hpp"



class Channel;
class Client;

class Client
{
    private:
        std::string password;
        std::string username;
        std::string nickname;
        std::string realname;

    public:
        int socket_fd;
        sockaddr_in address;
        //std::vector <Channel> isjoined;
        bool isregister;
        std::string get_password();
        std::string get_username();
        std::string get_nickname();
        std::string get_realname();
        //std::vector <std::string> commands;

        std::string hostname;
        void set_password(std::string pass);
        void set_username(std::string user);
        void set_nickname(std::string nick);
        void set_realname(std::string real);

        int    get_joined(Client *ite);
        std::string getPrefix();


        Client(int fd, sockaddr_in addr);
};

#endif
