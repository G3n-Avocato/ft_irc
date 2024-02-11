/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:21:00 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/11 18:42:07 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <sys/select.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>


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
		
		struct addrinfo			_hints;
		struct addrinfo			*_servinfo;
		const char				*_port;
		void					_get_server_info();

		int 					_fd_l;
		struct addrinfo 		*_cp_serv;
		void					_bind_socket_to_port();

		fd_set					_main;
		fd_set					_tmp;
		int						_fdmax;
		void					_config_wait_fd_co();

		void					_start_server_select();	

		int						_fd_acc;
		struct sockaddr_storage	_client_addr;
		char					_buf_client[256];
		void					_accept_connect_client();
		void					_recv_send_data(int i);

		void*					_get_in_addr(struct sockaddr *sa);
};
