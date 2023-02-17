# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 20:00:30 by rliu              #+#    #+#              #
#    Updated: 2023/02/17 20:51:48 by rliu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_container

CC 	= c++

CFLAGS 	= -Wall -Wextra -Werror -std=c++98 
IFLAGS  = -I. 

SRCS := ./TEST/main.cpp \
		./TEST/teststack.cpp \
		./TEST/testvector.cpp \
		./TEST/testmap.cpp \
		./TEST/testset.cpp


$(NAME): realcontainer mycontainer

OBJS := $(SRCS:%.cpp=%.o)
%.o: %.cpp
	${CC} ${CFLAGS} ${IFLAGS} -D TESTED_NAMESPACE=ft -c $< 

realcontainer :${OBJS} 
		$(CC) $(CFLAGS)${IFLAGS} -D TESTED_NAMESPACE=std  ${OBJS} -o std_container

mycontainer : ${OBJS} 
		$(CC) $(CFLAGS)${IFLAGS} -D TESTED_NAMESPACE=ft  ${OBJS} -o ft_container

clean: 
		rm -rf ${OBJS}
fclean:clean
		rm -rf std_container ft_container

all: $(NAME)

re: fclean all 

.PHONY: all fclean re