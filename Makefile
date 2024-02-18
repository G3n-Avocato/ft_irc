# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 22:27:18 by lamasson          #+#    #+#              #
#    Updated: 2024/02/17 17:23:50 by ecorvisi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ./ircserv
CXX				= c++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -g3
RM				= rm -rf

SRC				=	srcs/main.cpp \
					srcs/Server.cpp \
					srcs/User.cpp \
					srcs/Command.cpp
					


OBJ				= ${SRC:%.cpp=%.o}

${NAME}: ${OBJ}
		@${CXX} ${CXXFLAGS} ${OBJ} -o ${NAME}

all:	${NAME}

clean:
		@${RM} ${OBJ}

fclean: clean
		@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
