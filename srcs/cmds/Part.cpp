/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:32:19 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/03 02:32:03 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
#include "../../incs/Channel.hpp"

void	Command::_cmd_PART(std::vector<std::string> cmd, User* client, Server* opt) {
	std::map<std::string, std::string>	parse;
	std::string							tmp;
	if (cmd.size() < 2) {
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
		return ;
	}
	parse = this->_parsing_cmd_join(cmd[1], tmp, client);
	
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
				this->_send_data_to_client(ERR_NOTONCHANNEL(client->getNickname(), itp->first), client);
			else {
				std::vector<User*>	before = itchan->second->getListUsers();
				itchan->second->deleteUser(client->getNickname());
				itchan->second->deleteChanop(client->getNickname());
				client->setnbChan(-1);
				if (cmd.size() >= 3) {
					for (size_t i = 2; i < cmd.size(); i++) {
						tmp += cmd[i];
						if (i + 1 != cmd.size())
							tmp += " ";
					}
				std::string	msg = RPL_PART(client->getNickname(), client->getUsername(), itp->first, tmp);
				this->sendMsgtoUserlist(before, msg);
				tmp.clear();
				}
			}	
		}
	}
}
