/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:51:03 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/14 22:46:44 by lamasson         ###   ########.fr       */
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

		void	choose_cmds(const char**, const User*); //para channel ou server ?

	private:
		
		std::map<const std::string, void (Command::*)(const char**, const User*)>	_l_cmds;

		void	_cmd_PASS(const char**, const User*);
		void	_cmd_NICK(const char**, const User*);
		void	_cmd_USER(const char**, const User*);
		void	_cmd_JOIN(const char**, const User*);
		void	_cmd_PART(const char**, const User*);
		void	_cmd_PRIVMSG(const char**, const User*);
		void	_cmd_QUIT(const char**, const User*);
		void	_cmd_WHO(const char**, const User*);

		void	_cmd_KICK(const char**, const User*);
		void	_cmd_INVITE(const char**, const User*);
		void	_cmd_TOPIC(const char**, const User*);
		void	_cmd_MODE(const char**, const User*);
		
};
