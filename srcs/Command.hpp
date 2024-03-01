/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arforgea <arforgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:03 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/01 20:05:04 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <sys/socket.h>
#include <stdio.h>
#include <regex.h>

#include "Error.hpp"

class User;
class Channel;
class Server;

class Command {
	public:
		
		Command();
		~Command();

		void	choose_cmds(User* client, Server*);

 	private:
		
		std::map<const std::string, void (Command::*)(std::vector<std::string>, User*, Server*)>	_l_cmds;

		void	_cmd_PASS(std::vector<std::string>, User* client, Server*);
		void	_cmd_NICK(std::vector<std::string>, User* client, Server*);
		void	_cmd_USER(std::vector<std::string>, User* client, Server*);
		void	_cmd_JOIN(std::vector<std::string>, User* client, Server*);
		void	_cmd_PART(std::vector<std::string>, User* client, Server*);
		void	_cmd_PRIVMSG(std::vector<std::string>, User* client, Server*);
		void	_cmd_QUIT(std::vector<std::string>, User* client, Server*);
		// void	_cmd_WHO(std::vector<std::string>, User* client, Server*);
		// void	_cmd_KICK(std::vector<std::string>, User* client, Server*);
		// void	_cmd_INVITE(std::vector<std::string>, User* client, Server*);
		// void	_cmd_TOPIC(std::vector<std::string>, User* client, Server*);
		void	_cmd_MODE(std::vector<std::string>, User* client, Server*);

		//join.cpp - part.cpp
		std::map<std::string, std::string>	_parsing_cmd_join(std::string, std::string, User*);
		bool								_check_channel_users_limits(std::map<std::string, Channel*>::iterator, User*, std::string);
		bool								_check_channel_invite(std::map<std::string, Channel*>::iterator, User*, std::string);
		void								_sendMsgtoUserlist(std::vector<User*>, std::string);
		void								_sendJoinMsg(User*, Channel*);

		//mode.cpp
		bool								_flag_mode_check_exist(std::string, User*);
		void								_flag_mode_exec(std::vector<std::string>, User*, Server*);
		void								_mode_is(Channel*, User*, std::string, int);

		void								_send_data_to_client(std::string mess, User *user);
};
