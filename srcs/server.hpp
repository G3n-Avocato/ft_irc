/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:21:00 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/10 18:15:32 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <sys/select.h>
#include <sys/types.h>
#include <netdb.h>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

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

		void			_get_server_info();

		int 			_fd_l;
		struct addrinfo *_cp_serv;

		void			_bind_socket_to_port();

		fd_set			_main;
		fd_set			_tmp;
		int				_fdmax;

		
};
