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
        printErrExit("*** Hostname Error! ***", 1);
    return (hostname);
}

std::string Server::validatePassword(std::string const password)
{
    if (password.empty())
        printErrExit("*** Empty Password Error! ***", 1);
    return (password);
}

int Server::validatePort(const std::string& port)
{
    std::string::const_iterator it = port.begin();
    while (it != port.end() && std::isdigit(*it)) ++it;
    if (port.empty() || it != port.end())
        printErrExit("*** Port Error! ***", 1);
    return (std::stoi(port));
}

void Server::printErrExit(std::string message, int status)
{
    std::cerr << message << std::endl;
    exit (status);
}


// Member service functions
void Server::createAndListen(void)
{
    // Creating socket TCP and Stream type
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socket < 0)
        printErrExit("*** Socket Creation Error! ***", 1);

    // Setting options of the socket
    this->reuseOption = 1;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &this->reuseOption, 4) == -1)
        printErrExit("*** Socket Option Error! ***", 1);

    // Binding the socket
    this->_bind = bind(_socket, (sockaddr *)&socketAddress, sizeof(socketAddress));
    if (this->_bind)
        printErrExit("*** Binding Socket Error ***", 1);

    // Listening
    this->_listen = listen(this->_socket, 5);
    if (this->_listen)
        printErrExit("*** Listening Error! ***", 1);
    std::cout << " - Server is listening on port " << this->port << std::endl;
}

void Server::service(void)
{
    fd_set socket_fds, temp_socket_fds;
    int max_socket_fd, new_socket_fd;
    struct sockaddr_in clientAddress;
    socklen_t addressLen = sizeof(clientAddress);

    // Clearing socket fds and setting it as created socket descriptor
    FD_ZERO(&socket_fds);
    FD_SET(_socket, &socket_fds);
    max_socket_fd = this->_socket;

    while (true)
    {
        temp_socket_fds = socket_fds;

        if (select(max_socket_fd + 1, &temp_socket_fds, NULL, NULL, NULL))
        {
            std::cerr << "*** Select Function Error! ***" << std::endl;
            break ;
        }

        if (FD_ISSET(this->_socket, &temp_socket_fds))
        {
            if (new_socket_fd = accept(this->_socket, (struct sockaddr *)&clientAddress, &addressLen) == -1)
            {
                std::cerr << ""
            }
        } 
    }
    close (this->_socket);
}