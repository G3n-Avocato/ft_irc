/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:14 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/02/26 16:42:11 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _init(0) {
	this->_end = 1;
}

User::~User() {
}

void User::setSocket(int socket) {
	this->_socket = socket;
}

void	User::setNickname(std::string nick) {	
	this->_nickname = nick;	
}

void User::setUsername(std::string usern) {
	this->_username = usern;
}

void User::setInit(int init) {
	this->_init = init;	
}

struct sockaddr_storage User::getSockaddr() const
{
	return (this->_sockaddr);
}

struct sockaddr_storage& User::getRefSockaddr() {
	return (this->_sockaddr);
}

int	User::getSocket() const {
	return 	(this->_socket);
}

std::string	User::getNickname() const {
	return (this->_nickname);
}

std::string User::getUsername() const {
	return (this->_username);
}

int	User::getInit() const {
	return (this->_init);
}

bool	User::getcmdend() const {
	return (this->_end);
}

std::vector<std::vector<std::string> >	User::getvectorcmd() const {
	return (this->_cmd);
}

void	User::clearvectorcmd() {
	this->_cmd.clear();
	this->_end = 1;
}

void	User::printcmdtest()  {
	for (size_t i = 0; i != this->_cmd.size(); i++) {
		for (size_t j = 0; j != this->_cmd[i].size(); j++)
			std::cout << i << " " << j << " " << this->_cmd[i][j] << std::endl;
	}
}
