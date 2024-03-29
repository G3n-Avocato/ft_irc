# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 22:27:18 by lamasson          #+#    #+#              #
#    Updated: 2024/03/29 15:47:52 by ecorvisi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ./ircserv
NAME_BOT		= ./bot
CXX				= c++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98
RM				= rm -rf

SRC				= srcs/main.cpp \
				  srcs/Server.cpp \
				  srcs/User.cpp \
				  srcs/Command.cpp \
				  srcs/Parsing.cpp \
				  srcs/cmds/Join.cpp \
				  srcs/cmds/Pass.cpp \
				  srcs/cmds/Nick.cpp \
				  srcs/cmds/Usercmd.cpp \
				  srcs/cmds/Quit.cpp \
				  srcs/Channel.cpp \
				  srcs/cmds/Privmsg.cpp \
				  srcs/cmds/Part.cpp \
				  srcs/cmds/Mode.cpp \
				  srcs/utils.cpp \
				  srcs/cmds/Topic.cpp \
				  srcs/cmds/Invite.cpp \
				  srcs/cmds/Kick.cpp

SRC_BOT			= bonus/main.cpp \
				  bonus/bot.cpp \
				  bonus/calcul_bot2.cpp			

OBJ				= ${SRC:%.cpp=%.o}

OBJ_BOT				= ${SRC_BOT:%.cpp=%.o}

${NAME}: ${OBJ}
		@${CXX} ${CXXFLAGS} ${OBJ} -o ${NAME}

${NAME_BOT}: ${OBJ_BOT}
		@${CXX} ${CXXFLAGS} ${OBJ_BOT} -o ${NAME_BOT}

all:	${NAME}

bot:	${NAME_BOT}

clean:
		@${RM} ${OBJ}
		@${RM} ${OBJ_BOT}

fclean: clean
		@${RM} ${NAME}
		@${RM} ${NAME_BOT}

re: fclean all

.PHONY: all clean fclean re bot
