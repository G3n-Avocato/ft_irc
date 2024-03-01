/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Usercmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:49:30 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/01 17:50:40 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Server.hpp"
#include "Error.hpp"

void	Command::_cmd_USER(std::vector<std::string> cmd, User* client, Server *opt) {
	
	(void)opt;
	if (client->getInit() < 2) {
		return ;
	}
	else if (client->getInit() > 2)
	{
		this->_send_data_to_client(ERR_ALREADYREGISTRED(client->getUsername()), client);
		return ;		
	}
	else if (cmd.size() == 2 || cmd.size() == 5)
	{
		client->setUsername(cmd[1]);
		client->setInit(3);
		this->_send_data_to_client(RPL_WELCOME(client->getNickname()), client);
	}
	else
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getUsername(), cmd[0]), client);	
	
}
