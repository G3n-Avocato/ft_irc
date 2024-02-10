/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:21:00 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/10 01:38:23 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <sys/select.h>
#include <sys/types.h>
#include <netdb.h>

#include <cstring>
#include <cstdio>
#include <cstdlib>

class Server {
	
	public:
		
		Server();
		Server(const Server&);
		Server&	operator=(const Server&);
		~Server();

	private:
		
		struct addrinfo	_hints;
		struct addrinfo	*_servinfo;
		const char		*_port;

		int 			_fd_l;
		struct addrinfo *_cp_serv;
};
