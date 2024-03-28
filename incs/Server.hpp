/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:21:00 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/02 17:17:55 by ecorvisi         ###   ########.fr       */
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
#include <map>

#include "User.hpp"
#include "Error.hpp"
#include "Command.hpp"
#include "utils.hpp"

class Channel;

class Server {
	
	public:
		
		Server(const char *port, const std::string password);
		~Server();

		void							setListChannel(Channel*);
		void							setListUser(User*);
		void							deleteChannel(std::string name);
		void							deleteUser(int socket, int cas);

		std::map<std::string, Channel*> getListChannel() const;
		std::vector<User*>				getListUser() const;
		std::string						getPass() const;

		void							start_server_select();

	private:

		Server(const Server&);
		Server&	operator=(const Server&);

		//server socket
		const char						*_port;
		const std::string				_password;

		struct addrinfo					_hints;
		struct addrinfo					*_servinfo;
		void							_get_server_info();

		int 							_fd_l;
		struct addrinfo 				*_cp_serv;
		void							_bind_socket_to_port();

		fd_set							_main;
		fd_set							_setRead;
		int								_fdmax;
		void							_config_wait_fd_co();


		int								i;
		char							_buf_client[513];
		void							_accept_connect_client();
		void*							_get_in_addr(struct sockaddr *sa);
		void							_recv_send_data();
		std::vector<User*>::iterator	_find_client_socket_to_i();
		//end
		
		Command									_bible; //bibliotheque des commandes de notre server
		std::vector<User*>						_l_user; //list user sur server
		std::map<std::string, Channel*>			_l_channel; //list channel

		void									_printUsers(std::vector<User*> users);
		
};
