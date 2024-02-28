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

// #include "Command.hpp"
#include "Server.hpp"

//
#define RESET   "\033[0m"
#define BLACK   "\033[30m"                  /* Black */
#define RED     "\033[31m"                  /* Red */
#define GREEN   "\033[32m"                  /* Green */
#define YELLOW  "\033[33m"                  /* Yellow */
#define BLUE    "\033[34m"                  /* Blue */
#define MAGENTA "\033[35m"                  /* Magenta */
#define CYAN    "\033[36m"                  /* Cyan */
#define WHITE   "\033[37m"                  /* White */
#define BOLDBLACK   "\033[1m\033[30m"       /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"       /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"       /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"       /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"       /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"       /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"       /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"       /* Bold White */
//

std::string	rebuild_data(std::vector<std::string> last, int start) {
	std::string	tmp;
	
	for (std::vector<std::string>::iterator it = last.begin() + start; it != last.end(); it++) {
		tmp += *it;
		if (it + 1 != last.end())
			tmp += " ";
	}
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
    std::map<std::string, Channel*> channeLst   = server->getListChannel();

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
                //send_to_channel(current_user, data);
                std::cout << RED << "Warning: " << RESET << "Function 'send_to_channel' not supported !" << std::endl; //DEBUG!
            }
            else{
                std::vector<User*>::iterator it_user = userLst.begin();
                while (it_user != userLst.end()) {
                    if (!current_user.compare((*it_user)->getNickname()))
                        break ;
                    it_user++;
                }
                if (it_user == userLst.end())
                    std::cout << YELLOW << "Debug: " << RESET << "User '" << current_user << "' not fond."<< std::endl; //DEBUG!
                else
                    std::cout << YELLOW << "Debug: " << RESET << "User= " << (*it_user)->getNickname() << RESET << std::endl; //DEBUG!
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

        //    ERR_NORECIPIENT
        //    ERR_NOTEXTTOSEND      OK!
        //    ERR_CANNOTSENDTOCHAN
        //    ERR_TOOMANYTARGETS    OK!
        //    ERR_NOSUCHNICK        OK!
        //    RPL_AWAY