/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:55:33 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/07 19:44:25 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Error.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void	Command::_cmd_KICK(std::vector<std::string> cmd, User* client, Server* opt) {
	
	if (cmd.size() < 3)
	{
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

	if (this->_check_user(cmd, client, it) == 1)
		return ;
	else 
	{
	
		//regarder si le user est dans le chan
		std::vector<User*> listuser = it->second->getListUsers(); //list user in the channel
		std::vector<User*>::iterator ite;
		for ( ite = listuser.begin(); ite != listuser.end(); ite++) {	//find if the user kick is in the channel
			if (cmd[2] == (*ite)->getNickname())
				break ;
		}

		if (ite == listuser.end())
		{
			std::cout << "-----USER KICK NOT IN CHAN-----" << std::endl; //---------------------------------------
			return ;
		}
		else if (client->getNickname() == cmd[2])
		{
			std::cout << "-----AUTO KICK NOT ALLOWED-----" << std::endl; //---------------------------------------
			return ;
		}
		
		//le delete du chan

		it->second->deleteUser(cmd[2]);
		
		//set le nbchan du user

		(*ite)->setnbChan(-1);
		
		//faire le msg de kick

		if (cmd.size() != 3)
		{
			std::string msgkick;
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
				this->_send_data_to_client(RPL_KICK(client->getNickname(), cmd[2], cmd[1], msgkick), (*ite));
			}
		}
		else
		{
			//send msg to user 
			for ( ite = listuser.begin(); ite != listuser.end(); ite++) {
				this->_send_data_to_client(RPL_KICK(client->getNickname(), cmd[2], cmd[1], client->getNickname()), (*ite));
			}
		}
	}
}
