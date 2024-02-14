/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:03 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/14 18:12:23 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>

class User;

class Command {
	public:
		Command();
		~Command();

		void	choose_cmds(const std::string, const User*); //para

	private:
		std::vector<std::string>	_l_c{"PASS", "NICK", "USER", "JOIN", "PART", "PRIVMSG", "QUIT", "WHO"};
		std::vector<std::string>	_l_cmdsop{"KICK", "INVITE", "TOPIC", "MODE"};
		// std::map<std::string, >
		std::map<std::string, void (Command::*)(std::string, const User*)>	_l_cmds;

		void	_cmd_PASS(const std::string, const User*);
		void	_cmd_NICK(const std::string, const User*);
		void	_cmd_USER(const std::string, const User*);
		void	_cmd_JOIN(const std::string, const User*);
		void	_cmd_PART(const std::string, const User*);
		void	_cmd_PRIVMSG(const std::string, const User*);
		void	_cmd_QUIT(const std::string, const User*);
		void	_cmd_WHO(const std::string, const User*);

		void	_cmd_KICK(const std::string, const User*);
		void	_cmd_INVITE(const std::string, const User*);
		void	_cmd_TOPIC(const std::string, const User*);
		void	_cmd_MODE(const std::string, const User*);
		
};
