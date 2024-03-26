#include "client.hpp"
#include "server.hpp"
std::vector <std::string> commandSplitter(std::string buffer)
{
    std::stringstream stringStream(buffer);
    std::vector <std::string> splitStrings;
    for (std::string line; std::getline(stringStream, line, '\n'); )
        splitStrings.push_back(line);
    return splitStrings;
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
        std::string err = ERR_NEEDREGISTER();
        size_t lenght = err.length();
        send(ite->socket_fd, err.c_str(), lenght, 0);
        return ;
    }
}


void handleBuffer(std::string buffer, Client *client, std::vector <Client> clients, Server * server, std::vector <Channel> *channels)
{
    std::vector <std::string> allCommands = commandSplitter(buffer);
    for (std::vector<std::string>::iterator iter = allCommands.begin(); iter != allCommands.end(); iter++)
    {
        std::string line = *iter;
        commandParser(line, clients, client);
        commandSearch(clients, client, server, channels);
        client->commands.clear();
    }
}

 