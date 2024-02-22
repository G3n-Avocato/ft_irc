/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:03:06 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/22 17:00:48 by lamasson         ###   ########.fr       */
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
        // std::cout << YELLOW << "Server receive CMD: " << RESET << token << std::endl;
        str.erase(0, pos + arg.length());
    }
    return (str_vector);
}

void	hexchat_to_nc(std::vector<std::string>* raw_cmd) {
	int i = 0;
	
	for (std::vector<std::string>::iterator it = raw_cmd->begin(); it != raw_cmd->end(); it++) {
		std::cout << i << " pos = " << *it << std::endl;
		i++;
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

    int raw_cmd_size = raw_cmd.size();
    int i = 0;
    std::vector<std::string>::iterator it = raw_cmd.begin();
    while (i < raw_cmd_size){
        cmd_vector.push_back(string_to_vector(*it, " "));
        it++;
        i++;
    }
    return (cmd_vector);
}
