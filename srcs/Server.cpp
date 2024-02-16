/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:25:47 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/17 00:51:21 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Error.hpp"

Server::Server(const char *port, const char *password) : _port(port) , _password(password) {
// parsing port et password
	(void)this->_password;
	
	this->_get_server_info();
	this->_bind_socket_to_port();
	this->_config_wait_fd_co();
	this->_start_server_select();

}

//Server::Server(const Server &src) {
//}

//Server&	Server::operator=(const Server &rhs) {
//}

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
		break ;
	}
	if (this->_cp_serv == NULL) {
		fprintf(stderr, "serverinfo: failed to bind\n");
		exit (2);
	}
}

void	Server::_config_wait_fd_co() {
	FD_ZERO(&this->_main);
	FD_ZERO(&this->_setRead);

	if (listen(this->_fd_l, 10) == -1) {
		perror("listen");
		exit (3);
	}

	FD_SET(this->_fd_l, &this->_main);
	FD_SET(this->_fd_l, &this->_setRead);
	this->_fdmax = this->_fd_l;

}

//verif password pas faite 
void	Server::_start_server_select() {
	int i;

	while (1) {
		this->_setRead = this->_main;
		if (select(this->_fdmax + 1, &this->_setRead, NULL, NULL, NULL) == -1) {
			perror("select");
			exit (4);
		}
		
		for (i = 0; i <= this->_fdmax; i++) {
			if (FD_ISSET(i, &this->_setRead)) {
				if (i == this->_fd_l)
					this->_accept_connect_client();
				else 
					this->_recv_send_data(i);
			}
		}
	}
}


void	Server::_accept_connect_client() {
	socklen_t	addrlen = sizeof this->_client_addr;
	char		remoteIP[INET6_ADDRSTRLEN];
	
	this->_fd_acc = accept(this->_fd_l, (struct sockaddr*)&this->_client_addr, &addrlen);
	std::cout << "fd " << this->_fd_acc << std::endl;
	if (this->_fd_acc == -1)
		perror("accept");
	else {
		FD_SET(this->_fd_acc, &this->_main);
		if (this->_fd_acc > this->_fdmax)
			this->_fdmax = this->_fd_acc;
		printf("serverinfo: new connection from %s on ""socket %d\n", inet_ntop(this->_client_addr.ss_family, this->_get_in_addr((struct sockaddr*)&this->_client_addr), remoteIP, INET6_ADDRSTRLEN), this->_fd_acc);
	}
}

void*	Server::_get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

#include <iostream>

void	Server::_recv_send_data(int i) {
/*	int	nbytes = recv(i, this->_buf_client, sizeof this->_buf_client, 0);
	//parsing buf_client, data send by client // return erreur si pb // passe direct a send 
	//si nopb // traiter l'info 
	if (nbytes <= 0) {
		if (nbytes == 0)
			printf("server: socket %d hung up\n", i);
		else
	 		perror("recv");
		close(i);
		FD_CLR(i, &this->_main);
	}
	else {
		if (FD_ISSET(i, &this->_main)) {
			if (i != this->_fd_l) {
				std::cout << "test send 2-3" << std::endl;
				if (send(i, this->_buf_client, nbytes, 0) == -1)
					perror("send");
			}
		}
	}*/
	this->_fct_de_test_dev_cmds_laura(i);
}

int	Server::_fct_de_test_dev_cmds_laura(int i) {

	int nbytes = recv(i, this->_buf_client, sizeof this->_buf_client, 0);
	std::cout << "nbytes= " << nbytes <<  std::endl;
	std::cout << "buf= " << this->_buf_client << std::endl;
	if (nbytes <= 0) {
		if (nbytes == 0)
			printf("server: socket %d hung up\n", i);
		else
	 		perror("recv");
		close(i);
		FD_CLR(i, &this->_main);
	}
	
	else {
	 // this->_cmd_split = this->ft_split(this->_buf_client); //envoyer a la classe cmd pour l'exec // l_channel adresse pour pouvoir la modif
	// this->_bible.choose_cmds(this->_cmd_split, User *client, &_l_channel) // peut etre appeler send depuis class cmd
		if (FD_ISSET(i, &this->_main)) {
			if (i != this->_fd_l) { //necessaire ??
				std::string client = "toi";
				std::string cmd = "debout";
				std::string err = ERR_NEEDMOREPARAMS(client, cmd);
				if (send(i, err.c_str(), strlen(err.c_str()), 0) == -1)
					perror("send");
			}
		}
	}

	return (nbytes);
}
