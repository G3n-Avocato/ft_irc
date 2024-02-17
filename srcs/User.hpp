/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:36:58 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/17 13:14:46 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <cstring>
#include <sys/socket.h>

class User {
	public:

		User();
		~User();

		void	setnickname(const char *nick);
		void	setusername(const char *usern);
		void	sethostname(const char *host);
		void	setservname(const char *name);
		void	setSocket(int socket);

		struct sockaddr_storage	getSockaddr() const;
		struct sockaddr_storage& getRefSockaddr();
		int						getSocket() const;

	private:
		
		User(const User&);
		User&	operator=(const User&);

		char	_nickname[9];
		char	*_username;
		char	*_hostname;
		char	*_servname;
		
		struct sockaddr_storage 	_sockaddr;
		int							_socket;
		
		//list channel ?
};
