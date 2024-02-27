/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:02:54 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/02/26 22:58:43 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Server.hpp"
#include "Error.hpp"


void	Command::_cmd_NICK(std::vector<std::string> cmd, User* client, Server* opt) {

	if (client->getInit() == 0)
	{
		std::cout << "NEED PASSWORD BEFORE" << std::endl;
	}

	regex_t	regex;
	regcomp(&regex, "^([A-}])([A-}0-9-]{0,8})$", REG_EXTENDED);
	std::vector<User*>& lusers = opt->getLuserRef();
	
	if (cmd.size() < 2)	{
		regfree(&regex);
		this->_send_data_to_client(ERR_NONICKNAMEGIVEN(client->getUsername()), client);
		return ;
	}
	else if (cmd[1].size() > 9 || regexec(&regex, cmd[1].c_str(), 0, NULL, 0) == REG_NOMATCH) {
		regfree(&regex);
		this->_send_data_to_client(ERR_ERRONEUSNICKNAME(client->getUsername(), cmd[1]), client);
		return ;
	}
	else
	{
		regfree(&regex);
		std::vector<User*>::iterator it = lusers.begin();
		for (User *tmp = *it; tmp->getNickname() != cmd[1] && it != lusers.end(); it++ ) {
		}
		if (it != lusers.end())
		{
			this->_send_data_to_client(ERR_NICKNAMEINUSE(client->getUsername(), cmd[1]), client);
			return;
		}
	}
	regfree(&regex);
	
	client->setNickname(cmd[1]);
	if (client->getInit() == 1)
		client->setInit(2);
}
