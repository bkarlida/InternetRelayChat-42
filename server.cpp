#include "server.hpp"

// Constructor function
Server::Server(std::string port, std::string password)
: hostname(hostnameHelper()), password(password), port(validatePort(port))
{
    // Setting socket address parameters
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(this->port);
    socketAddress.sin_addr.s_addr = INADDR_ANY;

    std::cout << "hostname: " << this->hostname << "\nport: " << this->port << 
    "\npassword: " << this->password << std::endl;
}



// Helper functions
std::string Server::hostnameHelper(void)
{
    char hostname[1024];
    int hostError = gethostname(hostname, 1024);
    if (hostError == -1)
    {
        std::cerr << "*** Hostname Error! ***" << std::endl;
        exit (1);
    }
    return (hostname);
}

std::string Server::validatePassword(std::string const password)
{
    if (password.empty())
    {
        std::cerr << "*** Empty Password Error! ***" << std::endl;
        exit (1);
    }
    return (password);
}

int Server::validatePort(const std::string& port)
{
    std::string::const_iterator it = port.begin();
    while (it != port.end() && std::isdigit(*it)) ++it;
    if (port.empty() || it != port.end())
    {
        std::cerr << "*** Port Error! ***" << std::endl;
        exit (1);
    }
    return (std::stoi(port));
}


// Member service functions
void Server::createAndListen(void)
{
    // Creating socket TCP and Stream type
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socket < 0)
    {
        std::cerr << "*** Socket Creation Error! ***" << std::endl;
        exit (1);
    }

    // Setting options of the socket
    this->reuseOption = 1;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &this->reuseOption, 4) == -1)
    {
        std::cerr << "*** Socket Option Error! ***" << std::endl;
        exit (1);
    }

    // Binding the socket
    this->_bind = bind(_socket, (sockaddr *)&socketAddress, sizeof(socketAddress));
    if (this->_bind)
    {
        std::cerr << "*** Binding Socket Error ***" << std::endl;
        exit (1);
    }

    // Listening
    this->_listen = listen(this->_socket, 5);
    if (this->_listen)
    {
        std::cerr << "*** Listening Error! ***" << std::endl;
        exit (1);
    }
}