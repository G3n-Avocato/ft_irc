/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:10:49 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/04 02:25:37 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

void	Command::_cmd_INVITE(std::vector<std::string> cmd, User* client, Server* opt) {
	std::map<std::string, Channel*>				chan = opt->getListChannel();
	std::map<std::string, Channel*>::iterator	itchan;
	std::vector<User*>							user_serv = opt->getListUser();

	if (cmd.size() < 3) {
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
		return ;
	}
	itchan = chan.find(cmd[2]);
	if (!vector_check_user(user_serv, cmd[1]))
		this->_send_data_to_client(ERR_NOSUCHNICK(client->getNickname(), cmd[1]), client);
	else if (itchan == chan.end())
		this->_send_data_to_client(ERR_NOSUCHCHANNEL(client->getNickname(), cmd[2]), client);
	else if (itchan != chan.end()) {
		if (!vector_check_user(itchan->second->getListUsers(), client->getNickname()))
			this->_send_data_to_client(ERR_NOTONCHANNEL(client->getNickname(), cmd[2], "You're"), client);
		else if (!vector_check_user(itchan->second->getListChanop(), client->getNickname()))
			this->_send_data_to_client(ERR_CHANOPRIVSNEEDED(client->getNickname(), cmd[2]), client);
		else if (vector_check_user(itchan->second->getListUsers(), cmd[1]))
			this->_send_data_to_client(ERR_USERONCHANNEL(client->getNickname(), cmd[1], cmd[2]), client);
		else {
			size_t	i = vector_search_user(user_serv, cmd[1]);
			itchan->second->setListInvit(user_serv[i]);
			user_serv[i]->setInviteChan(cmd[2]);
			this->_send_data_to_client(RPL_INVITING(client->getNickname(), cmd[1], cmd[2]), client);
			this->_send_data_to_client(RPL_INVITE(client->getNickname(), cmd[1], cmd[2]), user_serv[i]);
		}
	}
}
