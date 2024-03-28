/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:38:11 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/26 17:25:00 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Error.hpp"
#include "../../incs/Server.hpp"
#include "../../incs/Channel.hpp"
#include "../../incs/utils.hpp"

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
			else if (!pass.empty() && i == pass.size())
				parse[canal] = parsing_cmd_mdp(pass[pass.size() - 1]);
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
		if (!vector_check_user(itchan->second->getListInvitUser(), client->getNickname())) {
			this->_send_data_to_client(ERR_INVITEONLYCHAN(client->getNickname(), name), client);
			return (false);
		}
		else {
			std::vector<std::string>	invit = client->getlistChanInvite();
			std::vector<std::string>::iterator itl = invit.begin();
			while (itl != invit.end()) {
				if (name.compare(*itl) == 0)
					break ;
				itl++;
			}
			if (itl == invit.end()) {
				this->_send_data_to_client(ERR_INVITEONLYCHAN(client->getNickname(), name), client);
				return (false);
			}
			else {
				itchan->second->deleteUserInvitList(client->getNickname());
				client->deleteinvitchan(name);
			}
		}
	}
	return (true);
}

void	Command::_cmd_JOIN(std::vector<std::string> cmd, User* client, Server* opt) {
	std::map<std::string, std::string>	parse;
	std::string							mdp;
	std::string							rpl_msg;

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
			rpl_msg = RPL_JOIN(client->getNickname(), client->getUsername(), itp->first);
			this->_sendMsgtoUserlist(itchan->second->getListUsers(), rpl_msg);
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
			rpl_msg = RPL_JOIN(client->getNickname(), client->getUsername(), itp->first);
			this->_sendMsgtoUserlist(itchan->second->getListUsers(), rpl_msg);
			this->_sendJoinMsg(client, itchan->second);	
		}
	}
}

void	Command::_sendMsgtoUserlist(std::vector<User*> list, std::string msg) {
	for (std::vector<User*>::iterator it = list.begin(); it != list.end(); it++) {
		this->_send_data_to_client(msg, *it);
	}
}

void	Command::_sendJoinMsg(User* client, Channel* canal) {
	std::string			usein = list_user_to_string(canal->getListUsers(), canal->getListChanop());
	std::vector<User*>	list = canal->getListUsers();
	for (std::vector<User*>::iterator it = list.begin(); it != list.end(); it++) {
		std::string	rpl_msg = RPL_NAMREPLY((*it)->getNickname(), canal->getName(), usein);
		this->_send_data_to_client(rpl_msg, *it);
	}
	usein.clear();
	if (!canal->getSubject().empty())
		this->_send_data_to_client(RPL_TOPIC(client->getNickname(), canal->getName(), canal->getSubject()), client);
	else
		this->_send_data_to_client(RPL_NOTOPIC(client->getNickname(), canal->getName()), client);
}
