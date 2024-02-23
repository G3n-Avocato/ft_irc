/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:03 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/21 18:07:46 by ecorvisi         ###   ########.fr       */
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

class Command {
	public:
		
		Command();
		~Command();

		void	choose_cmds(std::vector<std::vector<std::string> > cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		int		cmd_PASS(std::vector<std::string> cmd, std::string pass);

 	private:
		
		std::map<const std::string, void (Command::*)(std::vector<std::string>, User*, std::map<std::string, Channel*>*, std::vector<User*>*)>	_l_cmds;

		void	_cmd_NICK(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		// void	_cmd_USER(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		void	_cmd_JOIN(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		// void	_cmd_PART(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		// void	_cmd_PRIVMSG(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		// void	_cmd_QUIT(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		// void	_cmd_WHO(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		// void	_cmd_KICK(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		// void	_cmd_INVITE(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		// void	_cmd_TOPIC(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);
		// void	_cmd_MODE(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user);

		void	_send_data_to_client(std::string mess, User *user);
};
