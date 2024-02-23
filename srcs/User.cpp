/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:14 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/02/20 17:59:40 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : _init(0)
{
	
}

User::~User()
{

}

void User::setSocket(int socket)
{
	_socket = socket;
}

void	User::setNickname(std::string nick)
{	
	_nickname = nick;
	
}

void User::setUsername(std::string usern)
{
	_username = usern;
}

void User::setInit(int init)
{
	_init = init;	
}

struct sockaddr_storage User::getSockaddr() const
{
	return _sockaddr;
}

struct sockaddr_storage& User::getRefSockaddr()
{
	return _sockaddr;
}

int	User::getSocket() const
{
	return 	(_socket);
}

std::string	User::getNickname() const
{
	return _nickname;
}

std::string User::getUsername() const
{
	return _username;
}

int	User::getInit() const
{
	return _init;
}
