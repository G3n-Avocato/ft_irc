/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:49:43 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/02/26 22:51:38 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Server.hpp"
#include "Error.hpp"

void	Command::_cmd_PASS(std::vector<std::string> cmd,  User* client, Server* opt) 
{

	if (client->getInit() != 0) 		//check if the pass already set
		this->_send_data_to_client(ERR_ALREADYREGISTRED(client->getUsername()), client);
	else if (cmd.size() < 2) 				//check if the cmd have a params
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getUsername(), cmd[0]), client);
	else if (cmd[1] == opt->getPass())
		client->setInit(1);
}
