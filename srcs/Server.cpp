/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:25:47 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/30 18:30:15 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"
#include "../incs/Channel.hpp"
#include "../incs/utils.hpp"
#include <iostream>

Server::Server(const char *port, const std::string password) : _port(port) , _password(password) {
	this->_get_server_info();
	this->_bind_socket_to_port();
	this->_config_wait_fd_co();
}

Server::~Server() {
	freeaddrinfo(this->_servinfo);

	std::vector<User *>listuser = this->getListUser();
	for (std::vector<User *>::iterator it = listuser.begin(); it != listuser.end(); it++) {
		close((*it)->getSocket());
		FD_CLR((*it)->getSocket(), &this->_setRead);
		FD_CLR((*it)->getSocket(), &this->_main);
		delete *it;
	}

	std::map<std::string, Channel*>	listchannel = this->getListChannel();
	for (std::map<std::string, Channel*>::iterator itc = listchannel.begin(); itc != listchannel.end(); itc++) {
		delete itc->second;
	}
	close(this->_fd_l);
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
		throw std::logic_error("Close server.\n");
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
			freeaddrinfo(this->_servinfo);
			throw std::logic_error("Close server.\n");
		}
		if (bind(this->_fd_l, this->_cp_serv->ai_addr, this->_cp_serv->ai_addrlen) < 0) {
			close(this->_fd_l);
			continue ;
		}
		break ;
	}
	if (this->_cp_serv == NULL) {
		fprintf(stderr, "serverinfo: failed to bind\n");
		freeaddrinfo(this->_servinfo);
		throw std::logic_error("Close server.\n");
	}
}

void	Server::_config_wait_fd_co() {
	FD_ZERO(&this->_main);
	FD_ZERO(&this->_setRead);

	if (listen(this->_fd_l, 10) == -1) {
		perror("listen");
		freeaddrinfo(this->_servinfo);
		throw std::logic_error("Close server.\n");
	}

	FD_SET(this->_fd_l, &this->_main);
	FD_SET(this->_fd_l, &this->_setRead);
	this->_fdmax = this->_fd_l;

}

void	Server::start_server_select() {

	while (1) {
		this->_setRead = this->_main;
		if (select(this->_fdmax + 1, &this->_setRead, NULL, NULL, NULL) == -1) {
			perror("select");
			throw std::logic_error("Close server.\n");
		}
		for (i = 0; i <= this->_fdmax; i++) {
			if (FD_ISSET(i, &this->_setRead)) {
				if (i == this->_fd_l)
					this->_accept_connect_client();
				else 
					this->_recv_send_data();
			}
		}
	}
}

void	Server::_accept_connect_client() {
	User		*newclient = new User();
	socklen_t	addrlen = sizeof newclient->getSockaddr();
	
	std::cout << "----------NEW CONNECTION----------" << std::endl;
	
	char		remoteIP[INET6_ADDRSTRLEN];
	
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
    for (std::vector<User*>::const_iterator it = users.begin(); it != users.end(); it++) {
        std::cout << "User Socket: " << (*it)->getSocket() << std::endl;
        std::cout << "User Nickname: " << (*it)->getNickname() << std::endl;
        std::cout << "User Username: " << (*it)->getUsername() << std::endl; //bizarre
        std::cout << "User init int: " << (*it)->getInit() << std::endl;
    }
}

void	Server::_recv_send_data() {
	int nbytes = recv(i, this->_buf_client, sizeof this->_buf_client - 1, 0);
	this->_buf_client[nbytes] = '\0';
	
	std::cout << "----------NEW INPUT----------" << std::endl << std::endl;
	std::cout << "INPUT = " << nbytes << " = " << _buf_client << std::endl << std::endl;
	
	std::vector<User*>::iterator itu = this->_find_client_socket_to_i();
	(*itu)->setcmdParser(this->_buf_client);
	if (nbytes <= 0) {
		if (nbytes == 0)
		{
			printf("server: socket %d hung up\n", i);
			for (std::vector<User*>::iterator it = _l_user.begin(); it != _l_user.end(); ++it)
			{
				if ((*it)->getSocket() == i)
					this->_delete_user_all_chan((*it)->getNickname());
			}
			deleteUser(i, 0);
		}
		else
	 		perror("recv");
		close(i);
		FD_CLR(i, &this->_setRead);
		FD_CLR(i, &this->_main);
	}
	else if ((*itu)->getcmdend()) {
		if (FD_ISSET(i, &this->_main) && i != this->_fd_l) {
			itu = this->_find_client_socket_to_i();
			this->_bible.choose_cmds((*itu), this);
			for (std::vector<User*>::iterator ite = this->_l_user.begin(); ite != this->_l_user.end(); ite++)
			{
				if ((*ite)->getSocket() == i)
					(*itu)->clearvectorcmd();
			}
			_printUsers(_l_user);
		}
	}
}

std::vector<User*>::iterator	Server::_find_client_socket_to_i() {
	std::vector<User*>::iterator it = this->_l_user.begin();

	while (it != this->_l_user.end()) {
		if ((*it)->getSocket() == i)
			break ;
		it++;
	}
	return (it);
}

std::vector<User*>	Server::getListUser() const {
	return (this->_l_user);
}

std::map<std::string, Channel*>	Server::getListChannel() const {
	return (this->_l_channel);
}

void	Server::setListChannel(Channel *channel) {
	std::string	name = channel->getName();
	this->_l_channel[name] = channel;
}

void	Server::setListUser(User* client) {
	this->_l_user.push_back(client);
}

void	Server::deleteChannel(const std::string name) {
	std::map<std::string, Channel*>::iterator it = this->_l_channel.find(name);
	if (it != this->_l_channel.end()) {
		delete it->second ;
		this->_l_channel.erase(it);
	}
}

std::string	Server::getPass() const {
	return (this->_password);
}

void	Server::deleteUser(int socket, int cas) {	
	for (std::vector<User*>::iterator it = _l_user.begin(); it != _l_user.end(); ++it)
	{
		if ((*it)->getSocket() == socket)
		{
			delete *it;
			this->_l_user.erase(it);
			if (cas == 1) {
				FD_CLR(socket, &this->_setRead);
				FD_CLR(socket, &this->_main);
				close(socket);
			}
			if (socket == this->_fdmax)
				this->_fdmax -= 1;
			break;
		}
	}
}

void	Server::_delete_user_all_chan(std::string name) {
	std::vector<std::string>	del_chan;
	for (std::map<std::string, Channel*>::iterator it = _l_channel.begin(); it != _l_channel.end(); it++) {
		std::vector<User*> listuser = it->second->getListUsers();
		std::vector<User*>::iterator ituser;
		for (ituser = listuser.begin(); ituser != listuser.end(); ituser++) {
			if ((*ituser)->getNickname().compare(name) == 0)
				break;
		}
		if (ituser != listuser.end()) {
			this->_bible.sendMsgtoUserlist(listuser, RPL_QUIT(name, "Leaving"));
			it->second->deleteUser(name);
			it->second->deleteChanop(name);
			if (listuser.size() == 1)
				del_chan.push_back(it->second->getName());
		}
	}
	for (std::vector<std::string>::iterator del = del_chan.begin(); del != del_chan.end(); del++)
		this->deleteChannel(*del);
}
