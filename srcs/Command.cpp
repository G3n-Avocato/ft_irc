/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:06:29 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/05 10:01:45 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Command.hpp"
#include "../incs/User.hpp"
#include "../incs/Error.hpp"

Command::Command() {

	this->_l_cmds["PASS"] = &Command::_cmd_PASS;
	this->_l_cmds["NICK"] = &Command::_cmd_NICK;
	this->_l_cmds["USER"] = &Command::_cmd_USER;
	this->_l_cmds["JOIN"] = &Command::_cmd_JOIN;
	this->_l_cmds["PART"] = &Command::_cmd_PART;
	this->_l_cmds["PRIVMSG"] = &Command::_cmd_PRIVMSG;
	this->_l_cmds["QUIT"] = &Command::_cmd_QUIT;
	this->_l_cmds["KICK"] = &Command::_cmd_KICK;
	this->_l_cmds["INVITE"] = &Command::_cmd_INVITE;
	this->_l_cmds["TOPIC"] = &Command::_cmd_TOPIC;
	this->_l_cmds["MODE"] = &Command::_cmd_MODE;
}

Command::~Command() {
}

void	Command::choose_cmds(User* client, Server* opt) {
	std::vector<std::vector<std::string> >	cmd = client->getvectorcmd();
	for (std::vector<std::vector<std::string> >::iterator line = cmd.begin(); line != cmd.end(); line++) {
		std::map<const std::string, void (Command::*)(std::vector<std::string>, User*, Server*)>::iterator it = this->_l_cmds.find((*line)[0]);
		if (it != this->_l_cmds.end()) {
			if (this->_check_client_init_to_exec_cmds(client, (*line)[0]))
				(this->*(it->second))(*line, client, opt);
		}
	}
}

void	Command::_send_data_to_client(std::string mess, User* user) {
	int socket = user->getSocket();
	if (send(socket, mess.c_str(), mess.size(), 0) == -1)
		perror("send");
}

bool	Command::_check_client_init_to_exec_cmds(User* client, std::string cmd) {
	if (client->getInit() != 3) {
		if (!cmd.compare("PASS") || !cmd.compare("NICK") || !cmd.compare("USER") || !cmd.compare("QUIT"))
			return (true);
		std::string	msg = "NICK";
		if (!client->getNickname().empty())
			msg = client->getNickname();
		this->_send_data_to_client(ERR_NOTREGISTERED(msg), client);
		return (false);
	}
	return (true);
}