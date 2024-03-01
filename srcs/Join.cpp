/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:38:11 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/01 02:27:30 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "utils.hpp"

std::string	parsing_cmd_mdp(std::string mdp) {
	size_t i = 0;
	std::string		mdp_ok;

	while (i < mdp.length()) {
			if (!syntax_mdp_channel(mdp[i]))
				break ;
		i++;
	}
	if (i > 0 && mdp.length() < 23)
		mdp_ok = mdp.substr(0, i);
	return (mdp_ok);
}

std::map<std::string, std::string>	Command::_parsing_cmd_join(std::string chan, std::string mdp, User* client) {
	std::vector<std::string>			lnames = string_to_vector_(chan, ",");
	std::vector<std::string>			pass;
	size_t								i = 0;
	size_t 								j = 0;
	std::map<std::string, std::string>	parse;
	std::string							canal;

	if (!mdp.empty())
		pass = string_to_vector_(mdp, ",");
	while (i < lnames.size()) {
		while (!lnames[i].empty() && j != lnames[i].length()) {
			if (lnames[i][0] != '#' || !syntax_name_channel(lnames[i][j]))
				break ;
			j++;
		}
		if (j > 0 && j == lnames[i].length() && lnames[i].length() < 200) {
			canal = lnames[i].substr(0, j);
			j = 0;
			if (!pass.empty() && i < pass.size())
				parse[canal] = parsing_cmd_mdp(pass[i]);
			else
				parse[canal];
		}
		else
			this->_send_data_to_client(ERR_NOSUCHCHANNEL(client->getNickname(), lnames[i]), client);
		i++;
	}
	return (parse);
}

bool	Command::_check_channel_users_limits(std::map<std::string, Channel*>::iterator itchan, User* client, std::string name) {
	
	if (itchan->second->getFlagLimit()) {
		size_t max_u_chan = itchan->second->getLimitUsers();
		std::vector<User*>	tmp = itchan->second->getListUsers();
		if (max_u_chan < tmp.size() + 1) {
			this->_send_data_to_client(ERR_CHANNELISFULL(client->getNickname(), name), client);
			return (false);
		}
	}
	return (true);
}

bool	Command::_check_channel_invite(std::map<std::string, Channel*>::iterator itchan, User* client, std::string name) {	
	if (itchan->second->getFlagInvite()) {
		std::vector<User*>	list_invit = itchan->second->getListInvitUser();
		std::vector<User*>::iterator it = list_invit.begin();
		while (it != list_invit.end()) { //client invite in channel
			if (name.compare((*it)->getNickname()) == 0)
				break ;
		}
		if (it == list_invit.end()) {
			this->_send_data_to_client(ERR_INVITEONLYCHAN(client->getNickname(), name), client);
			return (false);
		}
		else if (it != list_invit.end()){
			/// (Arty)
			/// j'ai enlever un ';' ici et j'ai ajouté des accolades ça voulait pas compiler je sais pas à quoi ça sert ici...
			/// je laisse ça aux professionnels :D https://youtu.be/dQw4w9WgXcQ?si=q79wrxYAywjEgemX&t << (important à regarder !)
			
			///check if client a accepter l'invit
		}
	}
	return (true);
}

void	Command::_cmd_JOIN(std::vector<std::string> cmd, User* client, Server* opt) {
	std::map<std::string, std::string>	parse;
	std::string							mdp;
	
	if (cmd.size() < 2) {
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
		return ;
	}
	else if (cmd.size() != 2) //if no mdp secu for parsing_join
		mdp = cmd[2];
	parse = this->_parsing_cmd_join(cmd[1], mdp, client);

	for (std::map<std::string, std::string>::iterator itp = parse.begin(); itp != parse.end(); itp++) {
		std::map<std::string, Channel*>	listchan = opt->getListChannel();
		std::map<std::string, Channel*>::iterator itchan = listchan.find(itp->first);
		if (client->getnbChan() + 1 > 10) {
			this->_send_data_to_client(ERR_TOOMANYCHANNELS(client->getNickname(), itp->first), client);
			continue ;
		}
		//if CHANNEL DOESN'T EXIST
		if (itchan == listchan.end()) {
			Channel*	tmp = new Channel(itp->first, client);
			opt->setListChannel(tmp);
			client->setnbChan(1);
			listchan = opt->getListChannel();
			itchan = listchan.find(itp->first);
			this->_sendJoinMsg(client, itchan->second);	
		}
		//if CHANNEL EXIST 
		else if (itchan != listchan.end()) {
			
			//CHECK CHANNEL LIMIT USER -- CHECK USER LIMIT CHANNEL
			if (!this->_check_channel_users_limits(itchan, client, itp->first))
				continue ;	

			//if CHANNEL INVITE TRUE (EN COURS ....)
			if (!this->_check_channel_invite(itchan, client, itp->first))
				continue ;

			//if CHANNEL PASSWORD TRUE
			if (itchan->second->getFlagPass()) {
				const std::string		chanmdp = itchan->second->getPassword();
				if (itp->second.empty() || chanmdp.compare(itp->second) != 0) {
					this->_send_data_to_client(ERR_BADCHANNELKEY(client->getNickname(), itp->first), client);
					continue ;
				}
			}
			itchan->second->setNewUser(client);
			client->setnbChan(1);
			this->_sendJoinMsg(client, itchan->second);	
		}
	}
}

void	Command::_sendMsgtoUserlist(std::vector<User*> users_chan, std::string newuser, std::string canal) {
	for (std::vector<User*>::iterator it = users_chan.begin(); it != users_chan.end(); it++) {
		this->_send_data_to_client(RPL_JOIN(newuser, canal), *it);
	}
}

void	Command::_sendJoinMsg(User* client, Channel* canal) {
	this->_sendMsgtoUserlist(canal->getListUsers(), client->getNickname(), canal->getName());
	if (canal->getFlagTopic())
		this->_send_data_to_client(RPL_TOPIC(client->getNickname(), canal->getName(), canal->getSubject()), client);
	else
		this->_send_data_to_client(RPL_NOTOPIC(client->getNickname(), canal->getName()), client);
}
