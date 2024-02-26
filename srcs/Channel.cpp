/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:56:29 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/26 21:58:53 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "User.hpp"

Channel::Channel(std::string name, User* client) {
	if (name.size() > 200) // ou 50 la RFC ce contredit 
		return ; //erreur
	//ajouter le parsing des names de join 
	this->_name = name;
	std::string	firstop = client->getUsername();
	this->_chanop.push_back(firstop);
	this->_users.push_back(client);
	
	this->_invite = 0;
	this->_password = 0;
	this->_limit = 0;

	this->_limit_user = -1;
}

Channel::~Channel() {
}

void	Channel::setName(std::string name) {
	//parsing name channel
	this->_name = name;
}

void	Channel::setSubject(std::string str) {
	//parsing sujet
	this->_subject = str;
}

void	Channel::setNewChanop(User *client) {
	std::string new_op = client->getUsername();
	this->_chanop.push_back(new_op);
}

void	Channel::setNewUser(User *client) {
	this->_users.push_back(client);
}

void	Channel::setFlagInvite(int b) {
	this->_invite = b;
}

void	Channel::setPassword(std::string newpass) {
	this->_password = 1;
	//parsing password
	this->_pass = newpass;
}

void	Channel::setLimitUser(int nb) {
	this->_limit = 1;
	this->_limit_user = nb;
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
