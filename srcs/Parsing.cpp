/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:03:06 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/23 15:39:07 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string> string_to_vector(std::string str, std::string arg){
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

void	hexchat_to_nc(std::vector<std::string>* raw_cmd) {
	int i = 0;
	
	for (std::vector<std::string>::iterator itf = raw_cmd->begin(); itf != raw_cmd->end(); itf++) {
		std::cout << i << " before = " << *itf << std::endl;
		i++;
	}
	std::vector<std::string>::iterator it = raw_cmd->begin();
	if (it->find("CAP LS") != std::string::npos)
		return ;
	else {
		if (raw_cmd->size() > 1) {
			it++;
			raw_cmd->erase(it, raw_cmd->end());
		}
	}

	int j = 0;
	
	for (std::vector<std::string>::iterator ite = raw_cmd->begin(); ite != raw_cmd->end(); ite++) {
		std::cout << j << " after = " << *ite << std::endl;
		j++;
	}
}

std::vector<std::vector<std::string> > Server::_cmdParser(char *client_buff){
    std::string 							buf(client_buff);
    std::vector<std::string>				raw_cmd;
    std::vector<std::vector<std::string> >	cmd_vector;

	//test enl;ver
	std::cout << "bufclient= " << client_buff << std::endl;

    raw_cmd = string_to_vector(buf, "\r\n");
	
	hexchat_to_nc(&raw_cmd);
    for (std::vector<std::string>::iterator it = raw_cmd.begin(); it != raw_cmd.end(); it++)
        cmd_vector.push_back(string_to_vector(*it, " "));
    return (cmd_vector);
}
