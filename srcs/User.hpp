/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:36:58 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/26 18:27:46 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <vector>

class User {
	public:

		User();
		~User();

		void									printcmdtest();

		void									setNickname(std::string nick);
		void									setUsername(std::string usern);
		void									setInit(int init);
		void									setSocket(int socket);
		void									setcmdParser(char* client_buff);

		struct sockaddr_storage					getSockaddr() const;
		struct sockaddr_storage&				getRefSockaddr();
		int										getSocket() const;
		int										getInit() const;
		std::string								getNickname() const;
		std::string								getUsername() const;
		bool									getcmdend() const;
		std::vector<std::vector<std::string> >	getvectorcmd() const;

		void									clearvectorcmd();

	private:
		
		User(const User&);
		User&	operator=(const User&);

		std::string								_nickname;
		std::string 							_username;
		struct sockaddr_storage 				_sockaddr;
		int										_socket;
		int										_init; //indique a qu'elle endroit de l'enregistrement de l'user on est: 0 = aucune commande faite, 1 = PASS check, 2 = PASS + NICK, 3 = INIT FINI


		std::vector<std::string>				_string_to_vector(std::string, std::string, int);
		std::string								_recast_buf_end(std::vector<std::string>, std::string);
		
		std::vector<std::vector<std::string> >	_cmd;
		bool									_end;
		int										_nb_chan;
};
