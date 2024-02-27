/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:03 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/27 01:12:37 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #pragma once

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
		// void	_cmd_PART(std::vector<std::string>, User* client, Server*);
		// void	_cmd_PRIVMSG(std::vector<std::string>, User* client, Server*);
		void	_cmd_QUIT(std::vector<std::string>, User* client, Server*);
		// void	_cmd_WHO(std::vector<std::string>, User* client, Server*);
		// void	_cmd_KICK(std::vector<std::string>, User* client, Server*);
		// void	_cmd_INVITE(std::vector<std::string>, User* client, Server*);
		// void	_cmd_TOPIC(std::vector<std::string>, User* client, Server*);
		// void	_cmd_MODE(std::vector<std::string>, User* client, Server*);

		void	_send_data_to_client(std::string mess, User *user);
};
