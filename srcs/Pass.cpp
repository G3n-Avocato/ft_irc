/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:49:43 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/02/24 12:47:55 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "User.hpp"
#include "Error.hpp"

void	Command::cmd_PASS(std::vector<std::string> cmd, std::string pass, User *client) 
{

	if (client->getInit() != 0) 		//check if the pass already set
		this->_send_data_to_client(ERR_ALREADYREGISTRED(client->getUsername()), client);
	else if (cmd.size() < 2) 				//check if the cmd have a params
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getUsername(), cmd[0]), client);
	else if (cmd[1] == pass)
		client->setInit(1);
}
