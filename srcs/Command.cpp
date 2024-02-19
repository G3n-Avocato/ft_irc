/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:06:29 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/19 12:15:15 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "User.hpp"
#include "Error.hpp"

Command::Command() {

	// this->_l_cmds["PASS"] = &Command::_cmd_PASS;
	this->_l_cmds["NICK"] = &Command::_cmd_NICK;
	// this->_l_cmds["USER"] = &Command::_cmd_USER;
	this->_l_cmds["JOIN"] = &Command::_cmd_JOIN;
	// this->_l_cmds["PART"] = &Command::_cmd_PART;
	// this->_l_cmds["PRIVMSG"] = &Command::_cmd_PRIVMSG;
	// this->_l_cmds["QUIT"] = &Command::_cmd_QUIT;
	// this->_l_cmds["WHO"] = &Command::_cmd_WHO;
	// this->_l_cmds["KICK"] = &Command::_cmd_KICK;
	// this->_l_cmds["INVITE"] = &Command::_cmd_INVITE;
	// this->_l_cmds["TOPIC"] = &Command::_cmd_TOPIC;
	// this->_l_cmds["MODE"] = &Command::_cmd_MODE;
}

Command::~Command() {
}

//peut etre return quelque chose a send dans le server 
void	Command::choose_cmds(std::vector<std::vector<std::string> > cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user) {

	for (std::vector<std::vector<std::string> >::iterator line = cmd.begin(); line != cmd.end(); line++) {
			std::map<const std::string, void (Command::*)(std::vector<std::string>, User*, std::map<std::string, Channel*>*, std::vector<User*>*)>::iterator it = this->_l_cmds.find((*line)[0]); //verifier position du name de la cmd /attention/

	// 	(this->*(it->second))(*line, client, l_chan, l_user); //appel du pointeur sur la fonction membre avec iterateur
	}
}

//prototype pour les fonctions commandes 
void	Command::_cmd_JOIN(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user) {

	if (cmd.size() < 2)
	 	this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getUsername(), cmd[0]), client);

}

void	Command::_cmd_NICK(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>* l_chan, std::vector<User*>* l_user) {

	if (cmd.size() < 2)	{
		this->_send_data_to_client(ERR_NONICKNAMEGIVEN(client->getUsername()), client);
	}
	else if (cmd[1].size() > 9) {
		this->_send_data_to_client(ERR_ERRONEUSNICKNAME(client->getUsername(), cmd[1]), client);
	}
	else
	{
		for (std::map<std::string, Channel*>::iterator it = l_chan->begin(); it != l_chan->end(); it++) {
			if (it->first == cmd[1]) {
				this->_send_data_to_client(ERR_NICKNAMEINUSE(client->getUsername(), cmd[1]), client);
				return;
			}
		}
	}
	client->setNickname(cmd[1]);

}


void	Command::_send_data_to_client(std::string mess, User* user) {
	int socket = user->getSocket();
	if (send(socket, mess.c_str(), mess.size(), 0) == -1)
		perror("send");
}
