NAME= ft_containers
SRCS= mainmap.cpp
OBJS= $(SRCS:.cpp=.o)
CXX=c++
CXXFLAGS= -Werror -Wextra -Wall -std=c++98 

all : $(NAME)

$(NAME): $(OBJS)
	$(CXX) -g -fsanitize=address $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
