/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:06:29 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/16 15:14:37 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Command.hpp"

// Command::Command() {

// 	this->_l_cmds["PASS"] = &Command::_cmd_PASS;
// 	this->_l_cmds["NICK"] = &Command::_cmd_NICK;
// 	this->_l_cmds["USER"] = &Command::_cmd_USER;
// 	this->_l_cmds["JOIN"] = &Command::_cmd_JOIN;
// 	this->_l_cmds["PART"] = &Command::_cmd_PART;
// 	this->_l_cmds["PRIVMSG"] = &Command::_cmd_PRIVMSG;
// 	this->_l_cmds["QUIT"] = &Command::_cmd_QUIT;
// 	this->_l_cmds["WHO"] = &Command::_cmd_WHO;
// 	this->_l_cmds["KICK"] = &Command::_cmd_KICK;
// 	this->_l_cmds["INVITE"] = &Command::_cmd_INVITE;
// 	this->_l_cmds["TOPIC"] = &Command::_cmd_TOPIC;
// 	this->_l_cmds["MODE"] = &Command::_cmd_MODE;
// }

// Command::~Command() {
// }

// //peut etre return quelque chose a send dans le server 
// void	Command::choose_cmds(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>* l_chan) {

// 	std::map<const std::string, void (Command::*)(std::vector<char*>, User*, std::map<Channel*, std::vector<User*>>*)>::iterator it = this->_l_cmds.find(cmd[1]); //verifier position du name de la cmd /\attention/\

// 	(this->*(it->second))(cmd, client, l_chan); //appel du pointeur sur la fonction membre avec iterateur
// }

// //prototype pour les fonctions commandes 
// void	Command::_cmd_JOIN(std::vector<char*> cmd, User* client, std::map<Channel*, std::vector<User*>>* l_chan) {

// 	if (cmd.size() < 2)
// 		return (ERR_NEEDMOREPARAMS())	

// }
