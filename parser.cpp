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
    if (iter->size() > 4 && iter->substr(0, 4) == "PASS")
        pass = iter->substr(6), iter++;
 
    if (iter->size() > 4 && iter->substr(0, 4) == "NICK")
        nick = iter->substr(5), iter++;
    else
        return 0;
    if (iter->size() > 4 && iter->substr(0, 4) == "USER")
    {
        user = iter->substr(5, iter->find(' ', 5) - 5);
        real = iter->substr(iter->find(':') + 5);
    }
    else
        return 0;
    if (!pass.empty() && pass.erase(pass.size() - 1) == server.getPassword())
        client->isRegistered = true, client->isPassed = true;
    client->set_username(user);
    client->set_nickname(nick);
    client->set_realname(real);
    std::cout << real << user << nick << std::endl;
    return 1;
}

void    commandParser(std::string buffer,std::vector<Client> clients,Client &ite)
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
            ite.commands.push_back(temp.substr(index, i - index));
    }
    for (const std::string& command : ite.commands) {
        std::cout << "$" << command << std::endl;
    }
 
 }

void commandSearch(std::vector<Client> clients, Client *ite, Server *server, std::vector <Channel> *channels)
{
    std::vector<std::string>::iterator k = ite->commands.begin();
    if ("PASS" == *k)
    {
       std::cout << "in pass" << std::endl; 
       pass(*ite, *server);
    }
    
}


void handleBuffer(std::string buffer, Client *client, std::vector <Client> clients, Server * server, std::vector <Channel> *channels)
{
    if (commandInterface(buffer, client, clients, *server))
    {
         std::cout << "command interface return" << std::endl;
         return ;
    }
    commandParser(buffer, clients, *client);
    commandSearch(clients, client, server, channels);
}

 