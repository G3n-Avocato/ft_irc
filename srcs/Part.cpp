/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:32:19 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/02 17:34:03 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

void	Command::_cmd_PART(std::vector<std::string> cmd, User* client, Server* opt) {
	std::map<std::string, std::string>	parse;
	std::string							nomdp;
	if (cmd.size() < 2) {
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
		return ;
	}
	parse = this->_parsing_cmd_join(cmd[1], nomdp, client);
	
	std::map<std::string, Channel*> listchan = opt->getListChannel();
	for (std::map<std::string, std::string>::iterator itp = parse.begin(); itp != parse.end(); itp++) {
		std::map<std::string, Channel*>::iterator itchan = listchan.find(itp->first);
		if (itchan == listchan.end())
			this->_send_data_to_client(ERR_NOSUCHCHANNEL(client->getNickname(), itp->first), client);
		else if (itchan != listchan.end()) {
			std::string						name = client->getNickname();
			std::vector<User*>				chan_user = itchan->second->getListUsers();
			std::vector<User*>::iterator	itu = chan_user.begin();
			while (itu != chan_user.end()) {
				if (name.compare((*itu)->getNickname()) == 0)
					break ;
				itu++;
			}
			if (itu == chan_user.end())
				this->_send_data_to_client(ERR_NOTONCHANNEL(client->getNickname(), itp->first, "You're"), client);
			else {
				itchan->second->deleteUser(client->getNickname());
				itchan->second->deleteChanop(client->getNickname());
				client->setnbChan(-1);
				this->_send_data_to_client(RPL_PART(client->getNickname(), itp->first), client);
			}	
		}
	}
}
