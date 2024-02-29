/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:20:42 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/29 19:11:14 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "User.hpp"

bool	syntax_mdp_channel(char c) {
	if (c == '\0' || c == '\r' || c == '\n' || c == '\f' || c == '\t' || c == '\v' || c == ' ')
		return (false);
	return (true);
}

bool	syntax_name_channel(char c) {
	if ( c == '\0' || c == '\a' || c == '\n' || c == '\r' || c == ' ')
		return (false);
	return (true);
}

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


//ca marche pas du tout
bool	user_is_op(std::vector<User*> op, std::string name) {
	for (std::vector<User*>::iterator it = op.begin(); it != op.end(); it++) {
		if (name.compare((*it)->getNickname()) == 0)
			return (true);
	}
	return (false);
}

std::string			list_user_to_string(std::vector<User*> users, std::vector<User*> op) {
	std::string		listuser;

	for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++) {
		if (user_is_op(op, (*it)->getNickname()))
			listuser += "@";
		listuser += (*it)->getNickname();
		if (it + 1 != users.end())
			listuser += " ";
	}
	return (listuser);
}
