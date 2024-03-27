/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:04:29 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/07 19:58:12 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
#include "../../incs/Channel.hpp"
#include "../../incs/User.hpp"
#include "../../incs/Error.hpp"

int Command::_check_user(std::vector<std::string> cmd, User* client, std::map<std::string, Channel*>::iterator channel)
{
		std::vector<User*> listuser = channel->second->getListUsers(); //list user in the channel
		std::vector<User*>::iterator ite;
		for ( ite = listuser.begin(); ite != listuser.end(); ite++) {	//find if the user is in the channel
			if (client->getNickname() == (*ite)->getNickname())
				break ;
		}
		if (ite == listuser.end()) {
			this->_send_data_to_client(ERR_NOTONCHANNEL(client->getNickname(), cmd[1]), client);
			return (1);
		}

		if (channel->second->getFlagTopic() == true)
		{
			std::vector<User*> listuserop = channel->second->getListChanop(); //list user op in the channel
			std::vector<User*>::iterator iteop;
			for ( iteop = listuserop.begin(); iteop != listuserop.end(); iteop++) { //check if the user is op
				if (client->getNickname() == (*iteop)->getNickname())
					break ;
			}
			if (iteop == listuserop.end())  {
				this->_send_data_to_client(ERR_CHANOPRIVSNEEDED(client->getNickname(), cmd[1]), client);
				return (1);
			}
		}
		return (0);
}

void	Command::_cmd_TOPIC(std::vector<std::string> cmd, User* client, Server* opt) 
{
	if (cmd.size() < 2) {  //check params size
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
		return ;
	}
	
	std::map<std::string, Channel*> listchan = opt->getListChannel();  //list channel
	std::map<std::string, Channel*>::iterator it = listchan.find(cmd[1]);	//check if channel exist
	if (it == listchan.end())
	{
		this->_send_data_to_client(ERR_NOSUCHCHANNEL(client->getNickname(), cmd[1]), client);
		return ;
	}
	else
	{
		if (this->_check_user(cmd, client, it) == 1)
			return ;
	}
	if (cmd.size() == 2) // check si c'est la commande /topic <nom du channel>
	{
		std::string subj = it->second->getSubject();
		if (subj.size() != 0) { //check if channel have a subject
			this->_send_data_to_client(RPL_TOPIC(client->getNickname(), cmd[1], subj), client); //affiche le topic du chan
			return ;
		}
		else {
			this->_send_data_to_client(RPL_NOTOPIC(client->getNickname(), cmd[1]), client); // pas de topic pour le chan
			return ;
		}
	}
	else
	{
		std::string subj;
		for (unsigned int i = 2; i != cmd.size(); i++) // recover the subject
		{
			subj += cmd[i];
			subj += " ";
		}
		if (subj[0] == ':')
			subj.erase(subj.begin()); //delete the ':' character
		subj.erase(subj.end() - 1); //delete the " " at the end
		it->second->setSubject(subj); 

		std::vector<User*> listuser = opt->getListUser();
		for (std::vector<User*>::iterator it = listuser.begin(); it != listuser.end(); it++) {
			this->_send_data_to_client(RPL_TOPIC((*it)->getNickname(), cmd[1], subj), (*it));
		}

	}
}