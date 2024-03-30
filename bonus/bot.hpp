/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:46:18 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/29 19:11:20 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <fcntl.h>
#include <vector>
#include <climits>

class bot
{
    private:
        std::string                 bot_chan;
        std::string                 bot_nick;
        std::string                 bot_user;
        std::string                 bot_name;
        std::string                 server_pass;
        std::string	                _res_calcul;
		std::string                 _re_transformation(long int);
		std::string                 _calculator_precedence(std::string);
        std::string                 server_ip;
        std::vector<std::string>	_calcul;
        int                         server_port;
        int                         server_socket;
        struct sockaddr_in          server_address;
        bool		                _parsing_nb(std::string);
		bool		                _parsing_verif(int);
		bool		                _check_precedence();
		bool		                _calculator_classic();
		bool		                _parsing(std::string);
		bool		                _algo(std::string);
		bool		                _string_error();
		void		                _calcul_msg_to_string(std::string);

        int                         _stoi(std::string &s);

    public:
        bot();
        ~bot();

        const char          *get_ip();
        int                 get_server_socket();

        bool        parsing_input(int size, char **input);
        void        check_error(std::string flag);
        void        set_server_info(std::string ip, int port, std::string pass);
        void        set_bot_info(std::string nick, std::string user, std::string name);
        void        bot_connect(std::string to_channel);
        void        send_message(const std::string& message);
        void        handle_message(const std::string message);
        std::string receive_message(const int buffer_size);

};
