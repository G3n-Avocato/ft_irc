/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:56:29 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/28 02:30:54 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "User.hpp"

Channel::Channel(std::string name, User* client) {
	this->_name = name;
	
	this->_chanop.push_back(client);
	this->_users.push_back(client);
	
	this->_invite = false;
	this->_password = false;
	this->_limit = false;

	this->_limit_user = -1;
}

Channel::~Channel() {
}

bool	Channel::setName(std::string name) {
	if (this->_parsing_name(name)) {
		this->_name = name;
		return (true);
	}
	return (false);
}

void	Channel::setSubject(std::string str) {
	//parsing sujet
	this->_subject = str;
}

void	Channel::setNewChanop(User *client) {
	this->_chanop.push_back(client);
}

void	Channel::setNewUser(User *client) {
	this->_users.push_back(client);
}

void	Channel::setFlagInvite(int b) {
	if (b == 1)
		this->_invite = true;
	else
		this->_invite = false;
}

bool	Channel::setPassword(std::string newpass, int b) {
	if (b == 1) {
		if (this->_parsing_mdp(newpass)) {
			this->_password = true;
			this->_pass = newpass;
			return (true);
		}
		else
			return (false);
	}
	else
		this->_password = false;
	return (true);
}

void	Channel::setLimitUser(int nb) {
	if (nb != -1) {
		this->_limit = true;
		this->_limit_user = nb;
	}
	else {
		this->_limit = false;
		this->_limit_user = -1;
	}
}

bool	Channel::getFlagInvite() const  {
	return (this->_invite);
}

bool	Channel::getFlagPass() const {
	return (this->_password);
}

bool	Channel::getFlagLimit() const {
	return (this->_limit);
}

std::vector<User*>	Channel::getListUsers() const {
	return (this->_users);
}

int		Channel::getLimitUsers() const {
	return (this->_limit_user);
}

std::string	Channel::getName() const {
	return (this->_name);
}

std::vector<User*>	Channel::getListInvitUser() const {
	return (this->_list_invit);
}

std::string	Channel::getPassword() const {
	return (this->_pass);
}

bool	Channel::_parsing_name(std::string name) const {
	if (name.length() > 200)
		return (false);
	for (size_t i = 0; i != name.length(); i++) {
		if (name[0] != '#' || name[i] == '\0' || name[i] == '\a' || name[i] == '\n' || name[i] == '\r' || name[i] == ' ')
			return (false);
	}
	return (true);
}

bool	Channel::_parsing_mdp(std::string mdp) const {
	if (mdp.length() < 23)
		return (false);
	for (size_t i = 0; i != mdp.length(); i++) {
		if (mdp[i] == '\0' || mdp[i] == '\r' || mdp[i] == '\n' || mdp[i] == '\f' || mdp[i] == '\t' || mdp[i] == '\v' || mdp[i] == ' ')
			return (false);
	}
	return (true);
}
