/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 00:30:25 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/30 16:26:51 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
#include "../../incs/Channel.hpp"
#include "../../incs/User.hpp"
#include "../../incs/Error.hpp"

void	Command::_cmd_QUIT(std::vector<std::string> cmd, User* client, Server* opt)
{

	int socket = client->getSocket();

	std::string	msg;

	if (cmd.size() > 1)
	{
		for (size_t i = 1; i < cmd.size(); i++) // recover the msg
		{
			msg += cmd[i];
			if (i + 1 != cmd.size())
				msg += " ";
		}		
		if (msg[0] == ':')
			msg.erase(msg.begin()); //delete the ':' character
	}
	else
		msg = "Leaving";

	std::map<std::string, Channel*> listchan = opt->getListChannel();  //list channel
	std::vector<std::string>		del_chan;

	for (std::map<std::string, Channel*>::iterator it = listchan.begin(); it != listchan.end(); it++) // check in every chan if the user is in
	{
		std::vector<User*>				listuser = it->second->getListUsers();
		std::vector<User*>::iterator	ituser;
		for (ituser = listuser.begin(); ituser != listuser.end(); ituser++)
		{
			if (client->getNickname() == (*ituser)->getNickname())
				break;
		}
		if (ituser != listuser.end())
		{
			for (ituser = listuser.begin(); ituser != listuser.end(); ituser++) // send a msg to every user in the chan
			{
				if (client->getNickname() != (*ituser)->getNickname())
					this->_send_data_to_client(RPL_QUIT(client->getNickname(), msg), (*ituser));
			}
			it->second->deleteUser(client->getNickname()); // delete the user of the chan ajouter pour les op 
			it->second->deleteChanop(client->getNickname());
			if (listuser.size() == 1)
				del_chan.push_back(it->second->getName());
		}
	}
	for (std::vector<std::string>::iterator del = del_chan.begin(); del != del_chan.end(); del++)
		opt->deleteChannel(*del);

	opt->deleteUser(socket, 1);
}
 