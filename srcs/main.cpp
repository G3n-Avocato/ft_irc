/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:06:24 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/16 15:19:37 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	main(int argc, char **argv) {

	if (argc != 3)
		return (1);
	// try {
	Server	start(argv[1], argv[2]);
	// }
	// catch (std::exception &) {
		// std::cout << e.what();
	// }
	return (0);
}

/*
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#define PORT "9090"

//get sockaddr, IPV4 - IPV6 :
void	*get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int	main() {

	fd_set					main;
	fd_set					tmp;
	int						fdmax;

	int						listen_fd;
	int 					new_fd_acc;
	struct sockaddr_storage	client_addr;
	socklen_t				addrlen;

	char					buf_client[256];
	int						nbytes;

	char					remoteIP[INET6_ADDRSTRLEN];

	int						yes = 1;
	int	i;
	int	j;
	int	k;

	struct addrinfo hints;
	struct addrinfo *ai;
	struct addrinfo *p;

//clear fd set
	FD_ZERO(&main);
	FD_ZERO(&tmp);


	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	k = getaddrinfo(NULL, PORT, &hints, &ai);
	if (k != 0)
		exit(1);

	for (p = ai; p != NULL; p = p->ai_next) {
		
		listen_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listen_fd < 0)
			continue ;
		
		setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		if (bind(listen_fd, p->ai_addr, p->ai_addrlen) < 0) {
			close(listen_fd);
			continue ;
		}

		break ;
	}

	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		exit (2);
	}

	freeaddrinfo(ai);

	if (listen(listen_fd, 10) == -1) {
		perror("listen");
		exit(3);
	}

	FD_SET(listen_fd, &main);
	fdmax = listen_fd;

	while (1) {
		tmp = main; //copy
		if (select(fdmax + 1, &tmp, NULL, NULL, NULL) == -1) {
			perror("select");
			exit (4);
		}
		
		for (i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp)) {
				if (i == listen_fd) {
					addrlen = sizeof client_addr;
					new_fd_acc = accept(listen_fd, (struct sockaddr *)&client_addr, &addrlen);
					
					if (new_fd_acc == -1)
						perror("accept");
					else {
						FD_SET(new_fd_acc, &main);
						if (new_fd_acc > fdmax)
							fdmax = new_fd_acc;
						printf("server: new connection from %s on ""socket %d\n", inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr*)&client_addr), remoteIP, INET6_ADDRSTRLEN), new_fd_acc);
					}

				}
				else {
					
					nbytes = recv(i, buf_client, sizeof buf_client, 0);
					if (nbytes <= 0) {			
						if (nbytes == 0)
							printf("server: socket %d hung up \n", i);
						else
							perror("recv");
						
						close(i);
						FD_CLR(i, &main);
					}
					else {
						for (j = 0; j <= fdmax; j++) {
							if (FD_ISSET(j, &main)) {
								if (j != listen_fd && j != i) {
									if (send(j, buf_client, nbytes, 0) == -1)
										perror("send");
								}
							}
						}
					}
				}
			}
		}
	}
}
*/
