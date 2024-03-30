/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arforgea <arforgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:46:18 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/30 16:40:54 by arforgea         ###   ########.fr       */
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

class Bot
{
    private:

        Bot(const Bot&);
        Bot&    operator=(const Bot&);
        
        std::string                 bot_chan;
        std::string                 bot_nick;
        std::string                 bot_user;
        std::string                 bot_name;
        std::string                 server_pass;
        std::string                 server_ip;
        int                         server_port;
        int                         server_socket;
        struct sockaddr_in          server_address;
        void                        _check_error(std::string flag);
        void                        _set_server_info(std::string ip, int port, std::string pass);
        void                        _set_bot_info(std::string nick, std::string user, std::string name);
        void                        _send_message(const std::string& message);
        size_t                      _find_second_occurrence(const std::string&, char);
        void                        _try_send_co();

        std::string	                _res_calcul;
        std::vector<std::string>	_calcul;   
        bool		                _parsing_nb(std::string);
		bool		                _parsing_verif(int);
		bool		                _check_precedence();
		std::string                 _re_transformation(long int);
        std::string                 _calculator_precedence(std::string);
        bool		                _calculator_classic();
		bool		                _parsing(std::string);
		bool		                _algo(std::string);
		bool		                _string_error();
		void		                _calcul_msg_to_string(std::string);

    public:
    
        Bot();
        ~Bot();

        const char          *get_ip();
        int                 get_server_socket();

        bool        parsing_input(int size, char **input);
        void        bot_connect(std::string to_channel);
        void        send_message(const std::string& message);
        void        handle_message(const std::string message);
        std::string receive_message(const int buffer_size);

};
