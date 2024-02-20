/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:38:11 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/20 23:38:40 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "User.hpp"

std::vector<std::string> string_to_vector_(std::string str, std::string arg) {
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
//cas ou ,#test 

std::string	parsing_cmd_mdp(std::string mdp) {
	size_t i = 0;
	std::string		mdp_ok;
	
	while (i < mdp.length()) {
		if (mdp[i] == '\0' || mdp[i] == '\r' || mdp[i] == '\n' || mdp[i] == '\f' || mdp[i] == '\t' || mdp[i] == '\v' || mdp[i] == ' ') {
			i--;
			break ;
		}
		i++;
	}
	if (i > 0)
		mdp_ok = mdp.substr(0, i);
	return (mdp_ok);
}


std::map<std::string, std::string>	parsing_cmd_join(std::string chan, std::string mdp) {
	std::vector<std::string>	j_chans = string_to_vector_(chan, ",");
	std::vector<std::string>	j_mdp = string_to_vector_(mdp, ",");
	size_t	i = 0;
	size_t j = 0;
	
	std::map<std::string, std::string>	join;
	std::string		chan_ok;
	while (i < j_chans.size()) {
		while (j != j_chans[i].length()) {
			if (j_chans[i][0] != '#' || j_chans[i][j] == '\0' || j_chans[i][j] == '\a' || j_chans[i][j] == '\n' || j_chans[i][j] == '\r' || j_chans[i][j] == ' ') {
				j--;
				break ;
			}
			j++;
		}
		if (j > 0) {
			chan_ok = j_chans[i].substr(0, j);
			if (i < j_mdp.size())
				join[chan_ok] = parsing_cmd_mdp(j_mdp[i]);
			else
				join[chan_ok];
		}
		i++;
	}
	return (join);
}

void	Command::_cmd_JOIN(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user) {
	(void)l_chan;
	(void)l_user;

	for (size_t i = 0; i != cmd.size(); i++)
		std::cout << "parsing1: " << cmd[i] << std::endl;
	if (cmd.size() < 2)
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getUsername(), cmd[0]), client);
	std::map<std::string, std::string> ok = parsing_cmd_join(cmd[1], cmd[2]);
	for (std::map<std::string, std::string>::iterator it = ok.begin(); it != ok.end(); it++) {
		std::cout << "parsing2: " << it->first << " ";
		if (!it->second.empty())
			std::cout << it->second << std::endl;
		else
			std::cout << std::endl;
	}

}
