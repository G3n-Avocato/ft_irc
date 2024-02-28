/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:10 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/28 02:29:27 by lamasson         ###   ########.fr       */
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

		bool				setName(std::string name);
		void				setSubject(std::string str);
		void				setNewChanop(User* client);
		void				setNewUser(User* client);
		void				setFlagInvite(int b);
		bool				setPassword(std::string newpass, int b);
		void				setLimitUser(int nb);

		bool				getFlagInvite() const;
		bool				getFlagPass() const;
		bool				getFlagLimit() const;
		
		std::vector<User*>	getListUsers() const;
		int					getLimitUsers() const;
		std::string			getSubject() const;
		std::string			getName() const;
		std::vector<User*>	getListInvitUser() const;
		std::string			getPassword() const;

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

		std::vector<User*>			_list_invit; //list users with invit but not accepte yet
		
		bool						_parsing_name(std::string) const;
		bool						_parsing_mdp(std::string) const;
};
