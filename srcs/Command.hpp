/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:03 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/15 23:47:54 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "Error.hpp"

class User;
class Channel;

class Command {
	public:
		
		Command();
		~Command();

		void	choose_cmds(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>* l_chan); //para channel ou server ?

	private:
		
		std::map<const std::string, void (Command::*)(std::vector<char*>, User*, std::map<Channel*, std::vector<User*>>*)>	_l_cmds;

		void	_cmd_PASS(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>*	l_chan);
		void	_cmd_NICK(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>*	l_chan);
		void	_cmd_USER(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>*	l_chan);
		void	_cmd_JOIN(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>*	l_chan);
		void	_cmd_PART(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>*	l_chan);
		void	_cmd_PRIVMSG(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>* l_chan);
		void	_cmd_QUIT(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>*	l_chan);
		void	_cmd_WHO(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>*	l_chan);
		void	_cmd_KICK(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>*	l_chan);
		void	_cmd_INVITE(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>* l_chan);
		void	_cmd_TOPIC(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>* l_chan);
		void	_cmd_MODE(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>* l_chan);

};
