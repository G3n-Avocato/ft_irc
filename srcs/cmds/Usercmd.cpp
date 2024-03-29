/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Usercmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:49:30 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/05 10:05:37 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/User.hpp"
#include "../../incs/Server.hpp"
#include "../../incs/Error.hpp"

void	Command::_cmd_USER(std::vector<std::string> cmd, User* client, Server *opt) {
	
	(void)opt;
	//if (client->getInit() == 0) {
	//	this->_send_data_to_client(RPL_PASSNEED(), client);
	//	return ;
	//}
	if (client->getInit() <= 1) {
		this->_send_data_to_client(RPL_NICKNEED(), client);
		return ;
	}
	else if (client->getInit() > 2)
	{
		this->_send_data_to_client(ERR_ALREADYREGISTRED(client->getNickname()), client);
		return ;		
	}
	else if (cmd.size() == 2 || cmd.size() == 5)
	{
		client->setUsername(cmd[1]);
		client->setInit(3);
		this->_send_data_to_client(RPL_WELCOME(client->getNickname()), client);
	}
	else
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);	
	
}
