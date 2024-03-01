/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:37:24 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/01 01:52:13 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include "Error.hpp"

bool	Command::_check_userlist_nick(std::vector<User*> list, std::string name) {
	std::vector<User*>::iterator ituser = list.begin();
	while (ituser != list.end()) {
		if (name.compare((*ituser)->getNickname()) == 0)
			break ;
		ituser++;
	}
	if (ituser == list.end())
		return (false);
	return  (true);
}

bool	Command::_flag_mode_check_exist(std::string flag, User* client) {
	std::string	opt("opsitnmlbvk");
	std::string	optges("itkol");

	if (flag.size() < 2 || (flag[0] != '-' && flag[0] != '+'))
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"), client);
	else if (flag.size() > 2 || opt.find(flag[1]) == std::string::npos)
		this->_send_data_to_client(ERR_UNKNOWNMODE(client->getNickname(), "MODE"), client);
	else if (optges.find(flag[1]) == std::string::npos)
		this->_send_data_to_client(ERR_UMODEUNKNOWNFLAG(client->getNickname()), client);
	else
		return (true);
	return (false);
}

size_t	Command::_new_chanop(std::vector<User*> listuser, std::string name, User* client) {
	size_t itu = 0;
	while (itu < listuser.size()) {
		if (name.compare((*listuser[itu]).getNickname()) == 0)
			break ;
		itu++;
	}
	if (itu < listuser.size())
		return (itu);
	this->_send_data_to_client(ERR_NOSUCHNICK(client->getNickname(), name), client);
	return (itu);
}

void	Command::_flag_mode_exec(std::vector<std::string> cmd, User* client, Server* opt) {
	std::map<std::string, Channel*>				listchan = opt->getListChannel();
	std::map<std::string, Channel*>::iterator	itchan = listchan.begin();

	const char *mode[] = {"i", "t", "k", "o", "l"};
	bool		flag = 0;
	if (cmd[2][0] == '+')
		flag = 1;
	int			i = 0;
	const char		f = cmd[2][1];
	while (i < 5 && f != *mode[i])
		i++;
	switch (i) {
		case 0:
			itchan->second->setFlagInvite(flag);
			break ;
		case 1:
			itchan->second->setFlagTopic(flag);
			break ;
		case 2:
			if (cmd.size() < 4)
				this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
			else {
				int err = itchan->second->setPassword(cmd[3], flag);
				if (err == 467)
					this->_send_data_to_client(ERR_KEYSET(client->getNickname(), cmd[1]), client);
				else if (err == 461)
					this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
			}
			break ;
		case 3:
			if (cmd.size() < 4)
				this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
			else {
				if (flag) {
					std::vector<User*>				listuser = opt->getListUser();
					size_t							itu = this->_new_chanop(listuser, cmd[3], client);
					if (itu < listuser.size()) {
						itchan->second->setNewChanop(listuser[itu]);
						this->_mode_is(itchan->second, client, cmd[3]);
						this->_mode_is(itchan->second, listuser[itu], cmd[3]);
					}
				}
				else {
					if (!itchan->second->deleteChanop(cmd[3]))
						this->_send_data_to_client(ERR_NOSUCHNICK(client->getNickname(), cmd[3]), client);
				}
			}
			break ;
		case 4:
			if (!flag)
				itchan->second->setLimitUser(-1);
			else if (cmd.size() < 4)
				this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
			else if (flag) {
				long int nb = strtol(cmd[3].c_str(), NULL, 10);
				if (nb < 100)
					itchan->second->setLimitUser(nb);
				else
					this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getUsername(), cmd[0]), client);
			}
		default:
			break ;
	}
}

void	Command::_mode_is(Channel* canal, User* client, std::string para) {
	std::string	mode = "+";
	if (canal->getFlagInvite())
		mode += "i";
	if (canal->getFlagTopic())
		mode += "t";
	if (canal->getFlagPass())
		mode += "k";
	if (canal->getFlagLimit())
		mode += "l";
	if (!para.empty()) {
		mode.clear();
		mode = "+o";
	}
	this->_send_data_to_client(RPL_CHANNELMODEIS(client->getNickname(), canal->getName(), mode, para), client);
	mode.clear();
}

void	Command::_cmd_MODE(std::vector<std::string> cmd, User* client, Server* opt) {
	
	if (cmd.size() < 2) {
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
		return ;
	}
	std::map<std::string, Channel*>	listchan = opt->getListChannel();
	std::map<std::string, Channel*>::iterator itchan = listchan.find(cmd[1]);
	if (itchan == listchan.end())
		this->_send_data_to_client(ERR_NOSUCHCHANNEL(client->getNickname(), cmd[1]), client);
	else if (cmd.size() == 2)
		this->_mode_is(itchan->second, client, "");
	else {
		if (!this->_check_userlist_nick(itchan->second->getListUsers(), client->getNickname()))
			this->_send_data_to_client(ERR_NOTONCHANNEL(client->getNickname(), cmd[1]), client);
		else if (!this->_check_userlist_nick(itchan->second->getListChanop(), client->getNickname()))
			this->_send_data_to_client(ERR_CHANOPRIVSNEEDED(client->getNickname(), cmd[1]), client);
		else if (!this->_flag_mode_check_exist(cmd[2], client))
			;
		else
			this->_flag_mode_exec(cmd, client, opt);
	}
	return ;
}
