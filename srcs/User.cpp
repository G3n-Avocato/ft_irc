/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:14 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/04 01:19:26 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _init(0) {
	this->_end = 1;
	this->_nb_chan = 0;
}

User::~User() {
}

void	User::setNickname(std::string nick) {	
	this->_nickname = nick;	
}

void	User::setUsername(std::string usern) {
	this->_username = usern;
}

void	User::setInit(int init) {
	this->_init = init;	
}

void	User::setSocket(int socket) {
	this->_socket = socket;
}

void	User::setnbChan(int i) {
	this->_nb_chan += i;
}

void	User::setInviteChan(std::string invit) {
	std::vector<std::string>::iterator it = this->_channel_invit.begin();

	while (it != this->_channel_invit.end()) {
		if ((*it).compare(invit) == 0)
			break ;
		it++;
	}
	if (it == this->_channel_invit.end())
		_channel_invit.push_back(invit);
}

struct sockaddr_storage	User::getSockaddr() const {
	return (this->_sockaddr);
}

struct sockaddr_storage&	User::getRefSockaddr() {
	return (this->_sockaddr);
}

int	User::getSocket() const {
	return 	(this->_socket);
}

int	User::getInit() const {
	return (this->_init);
}

std::string	User::getNickname() const {
	return (this->_nickname);
}

std::string User::getUsername() const {
	return (this->_username);
}

bool	User::getcmdend() const {
	return (this->_end);
}

std::vector<std::vector<std::string> >	User::getvectorcmd() const {
	return (this->_cmd);
}

int		User::getnbChan() const {
	return (this->_nb_chan);
}

std::vector<std::string>	User::getlistChanInvite() const {
	return (this->_channel_invit);
}

void	User::clearvectorcmd() {
	this->_cmd.clear();
	this->_end = 1;
}

void	User::deleteinvitchan(std::string invit) {
	std::vector<std::string>::iterator	it = this->_channel_invit.begin();

	while (it != this->_channel_invit.end()) {
		if ((*it).compare(invit) == 0)
			break ;
		it++;
	}
	if (it != this->_channel_invit.end())
		this->_channel_invit.erase(it);
}
