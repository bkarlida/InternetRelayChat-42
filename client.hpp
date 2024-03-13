#pragma once

# include "irc.hpp"
# include "server.hpp"


class Client
{
    private:
        std::string username;
        std::string password;
        std::string nickname;
        std::string realname;
};