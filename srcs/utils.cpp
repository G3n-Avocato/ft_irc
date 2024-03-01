/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:20:42 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/01 16:59:03 by lamasson         ###   ########.fr       */
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

size_t	vector_search_user(std::vector<User*> list, std::string name) {
	size_t 	i = 0;
	while (i < list.size()) {
		if (name.compare((*list[i]).getNickname()) == 0)
			break ;
		i++;
	}
	return (i);
}

bool	vector_check_user(std::vector<User*> list, std::string name) {
	for (std::vector<User*>::iterator it = list.begin(); it != list.end(); it++) {
		if (name.compare((*it)->getNickname()) == 0)
			return (true);
	}
	return (false);
}

//fonction inutile pour le moment creer une string de la list des users avec un vector
std::string			list_user_to_string(std::vector<User*> users, std::vector<User*> op) {
	std::string		listuser;

	for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++) {
		if (vector_check_user(op, (*it)->getNickname()))
			listuser += "@";
		listuser += (*it)->getNickname();
		if (it + 1 != users.end())
			listuser += " ";
	}
	return (listuser);
}
