/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:10 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/03 03:14:49 by lamasson         ###   ########.fr       */
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
		void				setFlagInvite(bool);
		int					setPassword(std::string newpass, bool);
		void				setLimitUser(int nb);
		void				setFlagTopic(bool);

		bool				getFlagInvite() const;
		bool				getFlagPass() const;
		bool				getFlagLimit() const;
		bool				getFlagTopic() const;
		
		std::vector<User*>	getListUsers() const;
		std::vector<User*>	getListChanop() const;
		int					getLimitUsers() const;
		std::string			getSubject() const;
		std::string			getName() const;
		std::vector<User*>	getListInvitUser() const;
		std::string			getPassword() const;

		void				deleteUser(std::string);
		bool				deleteChanop(std::string);

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
		bool						_topic; //if true only op can change subject channel

		std::vector<User*>			_list_invit; //list users with invit but not accepte yet
		
		bool						_parsing_name(std::string) const;
		bool						_parsing_mdp(std::string) const;
};
