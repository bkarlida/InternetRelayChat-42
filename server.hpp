#pragma once

# include "irc.hpp"

class Server
{
    private:
        // Server variables
        const std::string hostname;
        const std::string password;
        const int port;

        // Socket variables
        struct sockaddr_in socketAddress;
        int reuseOption;
        int _socket;
        int _bind;
        int _listen;

        // Private functions
        std::string hostnameHelper(void);
        std::string validatePassword(std::string const password);
        int validatePort(const std::string& port);
    
    public:
        Server(std::string port, std::string password);

        void createAndListen(void);

};