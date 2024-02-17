/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:36:58 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/17 16:18:07 by ecorvisi         ###   ########.fr       */
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

		void	setNickname(std::string nick);
		void	setUsername(std::string usern);
		void	setSocket(int socket);

		struct sockaddr_storage	getSockaddr() const;
		struct sockaddr_storage& getRefSockaddr();
		int						getSocket() const;
		std::string				getNickname() const;
		std::string				getUsername() const;

	private:
		
		User(const User&);
		User&	operator=(const User&);

		std::string	_nickname;
		std::string _username;

		struct sockaddr_storage 	_sockaddr;
		int							_socket;
		
		//list channel ?
};
