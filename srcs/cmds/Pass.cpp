/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:49:43 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/29 17:14:19 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/User.hpp"
#include "../../incs/Server.hpp"
#include "../../incs/Error.hpp"

void	Command::_cmd_PASS(std::vector<std::string> cmd,  User* client, Server* opt) 
{

	std::string	str_nick = client->getNickname();
	if (str_nick.empty())
		str_nick = "NICK";
	if (client->getInit() != 0) 		//check if the pass already set
		this->_send_data_to_client(ERR_ALREADYREGISTRED(str_nick), client);
	else if (cmd.size() < 2) 				//check if the cmd have a params
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(str_nick, cmd[0]), client);
	else if (cmd[1] == opt->getPass())
		client->setInit(1);
	else 
		this->_send_data_to_client(ERR_PASSWDMISMATCH(str_nick), client);
}
