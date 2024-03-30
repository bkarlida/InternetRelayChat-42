#include "irc.hpp"
#include "client.hpp"
int nickInUse(std::string buffer, std::vector<Client> clients)
{
    for (std::vector<Client>::iterator iter = clients.begin(); iter != clients.end(); iter++)
    {
        if (iter->get_nickname() == buffer)
            return 1;
    }
    return 0;
}
void handleNc(std::string buffer,std::vector<Client> clients,Client &it, Server & server)
{
    std::cout << "buffer: " << buffer << std::endl;
    char temp[1024];
    command:
    std::string pass = "Please enter the password: ";
    memset(temp, 0, sizeof(temp));
    send(it.socket_fd, pass.c_str() , pass.size(), 0);
    int bytes_received = recv(it.socket_fd, temp, sizeof(buffer), 0);
    if(temp[0])
    {
        std::string strTemp(temp);
        strTemp = strTemp.substr(0, strTemp.size() - 1);
        std::cout << "pass temp: " << strTemp << std::endl << "len: " << strTemp.size() << std::endl;
        if (strTemp == server.getPassword())
            it.isPassed = true;
        else
            goto command;
    }
    else
        goto command;
    command1:
    std::string nick = "Please enter the nickname: ";
    send(it.socket_fd, nick.c_str() , nick.size(), 0);
    memset(temp, 0, sizeof(temp));
    bytes_received = recv(it.socket_fd, temp, sizeof(buffer), 0);
    if(temp[0])
    {
        std::string strTemp(temp);
        strTemp = strTemp.substr(0, strTemp.size() - 1);
        std::cout << "nick temp: " << strTemp << std::endl;
        if (nickInUse(strTemp, clients))
        {
            std::string message = "*** Nick name is already in use!\n";
            send(it.socket_fd, message.c_str() , message.size(), 0);
            goto command1;
        }
        it.set_nickname(strTemp);
    }
    else
        goto command1;
    command2:
    std::string username =  "Please enter the username: ";
    memset(temp, 0, sizeof(temp));
    send(it.socket_fd, username.c_str() , username.size(), 0);
    bytes_received = recv(it.socket_fd, temp, sizeof(buffer), 0);
    if(temp[0])
    {
        std::string strTemp(temp);
        strTemp = strTemp.substr(0, strTemp.size() - 1);
        std::cout << "user temp: " << strTemp << std::endl;
        it.set_username(strTemp);
    }
    else
        goto command2;
    command3:
    std::string realname = "Please enter the realname: ";
    send(it.socket_fd, realname.c_str() , realname.size(), 0);
    memset(temp, 0, sizeof(temp));
    bytes_received = recv(it.socket_fd, temp, sizeof(buffer), 0);
    if(temp[0])
    {
        std::string strTemp(temp);
        strTemp = strTemp.substr(0, strTemp.size() - 1);
        std::cout << "real temp: " << strTemp << std::endl;
        it.set_realname(temp);
    }
    else
        goto command3;
    std::cout << "isRegister: " << it.isRegistered << std::endl << "Nick: " << it.get_nickname() << std::endl << "User: " << it.get_username() << std::endl << "Real: " << it.get_realname() << std::endl;
    it.isRegistered = true;
}