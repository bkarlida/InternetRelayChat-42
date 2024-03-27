#include "client.hpp"
#include "server.hpp"
int commandInterface(std::string buffer, Client *client, std::vector <Client> clients, Server &server)
{
    std::string pass;
    std::string nick;
    std::string user;
    std::string real;
    std::stringstream stringStream(buffer);
    std::vector <std::string> splitStrings;
    for (std::string line; std::getline(stringStream, line, '\n'); )
        splitStrings.push_back(line);
    std::vector <std::string>::iterator iter = splitStrings.begin();
    if (splitStrings.size() < 2)
        return 0;
    if (iter->size() > 4 && iter->substr(0, 4) == "PASS")
        pass = iter->substr(6, iter->find(13, 6) - 6), iter++;
 
    if (iter->size() > 4 && iter->substr(0, 4) == "NICK")
        nick = iter->substr(5, iter->find(13, 5) - 5), iter++;

    if (iter->size() > 4 && iter->substr(0, 4) == "USER")
    {
        user = iter->substr(5, iter->find(' ', 5) - 5);
        real = iter->substr(iter->find(':') + 5);
    }

    if (pass == server.getPassword())
    {
        client->isPassed = true;
        send(client->socket_fd, "Server: Password is correct.\r\n", 30, 0);
    }
    // else if (!pass.empty())
    // {
    //     std::string err = ERR_PASSWDMISMATCH();
    //     size_t lenght = err.length();
    //     send(client->socket_fd, err.c_str(), lenght, 0);
    // }
    // else
    // {
    //     std::string err = ERR_PASSWREQUIRED();
    //     size_t lenght = err.length();
    //     send(client->socket_fd, err.c_str(), lenght, 0);
    // }
    if (client->get_username().empty() && !user.empty())
        client->set_username(user);
    if (client->get_nickname().empty() && !nick.empty())
        client->set_nickname(nick);
    if (client->get_realname().empty() && !real.empty())
        client->set_realname(real.erase(real.size() - 1));
    return 1;
}

void    commandParser(std::string buffer,std::vector<Client> clients,Client * client)
{
    int a;
    if (buffer[buffer.length() - 2] == '\r')
        a = buffer.length() - 2;
    else
        a = buffer.length() - 1;
    std::string temp = buffer.substr(0,a);
    int index;
    int flag;
    for(int i = 0; i < a; i++)
    {
        flag = 0;
        while (temp[i] == ' ' && i < a)
            i++;
        if (i < a)
            index = i;
        while (temp[i] != ' ' && i < a)
        {
            flag = 1;
            i++;
        }
        if (flag == 1)
            client->commands.push_back(temp.substr(index, i - index));
    }

    for (const std::string& command : client->commands) {
        std::cout << "$" << command << std::endl;
    }
 
 }

void commandSearch(std::vector<Client> clients, Client *ite, Server *server, std::vector <Channel> *channels)
{
    std::cout << "commandSearch"<<"userName: " + ite->get_username() << "\nrealName" + ite->get_realname()<< std::endl;
    std::vector<std::string>::iterator k = ite->commands.begin();
    if ("PASS" == *k)
    {
       pass(ite, server);
    }
    else if ("USER" == *k )
    {
        user(clients, *ite, *server);
    }
    else if (!ite->isRegistered)
    {
        return ;
    }
    else if ("NICK" == *k )
    {
        nick(clients, *ite, *server, *channels);
    }
}


void handleBuffer(std::string buffer, Client *client, std::vector <Client> clients, Server * server, std::vector <Channel> *channels)
{
    if (!client->isPassed && commandInterface(buffer, client, clients, *server))
    {
        std::cout << "command interface return" << std::endl;
        return ;
    }
    commandParser(buffer, clients, client);
    commandSearch(clients, client, server, channels);
}
