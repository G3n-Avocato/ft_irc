/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:03:06 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/23 23:08:12 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string> string_to_vector(std::string str, std::string arg) {
    std::vector<std::string>    str_vector;
	std::string                 token;
	size_t                      pos = 0;

    while (str.length() > 0) {
        if((pos = str.find(arg.c_str())) == std::string::npos){
            pos = str.length();
        }
   	    token = str.substr(0, pos);
        str_vector.push_back(token);
        str.erase(0, pos + arg.length());
    }
    return (str_vector);
}

std::vector<std::vector<std::string> > Server::_cmdParser(char *client_buff){
    std::string 							buf(client_buff);
    std::vector<std::string>				raw_cmd;
    std::vector<std::vector<std::string> >	cmd_vector;


    raw_cmd = string_to_vector(buf, "\r\n");
    for (std::vector<std::string>::iterator it = raw_cmd.begin(); it != raw_cmd.end(); it++)
        cmd_vector.push_back(string_to_vector(*it, " "));
    return (cmd_vector);
}
