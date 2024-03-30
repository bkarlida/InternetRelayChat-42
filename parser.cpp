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
    std::cout << "last: " << (int)buffer[buffer.size() - 1] << " " << (int)buffer[buffer.size() - 2] << std::endl;
    int a;
    if (buffer[buffer.size() - 2] == 13)
        a = buffer.size() - 2;
    else
        a = buffer.size();
    std::string temp = buffer.substr(0,a);
    std::cout << "From parser: " << temp << " a: " << a << std::endl;
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

void commandSearch(std::vector<Client> clients, Client *ite, Server *server, std::vector <Channel> *channels, std::string buffer)
{
    std::vector<std::string>::iterator k = ite->commands.begin();
    std::cout << "commandSearch: " << *k << std::endl; 
    if ("PASS" == *k)
    {
       pass(ite, server);
    }
    else if ("USER" == *k )
    {
        user(clients, *ite, *server);
    }
    // else if (!ite->isRegistered)
    // {
    //     return ;
    // }
    else if ("NICK" == *k )
    {
        nick(clients, *ite, *server, *channels);
    }
    else if ("JOIN" == *k )
    {
        join(clients, *ite, *server, *channels);
    }
    else if ("WHO" == *k )
    {
        who(clients, *ite, *server, *channels);
    }
    else if ("MODE" == *k )
    {
        mode(clients, *ite, *server, *channels);
    }
    else if ("TOPIC" == *k )
    {
        topic(clients, *ite, *server, *channels);
    }
    else if ("PRIVMSG" == *k )
    {
        privmsg(clients, *ite, *channels, buffer);
    }
    else if ("CAP" == *k )
    {
        cap(clients, *ite, *server);
    }
    else if ("KICK" == *k )
    {
        kick(clients, *ite, *server, *channels);
    }
}

void handleBuffer(std::string buffer, Client *client, std::vector <Client> clients, Server * server, std::vector <Channel> *channels)
{
    std::cout << "buffer last 3: " << (int)buffer[buffer.size() - 1] << " " << (int)buffer[buffer.size() - 2] << " " << (int)buffer[buffer.size() - 3] << std::endl;
    if (buffer[buffer.size() - 2] != 13 && !client->isRegistered)
    {
        std::cout << "***from nc\n";
        handleNc(buffer, clients, *client, *server);
        return ;
    }
    std::vector <std::string> allCommands = commandSplitter(buffer);
    for (std::vector<std::string>::iterator iter = allCommands.begin(); iter != allCommands.end(); iter++)
    {
        std::string line = *iter;
        commandParser(line, clients, client);
        commandSearch(clients, client, server, channels, buffer);
        client->commands.clear();
    }
}
