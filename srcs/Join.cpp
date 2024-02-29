/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:38:11 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/29 04:19:42 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"
#include "Server.hpp"
#include "Channel.hpp"

std::vector<std::string> string_to_vector_(std::string str, std::string arg) {
    std::vector<std::string>    str_vector;
	std::string                 token;
	size_t                      pos = 0;

    while (str.length() > 0) {
        if((pos = str.find(arg.c_str())) == std::string::npos){
            pos = str.length();
        }
   	    token = str.substr(0, pos);
        str_vector.push_back(token);
		str.erase(0, pos + arg.length());
    }
    return (str_vector);
}

std::string	parsing_cmd_mdp(std::string mdp) {
	size_t i = 0;
	std::string		mdp_ok;


	while (i < mdp.length()) {
		if (mdp[i] == '\0' || mdp[i] == '\r' || mdp[i] == '\n' || mdp[i] == '\f' || mdp[i] == '\t' || mdp[i] == '\v' || mdp[i] == ' ') {
			break ;
		}
		i++;
	}
	if (i > 0 && mdp.length() < 23)
		mdp_ok = mdp.substr(0, i);
	return (mdp_ok);
}

std::map<std::string, std::string>	Command::_parsing_cmd_join(std::string chan, std::string mdp, User* client) {
	std::vector<std::string>			j_chans = string_to_vector_(chan, ",");
	std::vector<std::string>			j_mdp;
	size_t								i = 0;
	size_t 								j = 0;
	std::map<std::string, std::string>	parse;
	std::string							chan_ok;

	if (!mdp.empty())
		j_mdp = string_to_vector_(mdp, ",");
	while (i < j_chans.size()) {
		while (!j_chans[i].empty() && j != j_chans[i].length()) {
			if (j_chans[i][0] != '#' || j_chans[i][j] == '\0' || j_chans[i][j] == '\a' || j_chans[i][j] == '\n' || j_chans[i][j] == '\r' || j_chans[i][j] == ' ') {
				break ;
			}
			j++;
		}
		if (j > 0 && j == j_chans[i].length() && j_chans[i].length() < 200) {
			chan_ok = j_chans[i].substr(0, j);
			j = 0;
			if (!j_mdp.empty() && i < j_mdp.size())
				parse[chan_ok] = parsing_cmd_mdp(j_mdp[i]);
			else
				parse[chan_ok];
		}
		else
			this->_send_data_to_client(ERR_NOSUCHCHANNEL(client->getNickname(), j_chans[i]), client);
		i++;
	}
	return (parse);
}

void	Command::_cmd_JOIN(std::vector<std::string> cmd, User* client, Server* opt) {
	std::map<std::string, std::string>	parse;
	std::string							mdp;
	
	if (cmd.size() < 2) {
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
		return ;
	}
	else if (cmd.size() != 2) //cas ou pas de mdp segfault	
		mdp = cmd[2];
	parse = this->_parsing_cmd_join(cmd[1], mdp, client);

	for (std::map<std::string, std::string>::iterator itp = parse.begin(); itp != parse.end(); itp++) {
		std::map<std::string, Channel*>	listchan = opt->getListChannel(); // chan list
		std::map<std::string, Channel*>::iterator itchan = listchan.find(itp->first); //find if chan
		if (itchan == listchan.end()) { //chan no exist // remplir listchan serv // +1 a nbchan->user
			Channel*	tmp = new Channel(itp->first, client);
			opt->setListChannel(tmp);
			client->setnbChan(1);
			this->_send_data_to_client(RPL_JOIN(client->getNickname(), itp->first), client);
		}
		else if (itchan != listchan.end()) { //channel exist
			//check nb user chan et nb chan user
			if (itchan->second->getFlagLimit()) {
				size_t max_u_chan = itchan->second->getLimitUsers();
				std::vector<User*>	tmp = itchan->second->getListUsers();
				if (max_u_chan < tmp.size() + 1) {
					this->_send_data_to_client(ERR_CHANNELISFULL(client->getNickname(), itp->first), client);
					continue ;
				}
			}
			if (client->getnbChan() + 1 > 10) {
				this->_send_data_to_client(ERR_TOOMANYCHANNELS(client->getNickname(), itp->first), client);
				continue ;
			}
			//channel mode invite 
			if (itchan->second->getFlagInvite()) {
				std::string name = client->getNickname();
				std::vector<User*>	list_invit = itchan->second->getListInvitUser();
				std::vector<User*>::iterator it = list_invit.begin();
				while (it != list_invit.end()) { //client invite in channel
					if (name.compare((*it)->getNickname()) == 0)
						break ;
				}
				if (it == list_invit.end()) {
					this->_send_data_to_client(ERR_INVITEONLYCHAN(client->getNickname(), itp->first), client);
					continue ;
				}
				else if (it != list_invit.end())
					; ///check if client a accepter l'invit
			}
			//channel mode pass
			if (itchan->second->getFlagPass()) {
				const std::string		chanmdp = itchan->second->getPassword();
				if (itp->second.empty() || chanmdp.compare(itp->second) != 0) {
					this->_send_data_to_client(ERR_BADCHANNELKEY(client->getNickname(), itp->first), client);
					continue ;
				}
			}
			itchan->second->setNewUser(client);
			client->setnbChan(1);
			this->_send_data_to_client(RPL_JOIN(client->getNickname(), itp->first), client);
		}
	}
}
