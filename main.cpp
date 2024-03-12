#include "irc.hpp"
#include "server.hpp"

int main(int ac, char ** av)
{
    if (ac != 3)
    {
        std::cout << "Usage of IRC server: './ircserv <port> <password>'" << std::endl;
        return 1;
    }
    Server server(av[1], av[2]);

    server.createAndListen();
    std::cout << " - Server is listening now..." << std::endl;
}