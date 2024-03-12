#include "irc.hpp"

int main(int ac, char ** av)
{
    if (ac != 3)
    {
        std::cout << "Usage of IRC server: './ircserv <port> <password>'" << std::endl;
        return 1;
    }
}