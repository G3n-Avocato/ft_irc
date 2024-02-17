/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:37:14 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/02/17 13:14:50 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User()
{
	
}

User::~User()
{

}

void User::setSocket(int socket)
{
	_socket = socket;
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

// void	User::setnickname(const char *nick)
// {
// 	if (strlen(nick) > 9)
// 	{
// 		std::cerr << "Nickname too long" << std::endl;
// 		return ;
// 	}
	
// 	char *tmp = new char[10];
// 	strcpy(_nickname, nick);
	
// }
