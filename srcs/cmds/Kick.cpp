/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arforgea <arforgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:55:33 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/30 16:26:32 by arforgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/User.hpp"
#include "../../incs/Error.hpp"
#include "../../incs/Server.hpp"
#include "../../incs/Channel.hpp"

void	Command::_cmd_KICK(std::vector<std::string> cmd, User* client, Server* opt) {
	
	if (cmd.size() < 3)
	{
		this->_send_data_to_client(ERR_NEEDMOREPARAMS(client->getNickname(), cmd[0]), client);
		return ;
	}

	std::map<std::string, Channel*> listchan = opt->getListChannel();  //list channel
	std::map<std::string, Channel*>::iterator it = listchan.find(cmd[1]);	//check if channel exist

	if (it == listchan.end()) {
		this->_send_data_to_client(ERR_NOSUCHCHANNEL(client->getNickname(), cmd[1]), client);
		return ;
	}
	if (this->_check_user(cmd, client, it) == 1)
		return ;
	if (!vector_check_user(it->second->getListChanop(), client->getNickname())) {
		this->_send_data_to_client(ERR_CHANOPRIVSNEEDED(client->getNickname(), cmd[1]), client);
		return ;
	}
	else 
	{
		std::vector<std::string>user = string_to_vector_(cmd[2], ",");
		
	

		for (unsigned long l = 0; l < user.size(); l++)
		{
			std::vector<User*> listuser = it->second->getListUsers(); //list user in the channel
			std::vector<User*>::iterator ite;
			for ( ite = listuser.begin(); ite != listuser.end(); ite++) {	//find if the user kick is in the channel
				if (user[l] == (*ite)->getNickname())
					break ;
			}
			if (ite == listuser.end())
				this->_send_data_to_client(ERR_USERNOTINCHANNEL(client->getNickname(), user[l], cmd[1]), client);
			else if (client->getNickname() == user[l])
				return ;
			else {
				it->second->deleteUser(user[l]);
				//set le nbchan du user
				(*ite)->setnbChan(-1);
				std::string	msgkick = "";
				if (cmd.size() != 3)
				{
					msgkick.clear();
					for (unsigned int i = 3; i != cmd.size(); i++) // recover the msg
					{
						msgkick += cmd[i];
						msgkick += " ";
					}		
					if (msgkick[0] == ':')
						msgkick.erase(msgkick.begin()); //delete the ':' character
					msgkick.erase(msgkick.end() - 1); //delete the " " at the end

					//send msg to user 
					for ( ite = listuser.begin(); ite != listuser.end(); ite++) {
						this->_send_data_to_client(RPL_KICK(client->getNickname(), user[l], cmd[1], msgkick), (*ite));
					}
				}
				else
				{
					//send msg to user 
					for ( ite = listuser.begin(); ite != listuser.end(); ite++) {
						this->_send_data_to_client(RPL_KICK(client->getNickname(), user[l], cmd[1], msgkick), (*ite));
					}
				}
			}
		}
	}
}
