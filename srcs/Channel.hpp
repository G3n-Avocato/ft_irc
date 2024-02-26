/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:10 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/26 19:00:30 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>

class User;

class Channel {
	public:
		
		Channel(std::string name, User* client);
		~Channel();

		void				setName(std::string name);
		void				setSubject(std::string str);
		void				setNewChanop(User* client);
		void				setNewUser(User* client);
		void				setFlagInvite();
		void				setPassword(std::string newpass); //pass + bool
		void				setLimitUser(int nb); // nb + bool

		bool				getFlagInvite() const;
		bool				getFlagPass() const;
		bool				getFlagLimit() const;
		std::vector<User*>	getListUsers() const;

	private:

		Channel();
		Channel(const Channel&);
		Channel&			operator=(const Channel&);
		
		std::string					_name;
		std::string					_subject;
		std::vector<std::string>	_chanop;
		std::vector<User*>			_users;
		std::string					_pass;
		int							_limit_user;

		bool						_invite;
		bool						_password;
		bool						_limit;

		std::vector<User*>			_users_invite; // potentiel list des users qui ont recu une invitation mais pas encore accepte
};
