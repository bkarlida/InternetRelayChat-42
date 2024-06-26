#pragma once

# include "irc.hpp"
# include "channel.hpp"

class Server
{
    private:
        // Server variables
        const std::string hostname;
        const std::string password;
        const int port;

        // Socket variables
        struct sockaddr_in socketAddress;
        int _socket;
        int _bind;
        int _listen;

        // Private functions
        std::string validatePassword(std::string const password);
        int validatePort(const std::string& port);
        void printErrExit(std::string message, int status);
    
    public:
        std::string hostnameHelper(void);
        std::string getPassword(void);
        std::vector <Channel> channels;
        Server(std::string port, std::string password);

        void createAndListen(void);
        void service(void);

};