/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arforgea <arforgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:36:15 by arforgea          #+#    #+#             */
/*   Updated: 2024/03/05 21:21:12 by arforgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Server.hpp"
#include "../../incs/Channel.hpp"

std::string	rebuild_data(std::vector<std::string> last, int start) {
	std::string	tmp;

	for (std::vector<std::string>::iterator it = last.begin() + start; it != last.end(); it++) {
		tmp += *it;
		if (it + 1 != last.end())
			tmp += " ";
	}
	if (tmp[0] == ':')
		tmp.erase(tmp.begin());
	return (tmp);
}

std::vector<std::string> string_to_vector(std::string str, std::string arg){
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

void	Command::_cmd_PRIVMSG(std::vector<std::string> rawCmd, User* client, Server* server){
    std::vector<User*>              userLst     = server->getListUser(); 
    std::map<std::string, Channel*> channelLst   = server->getListChannel();

    if (rawCmd.size() >= 3 && rawCmd[0].find("MSGPRIV")) { 
        std::string                         data    = rebuild_data(rawCmd, 2); 
        std::vector<std::string>            sendLst = string_to_vector(rawCmd[1], ",");
        std::vector<std::string>::iterator  it_send = sendLst.begin();
        if(it_send == sendLst.end()) {
            this->_send_data_to_client(ERR_NORECIPIENT(client->getNickname(), rawCmd[0]), client);
            return;
        }
        for (unsigned long i = 0; sendLst.size() > 0 && i < sendLst.size(); i++) {
            std::string tmp = sendLst[i];
            for (unsigned long j = i + 1; j < sendLst.size(); j++) {
                if (!tmp.compare(sendLst[j])) {
                    this->_send_data_to_client(ERR_TOOMANYTARGETS(client->getNickname()), client);
                    return ;
                }
            }
        }
        while (it_send != sendLst.end()) {
            std::string current_user = *it_send;
            if (!current_user.find("#")) {
		        std::map<std::string, Channel*>::iterator channel_it = channelLst.find(current_user);
                if (channel_it != channelLst.end()) {
                    std::vector<User*>	ChannelUserLst = channel_it->second->getListUsers();
                    for (std::vector<User*>::iterator it_user = ChannelUserLst.begin(); it_user != ChannelUserLst.end(); it_user++) {
                        if(client->getNickname().compare((*it_user)->getNickname()))
                            this->_send_data_to_client(CHAN_MSG(client->getNickname(), channel_it->second->getName(), data), (*it_user));
                    }
                }
                else
                    this->_send_data_to_client(ERR_CANNOTSENDTOCHAN(client->getNickname(), current_user), client);
            }
            else {
                std::vector<User*>::iterator it_user = userLst.begin();
                while (it_user != userLst.end()) {
                    if (!current_user.compare((*it_user)->getNickname()))
                        break ;
                    it_user++;
                }
                if (it_user != userLst.end())
                    this->_send_data_to_client(USER_MSG(client->getNickname(), current_user, data), (*it_user));
                else
                    this->_send_data_to_client(ERR_NOSUCHNICK(client->getNickname(), current_user), client);
            }
            it_send++;
        }
    }
    else if(rawCmd.size() == 2)
        this->_send_data_to_client(ERR_NOTEXTTOSEND(client->getNickname()), client);
    else if (rawCmd.size() < 2)
        this->_send_data_to_client(ERR_NORECIPIENT(client->getNickname(), rawCmd[0]), client);
}   