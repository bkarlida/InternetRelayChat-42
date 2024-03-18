#include "client.hpp"
#include "server.hpp"

void	commandInterface(std::string buffer, Client *client)
{
	int		i;
	int		index;

	i = 0;
	std::vector<std::string> commands;
	index = buffer.find('\n', i);
	int indexx = buffer.find('\n',(index + 1));
	while (index != std::string::npos)
	{
		commands.push_back(buffer.substr(i, index - i));
		i = index + 1;
		index = buffer.find('\n', i);
	}
	for (std::vector<std::string>::iterator y = commands.begin(); y != commands.end(); y++)
	{
		std::cout << "*" << *y << std::endl;
	}
	std::vector<std::string>::iterator iter = commands.begin();

	iter = commands.begin();
	i = 0;
	index = iter->find(':',i);
	//iter.set_password(iter->substr(index + 1, iter++->length() - 2));
	std::cout <<"*9"<<  iter->substr(index + 1, iter++->length() - 2)<<std::endl;


	i = 0;
	index = iter->find(' ',i);
	//iter.set_nickname(iter->substr(index + 1, iter++->length() - (index + 3)));
	std::cout <<"*6"<<  iter->substr(index + 1, iter++->length() - (index + 3))<<std::endl;

	i = 0;
	index = iter->find(' ',i);
	indexx = iter->find(' ',index + 1);
	//iter.set_username(iter->substr(index + 1, indexx - (index + 1)));
	std::cout <<"*5"<<  iter->substr(index + 1, indexx - (index + 1))<<std::endl;

	index = iter->find(':', indexx);
	//iter.set_realname(iter->substr(index + 1, (iter->length() - index) - 3));
	std::cout <<"*4"<<  iter->substr(index + 1, (iter->length() - index) - 3)<<std::endl;

}
