
#include "command.hpp"

void mode(std::vector<Client> clients, Client ite, Server &server, std::vector <Channel> channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	std::string names;
	int flag = 0;
	for (std::vector<Channel>::iterator isadmin = channels.begin(); isadmin != channels.end(); isadmin++)
	{
		if(isadmin->ChannelName == k[1])
		{
			for (std::vector<Client *>::iterator c = isadmin->admin.begin(); c != isadmin->admin.end(); c++)
			{
				std::cout << isadmin->admin.size() << std::endl;
				if ((*c)->get_nickname() != ite.get_nickname())
					flag = 1;
			}
		}
	}
	if (flag)
		return;	

	if(k[2] == "+o")
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{

			if(itChannels->ChannelName == k[1])
			{
				names = '@' + k[3];
				sendmessage(ite, "Mode " + itChannels->ChannelName + " +o " +k[3]);
				itChannels->admin.push_back(&ite);
				for(std::vector <Client *>::iterator itera = itChannels->users.begin() ; itera != itChannels->users.end(); itera++)
				{
					(*itera)->set_nickname(names);
					message_join((*itera), RPL_NAMREPLY((*itera)->get_nickname(), k[1], names));
				}
			}
		}
	}
	else if(k[2] == "-o")
	{
for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
{
    if (itChannels->ChannelName == k[1])
    {
        int i = 0;
        for (std::vector<Client *>::iterator c = itChannels->admin.begin(); c != itChannels->admin.end();)
        {
            if ((*c)->get_nickname() == ite.get_nickname())
            {
                std::cout << "in erase mode -o" << std::endl;
                c = itChannels->admin.erase(c); // erase fonksiyonunun döndürdüğü geçerli konumu kullan
            }
            else
            {
                ++c; // Silinmeyen öğeleri geçmek için döngü değişkenini bir sonraki geçerli konuma ilerlet
            }
            i++;
        }
        sendmessage(ite, "Mode " + itChannels->ChannelName + " -o " + k[3]);
        for (std::vector<Client *>::iterator itera = itChannels->users.begin(); itera != itChannels->users.end(); itera++)
        {
            message_join((*itera), RPL_NAMREPLY((*itera)->get_nickname(), k[1], k[3]));
        }
    }
}

	}
}
