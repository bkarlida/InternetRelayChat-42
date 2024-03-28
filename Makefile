CPP = c++

FLAGS = -Wall -Werror -Wextra -std=c++98

NAME = ircserv

SRC = main.cpp server.cpp client.cpp parser.cpp utils.cpp command/command.cpp command/pass.cpp channel.cpp command/user.cpp command/nick.cpp command/join.cpp command/mode.cpp command/who.cpp command/topic.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CPP) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) $(OBJ)
re: clean all

.PHONY: clean all re
