/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:25:47 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/10 18:18:07 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server() {
}

Server::Server(const Server &src) {
}

Server&	Server::operator=(const Server &rhs) {
}

Server::~Server() {
}

void	Server::_get_server_info() {
	int status;

	memset(&this->_hints, 0, sizeof this->_hints);
	this->_hints.ai_family = AF_UNSPEC;
	this->_hints.ai_socktype = SOCK_STREAM;
	this->_hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo(NULL, this->_port, &this->_hints, &this->_servinfo);
	if (status != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit (1);
	}
	
}

void	Server::_bind_socket_to_port() {
	int yes = 1;

	for (this->_cp_serv = this->_servinfo; this->_cp_serv != NULL; this->_cp_serv = this->_cp_serv->ai_next) {
		
		this->_fd_l = socket(this->_cp_serv->ai_family, this->_cp_serv->ai_socktype, this->_cp_serv->ai_protocol);
		if (this->_fd_l < 0)
			continue ;
		if (setsockopt(this->_fd_l, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			perror("setsockopt");
			exit (1);
		}
		if (bind(this->_fd_l, this->_cp_serv->ai_addr, this->_cp_serv->ai_addrlen) < 0) {
			close(this->_fd_l);
			continue ;
		}
	}
	if (this->_cp_serv == NULL) {
		fprintf(stderr, "serverinfo: failed to bind\n");
		exit (2);
	}
}

void	Server::() {
	FD_ZERO(&this->_main);
	FD_ZERO(&this->_tmp);

	if (listen(this->_fd_l, 10) == -1) {
		perror("listen");
		exit (3);
	}

	FD_SET(this->_fd_l, &this->_main);
	this->_fdmax = this->_fd_l;

}
