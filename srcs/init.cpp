/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:25:47 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/10 01:55:06 by lamasson         ###   ########.fr       */
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

void	Server::get_server_info() {
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

void	Server::bind_socket_to_port() {
	
	for (this->_cp_serv = this->_servinfo; this->_cp_serv != NULL; this->_cp_serv = this->_cp_serv->ai_next) {
		
		this->_fd_l = socket(this->_cp_serv->ai_family, this->_cp_serv->ai_socktype, this->_cp_serv->ai_protocol);
		if (this->_fd_l < 0)
			continue ;
		if (setsockopt(this->_fd_l, ))
	}

}
