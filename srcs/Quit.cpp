/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 00:30:25 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/07 21:19:12 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include "User.hpp"
#include "Error.hpp"

void	Command::_cmd_QUIT(std::vector<std::string> cmd, User* client, Server* opt)
{

	int socket = client->getSocket();

	std::string	msg;

	if (cmd.size() > 1)
	{
		for (unsigned int i = 1; i != cmd.size(); i++) // recover the msg
		{
			msg += cmd[i];
			msg += " ";
		}		
		if (msg[0] == ':')
			msg.erase(msg.begin()); //delete the ':' character
		msg.erase(msg.end() - 1); //delete the " " at the end
	}
	else
		msg = "Leaving";

	std::map<std::string, Channel*> listchan = opt->getListChannel();  //list channel
	
	for (std::map<std::string, Channel*>::iterator it = listchan.begin(); it != listchan.end(); it++)
	{

		std::vector<User*> listuser = it->second->getListUsers();
		std::vector<User*>::iterator ituser;
		for (ituser = listuser.begin(); ituser != listuser.end(); ituser++)
		{
			if (client->getNickname() == (*ituser)->getNickname())
				break;
		}
		if (ituser != listuser.end())
		{
			for (ituser = listuser.begin(); ituser != listuser.end(); ituser++)
			{
				if (client->getNickname() != (*ituser)->getNickname())
					this->_send_data_to_client(RPL_QUIT(client->getNickname(), msg), (*ituser));
			}
			it->second->deleteUser(client->getNickname());
		}
	}
	

	//rechercher dans tous les chans si le USER est present
	// le delete des list USER + RPL_QUIT

	opt->deleteUser(socket);
}
 