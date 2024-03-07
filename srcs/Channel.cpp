/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:56:29 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/05 11:18:14 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "User.hpp"
#include "utils.hpp"

Channel::Channel(std::string name, User* client) {
	this->_name = name;
	
	this->_chanop.push_back(client);
	this->_users.push_back(client);
	
	this->_invite = false;
	this->_password = false;
	this->_limit = false;
	this->_topic = false;

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
	this->_subject = str;
}

void	Channel::setNewChanop(User *client) { 
	if (!vector_check_user(this->_chanop, client->getNickname()))
		this->_chanop.push_back(client);
}

void	Channel::setNewUser(User *client) {
	if (!vector_check_user(this->_users, client->getNickname()))
		this->_users.push_back(client);
}

void	Channel::setFlagInvite(bool b) {
	if (b)
		this->_invite = true;
	else
		this->_invite = false;
}

int	Channel::setPassword(std::string newpass, bool b) {
	if (b && this->_password) {
		return (467);
	}
	else if (!this->_parsing_mdp(newpass)) {
		return (461);
	}
	else if (b && !this->_password) {
		this->_password = true;
		this->_pass = newpass;
	}
	else if (!b && this->_password) {
		if (this->_pass.compare(newpass) == 0) {
			this->_password = false;
			this->_pass.clear();
		}
		else
			return (467);
	}
	return (0);
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
void	Channel::setListInvit(User* client) {
	if (!vector_check_user(this->_list_invit, client->getNickname()))
		this->_list_invit.push_back(client);
}

void	Channel::setFlagTopic(bool b) {
	if (b)
		this->_topic = true;
	else
		this->_topic = false;
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

bool	Channel::getFlagTopic() const {
	return (this->_topic);
}

std::vector<User*>	Channel::getListUsers() const {
	return (this->_users);
}

std::vector<User*>	Channel::getListChanop() const {
	return (this->_chanop);
}

int		Channel::getLimitUsers() const {
	return (this->_limit_user);
}

std::string	Channel::getSubject() const {
	return (this->_subject);
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
		if (name[0] != '#' || !syntax_name_channel(name[i]))
			return (false);
	}
	return (true);
}

bool	Channel::_parsing_mdp(std::string mdp) const {
	if (mdp.length() > 23)
		return (false);
	for (size_t i = 0; i != mdp.length(); i++) {
		if (!syntax_mdp_channel(mdp[i]))
			return (false);
	}
	return (true);
}

void	Channel::deleteUser(std::string name) {
	std::vector<User*>::iterator it_users = this->_users.begin();

	while (it_users != this->_users.end()) {
		if (name.compare((*it_users)->getNickname()) == 0)
			break ;
		it_users++;
	}
	if (it_users != this->_users.end())
		this->_users.erase(it_users);
}

bool	Channel::deleteChanop(std::string name) {
	std::vector<User*>::iterator it_chanop = this->_chanop.begin();
	
	while (it_chanop != this->_chanop.end()) {
		if (name.compare((*it_chanop)->getNickname()) == 0)
			break ;
		it_chanop++;
	}
	if (it_chanop != this->_chanop.end())
		this->_chanop.erase(it_chanop);
	else
		return (false);
	return (true);
}

void	Channel::deleteUserInvitList(std::string name) {
	size_t	i = vector_search_user(this->_list_invit, name);
	if (i < this->_list_invit.size()) {
		std::vector<User*>::iterator	pos = this->_list_invit.begin() + i;
		this->_list_invit.erase(pos);
	}
}
