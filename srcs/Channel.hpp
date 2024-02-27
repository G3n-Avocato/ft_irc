/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:10 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/27 18:13:40 by lamasson         ###   ########.fr       */
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
		void				setFlagInvite(int b);
		void				setPassword(std::string newpass);
		void				setLimitUser(int nb);

		bool				getFlagInvite() const;
		bool				getFlagPass() const;
		bool				getFlagLimit() const;
		
		std::vector<User*>	getListUsers() const;
		int					getLimitUsers() const;
		std::string			getSubject() const;
		std::string			getName() const;

		void				deleteUser(std::string); //afaire
		void				deleteChanop(std::string); //afaire

	private:

		Channel();
		Channel(const Channel&);
		Channel&			operator=(const Channel&);
		
		std::string					_name;
		std::string					_subject;
		std::vector<User*>			_chanop;
		std::vector<User*>			_users;
		std::string					_pass;
		int							_limit_user;

		bool						_invite;
		bool						_password;
		bool						_limit;

		std::vector<User*>			_users_invite; //list users with invit but not accepte yet
};
