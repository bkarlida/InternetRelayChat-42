#include "irc.hpp"
#include "server.hpp"
#include "client.hpp"

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
    int reuseOption = 1;
    if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &reuseOption, sizeof(int)) == -1)
        printErrExit("*** Socket Option Error! ***", 1);

    // Binding the socket
    this->_bind = bind(this->_socket, (struct sockaddr *)&this->socketAddress, sizeof(this->socketAddress));
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
    const int MAX_CLIENTS = 50;
    struct pollfd fds[MAX_CLIENTS + 1]; // +1 for listening socket
    struct sockaddr_in clientAddress;
    socklen_t addressLen = sizeof(clientAddress);
    std::vector<Client> clients;

    // Clearing socket fds and setting it as created socket descriptor
    fds[0].fd = _socket;
    fds[0].events = POLLIN;

    for (int i = 1; i < MAX_CLIENTS + 1; ++i)
    {
        fds[i].fd = -1;
        fds[i].events = POLLIN;
        fds[i].revents = 0;   // suspicious
    }

    while (true)
    {
        int activity = poll(fds, MAX_CLIENTS + 1, -1);
        if (activity == -1)
        {
            std::cerr << "*** Poll Function Error! ***" << std::endl;
            break;
        }

        // Check if listening socket has some activity
        if (fds[0].revents & POLLIN)
        {
            int new_socket_fd = accept(_socket, (struct sockaddr *)&clientAddress, &addressLen);
            if (new_socket_fd == -1)
            {
                std::cerr << "*** Accept Function Error! ***" << std::endl;
                break;
            }
            else
            {
                if (clients.size() >= MAX_CLIENTS)
                {
                    std::cout << " - Maximum client size reached\n";
                    // ! check notes for this job!
                }
                else
                {
                    std::cout << " - New connection from " << inet_ntoa(clientAddress.sin_addr) << " on socket " << new_socket_fd << std::endl;

                    // Creat new client element and push to vector
                    clients.push_back(Client(new_socket_fd, clientAddress));


                    // Add new socket to fds array
                    for (int i = 1; i < MAX_CLIENTS + 1; ++i)
                    {
                        if (fds[i].fd == -1)
                        {
                            fds[i].fd = new_socket_fd;
                            break;
                        }
                    }
                }
            }
        }

        // Check for IO operation on existing sockets
        for (int i = 1; i < MAX_CLIENTS + 1; ++i)
        {
            if (fds[i].fd != -1 && fds[i].revents & POLLIN)
            {
                char buffer[1024];
                int bytes_recieved = recv(fds[i].fd, buffer, sizeof(buffer), 0);

                if (bytes_recieved <= 0)
                {
                    if (bytes_recieved == 0)
                        std::cout << " - Connection closed on socket " << fds[i].fd << std::endl;
                    else
                        std::cerr << "*** Recv Function Error! ***" << std::endl;

                    clients.erase(clients.begin() + i - 1);
                    close(fds[i].fd);
                    for (int j = i; j < MAX_CLIENTS + 1; ++j) {
                        fds[j] = fds[j + 1];
                    }
                    fds[MAX_CLIENTS].fd = -1;
                }
                else
                {
                    buffer[bytes_recieved] = '\0';
                    handleBuffer(buffer, &clients[i -1], clients, this, &this->channels);
                    std::cout << " - Received data from socket " << fds[i].fd << ": #" << buffer << "#" << std::endl;
                    clients[i - 1].commands.clear();
                }
            }
        }
    }

    // Close listening socket
    close(_socket);
}


// Setter and Getter Functions
std::string Server::getPassword(void)
{ return (this->password); }