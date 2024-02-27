/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:38:11 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/27 18:07:49 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

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
		str.erase(0, pos + arg.length());
    }
    return (str_vector);
}

std::string	parsing_cmd_mdp(std::string mdp) {
	size_t i = 0;
	std::string		mdp_ok;
	
	while (i < mdp.length()) {
		if (mdp[i] == '\0' || mdp[i] == '\r' || mdp[i] == '\n' || mdp[i] == '\f' || mdp[i] == '\t' || mdp[i] == '\v' || mdp[i] == ' ') {
			break ;
		}
		i++;
	}
	if (i > 0)
		mdp_ok = mdp.substr(0, i);
	return (mdp_ok);
}


std::map<std::string, std::string>	parsing_cmd_join(std::string chan, std::string mdp) {
	std::vector<std::string>			j_chans = string_to_vector_(chan, ",");
	std::vector<std::string>			j_mdp;
	size_t								i = 0;
	size_t 								j = 0;
	std::map<std::string, std::string>	parse;
	std::string							chan_ok;

	if (!mdp.empty())
		j_mdp = string_to_vector_(mdp, ",");
	while (i < j_chans.size()) {
		while (!j_chans[i].empty() && j != j_chans[i].length()) {
			if (j_chans[i][0] != '#'|| j_chans[i][j] == '\0' || j_chans[i][j] == '\a' || j_chans[i][j] == '\n' || j_chans[i][j] == '\r' || j_chans[i][j] == ' ') {
				break ;
			}
			j++;
		}
		if (j > 0) {
			chan_ok = j_chans[i].substr(0, j);
			j = 0;
			if (!j_mdp.empty() && i < j_mdp.size())
				parse[chan_ok] = parsing_cmd_mdp(j_mdp[i]);
			else
				parse[chan_ok];
		}
		i++;
	}
	return (parse);
}

void	Command::_cmd_JOIN(std::vector<std::string> cmd, User* client, Server* opt) {
	std::map<std::string, std::string>	parse;
	std::string							mdp;
	
	if (cmd.size() < 2)
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getUsername(), cmd[0]), client);
	else if (cmd.size() != 2) //cas ou pas de mdp segfault	
		mdp = cmd[2];
	parse = parsing_cmd_join(cmd[1], mdp);

	/////////////////////////////////////////test2
	for (std::map<std::string, std::string>::iterator it = parse.begin(); it != parse.end(); it++) {
		std::cout << "parsing2: " << it->first << " size= " << it->first.size() << std::endl;
		if (!it->second.empty())
			std::cout << "mdp parsing 2: " << it->second << std::endl;
	}
	/////////////////////////////////////////////////
	
	std::map<std::string, Channel*>	listchan = opt->getListChannel(); // channel list
	std::map<std::string, std::string>::iterator itp = parse.begin(); // it sur cmd parse

	std::map<std::string, Channel*>::iterator itchan = listchan.find(itp->first); //cherche channel existant
	if (itchan == listchan.end()) {
		Channel	tmp(itp->first, client);
		opt->setListChannel(&tmp);
		

	}
	else if (itchan != listchan.end())
		;
}
