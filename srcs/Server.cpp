/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:25:47 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/23 23:14:16 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Error.hpp"
#include <iostream>


Server::Server(const char *port, const char *password) : _port(port) , _password(password) {
// parsing port et password
	(void)this->_password;
	
	this->_get_server_info();
	this->_bind_socket_to_port();
	this->_config_wait_fd_co();
	this->_start_server_select();

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
	User		*newclient = new User();
	socklen_t	addrlen = sizeof newclient->getSockaddr();
	
	std::cout << "----------NEW CONNECTION----------" << std::endl;
	
	char		remoteIP[INET6_ADDRSTRLEN];

//	struct sockaddr_storage	test;
//	socklen_t	len = sizeof test;
	
	newclient->setSocket(accept(this->_fd_l, (struct sockaddr*)(&newclient->getRefSockaddr()), &addrlen));
	
	if (newclient->getSocket() == -1)
		perror("accept");
	else {
		if (newclient->getSocket() > this->_fdmax)
			this->_fdmax = newclient->getSocket();
		FD_SET(newclient->getSocket(), &this->_main);
		printf("serverinfo: new connection from %s on ""socket %d\n", inet_ntop(newclient->getSockaddr().ss_family, this->_get_in_addr((struct sockaddr*)(&newclient->getRefSockaddr())), remoteIP, INET6_ADDRSTRLEN), newclient->getSocket());
	}
	_l_user.push_back(newclient);
	
}

void*	Server::_get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void Server::_printUsers(std::vector<User*> users) {
    std::cout << "Printing all users:" << std::endl;
    for (std::vector<User*>::const_iterator it = users.begin(); it != users.end(); ++it) {
        std::cout << "User Socket: " << (*it)->getSocket() << std::endl;
        std::cout << "User Nickname: " << (*it)->getNickname() << std::endl;
    }
}

void	Server::_recv_send_data(int i) {
	int nbytes = recv(i, this->_buf_client, sizeof this->_buf_client - 1, 0);
	this->_buf_client[nbytes] = '\0';   ///////// GRACE A CETTE MERDE TOUT EST REGLEE POUR LA DATA EN TROP 

	if (nbytes <= 0) {
		if (nbytes == 0)
			printf("server: socket %d hung up\n", i);
		else
	 		perror("recv");
		close(i);
		FD_CLR(i, &this->_main);
	}
	else {
		std::cout << "----------NEW INPUT----------" << std::endl << std::endl;
		std::cout << "INPUT = " << _buf_client << std::endl << std::endl;
		this->_cmd = this->_cmdParser(this->_buf_client);
		if (FD_ISSET(i, &this->_main) && i != this->_fd_l) {
	 		std::vector<User*>::iterator it = this->_l_user.begin(); 
			while (it != this->_l_user.end()) {
				if ((*it)->getSocket() == i)
					break ;
				it++;
			}
			this->_bible.choose_cmds(this->_cmd, (*it), &_l_channel, &_l_user);
			this->_cmd.clear();
		}
	}
}

void	Server::_user_hub_test(User *user) {
	(void)user;	
	/*
	if (user->getInit() != 3)
	{
		std::cout << "------USER " << user->getSocket() << " INIT NOT FINISH------" << std::endl;
		for (unsigned long k = 0; k < _cmd.size(); k++)
		{
			std::cout << "cmd[" << k << "]: " << std::endl;
			for (unsigned long j = 0; j < _cmd[k].size(); j++)
			{	
				std::cout << this->_cmd[k][j] << std::endl;
			}
			
			
			//not finish yet
			//skip CAP LS
			if (_cmd[k][0] == "CAP")
				;
			else
			{
				switch (user->getInit()) {
					case 0:
						std::cout << "_cmd[k][0] == |" << _cmd[k][0] << "|" << std::endl;
						if (_cmd[k][0] == "PASS" || _cmd[k][0] == "PASS\n")						// HEXCHAT = PASS 1234 NC = PASS 1234\n
						{
							if (this->_bible.cmd_PASS(_cmd[k], std::string(_password)) == 0)
								user->setInit(1);
							break;
						}
						else
							std::cout << "NEED PASS" << std::endl;
						break;
					case 1:
						if (_cmd[k][0] == "NICK")
						{
							std::cout << "NICk CMD HERE" << std::endl;
							user->setInit(2);
							break;
						}
						else
							std::cout << "NEED NICK" << std::endl;
						break;
					case 2:
						if (_cmd[k][0] == "USER")
						{
							std::cout << "USER CMD HERE" << std::endl;
							user->setInit(3);
							break;
						}
						else
							std::cout << "NEED USER" << std::endl;
						break;
				}	
			}
			
		}
	
	}
	else
	{
		std::cout << "----------NEW CMD----------" << std::endl;
		this->_bible.choose_cmds(this->_cmd, user, &_l_channel, &_l_user);
		std::cout << "----------PRINT USER----------" << std::endl;
		this->printUsers(_l_user);
	}
	*/

}


