/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arforgea <arforgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:36:15 by arforgea          #+#    #+#             */
/*   Updated: 2024/02/28 20:36:28 by arforgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

//
#define RESET   "\033[0m"
#define RED     "\033[31m"                  /* Red */
#define YELLOW  "\033[33m"                  /* Yellow */
#define BLUE    "\033[34m"                  /* Blue */
//

std::string	rebuild_data(std::vector<std::string> last, int start) {
	std::string	tmp;
	
	for (std::vector<std::string>::iterator it = last.begin() + start; it != last.end(); it++) {
		tmp += *it;
		if (it + 1 != last.end())
			tmp += " ";
	}
    tmp.erase(0, 1);
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

    std::cout << YELLOW << "Debug:" << RESET << " rawCmd size=" << BLUE << rawCmd.size() << RESET << std::endl; //DEBUG!
    if(rawCmd.size() >= 3 && rawCmd[0].find("MSGPRIV")){
        std::string                         data    = rebuild_data(rawCmd, 2); 
        std::vector<std::string>            sendLst = string_to_vector(rawCmd[1], ",");
        std::vector<std::string>::iterator  it_send = sendLst.begin();
        std::cout << YELLOW << "Debug:" << RESET << " rebuild Data=" << BLUE << data << RESET << std::endl; //DEBUG!
        for(unsigned long i = 0; sendLst.size() > 0 && i < sendLst.size(); i++){
            std::string tmp = sendLst[i];
            for(unsigned long j = i + 1; j < sendLst.size(); j++){
                if(!tmp.compare(sendLst[j])){
                    _send_data_to_client(ERR_TOOMANYTARGETS(sendLst[j]), client);
                    return ;
                }
            }
        }
        while(it_send != sendLst.end()){
            std::string current_user = *it_send;
            if(!current_user.find("#")){
		        std::map<std::string, Channel*>::iterator channel_it = channelLst.find(current_user);
                if(channel_it != channelLst.end()){
                    std::cout << YELLOW << "Debug:" << RESET << " Channel= " << BLUE << channel_it->second->getName() << RESET << std::endl; //DEBUG!
                    std::vector<User*>	ChannelUserLst = channel_it->second->getListUsers();
                    std::vector<User*>::iterator it_user = ChannelUserLst.begin();
                    while (it_user != ChannelUserLst.end()){
                        if(client->getNickname().compare((*it_user)->getNickname()))
                            _send_data_to_client(CHAN_MSG(client->getNickname(), channel_it->second->getName(), data), (*it_user));
                        it_user++;
                    }
                }
                else{
                    std::cout << YELLOW << "Debug:" << RESET << " Channel not fond" << RESET << std::endl; //DEBUG!
                     _send_data_to_client(ERR_CANNOTSENDTOCHAN(client->getNickname(), current_user), client);
                }
            }
            else{
                std::vector<User*>::iterator it_user = userLst.begin();
                while (it_user != userLst.end()) {
                    if (!current_user.compare((*it_user)->getNickname()))
                        break ;
                    it_user++;
                }
                if (it_user == userLst.end())                                                                                   //DEBUG!
                    std::cout << YELLOW << "Debug: " << RESET << "User '" << current_user << "' not fond."<< std::endl;         //DEBUG!
                else                                                                                                            //DEBUG!
                    std::cout << YELLOW << "Debug: " << RESET << "User= " << (*it_user)->getNickname() << RESET << std::endl;   //DEBUG!
                if(it_user != userLst.end()){
                    _send_data_to_client(USER_MSG(client->getNickname(), current_user, data), (*it_user));
                }
                else{
                    _send_data_to_client(ERR_NOSUCHNICK(client->getNickname(), current_user), client);
                }
            }
            it_send++;
        }
    }
    else if(rawCmd.size() == 2){
        _send_data_to_client(ERR_NOTEXTTOSEND(client->getNickname()), client);
    }
}

        //    ERR_NORECIPIENT       j'arrive pas à trouver d'infos sur ce qu'est cette erreur !!!!!! (j'ai pas trop cherché en vrai)
        //    ERR_NOTEXTTOSEND      OK!
        //    ERR_CANNOTSENDTOCHAN  OK!
        //    ERR_TOOMANYTARGETS    OK!
        //    ERR_NOSUCHNICK        OK!
        //    RPL_AWAY              RPL à voir plus tard je vois pas à quoi ça sert...