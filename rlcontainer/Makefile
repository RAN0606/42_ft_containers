# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 20:00:30 by rliu              #+#    #+#              #
#    Updated: 2023/02/20 17:01:39 by rliu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_container

CC 	= c++

CFLAGS 	= -Wall -Wextra -Werror -std=c++98 
IFLAGS  = -I. -I./TEST

$(NAME): mycontainer realcontainer	
# SRCS := ./TEST/main.cpp \
# 		./TEST/teststack.cpp \
# 		./TEST/testvector.cpp \
# 		./TEST/testmap.cpp \
# 		./TEST/testset.cpp
# mycontainer: ${SRCS} 
# 		$(CC) $(CFLAGS) ${IFLAGS} -D TESTED_NAMESPACE=ft ${SRCS} -o ft_container 
# realcontainer: ${SRCS} 
# 		$(CC) $(CFLAGS) ${IFLAGS} -D TESTED_NAMESPACE=std ${SRCS} -o std_container 

SRCS_FT = fttest_main.cpp
SRCS_STD = stdtest_main.cpp

%.o : %.cpp
		$(CC) $(CFLAGS) ${IFLAGS} $^ -c
OBJS_FT = ${SRCS_FT:.cpp=.o}       
OBJS_STD = ${SRCS_STD:.cpp=.o}

mycontainer: ${OBJS_FT} 
		$(CC) $(CFLAGS) ${IFLAGS} ${OBJS_FT} -o ft_container 

realcontainer: ${OBJS_STD} 
		$(CC) $(CFLAGS) ${IFLAGS} ${OBJS_STD} -o std_container 

test: ft_container std_container
	time ./std_container >stdresult; time ./ft_container>ftresult ; diff stdresult ftresult

clean: 
		rm -rf *.o stdresult ftresult
		
fclean:clean
		rm -rf std_container ft_container

all: $(NAME)

re: fclean all mycontainer realcontainer

.PHONY: all fclean re