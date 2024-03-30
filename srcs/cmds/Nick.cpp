/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:02:54 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/05 10:05:04 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/User.hpp"
#include "../../incs/Server.hpp"
#include "../../incs/Error.hpp"

void	Command::_cmd_NICK(std::vector<std::string> cmd, User* client, Server* opt) {

	if (client->getInit() == 0)
	{
		this->_send_data_to_client(RPL_PASSNEED(), client);
		return ;
	}

	regex_t	regex;
	regcomp(&regex, "^([A-}])([A-}0-9-]{0,8})$", REG_EXTENDED);
	std::vector<User*> lusers = opt->getListUser();
	std::string	str_nick = client->getNickname();
	if (str_nick.empty())
		str_nick = "NICK";
	if (cmd.size() != 2) { // if no nick given
		regfree(&regex);
		this->_send_data_to_client(ERR_NONICKNAMEGIVEN(str_nick), client);
		return ;
	}
	else if (cmd[1].size() > 9 || regexec(&regex, cmd[1].c_str(), 0, NULL, 0) == REG_NOMATCH) { // check if nickname is allowed
		regfree(&regex);
		this->_send_data_to_client(ERR_ERRONEUSNICKNAME(str_nick, cmd[1]), client);
		return ;
	}
	else // check if nobody have this nickname
	{
		regfree(&regex);
		for (std::vector<User*>::iterator it = lusers.begin(); it != lusers.end(); ++it) {
			if (check_nickname_cass((*it)->getNickname(), cmd[1]) == false) {
				this->_send_data_to_client(ERR_NICKNAMEINUSE(str_nick, cmd[1]), client);
				return;
			}
		}
	}
	regfree(&regex);
	
	client->setNickname(cmd[1]);
	if (client->getInit() == 1)
		client->setInit(2);
}
