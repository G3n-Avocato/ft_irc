/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:03:06 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/26 17:48:51 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

std::vector<std::string> User::_string_to_vector(std::string str, std::string arg, int i) {
    std::vector<std::string>    str_vector;
	std::string                 token;
	size_t                      pos = 0;

    while (str.length() > 0) {
        pos = str.find(arg.c_str());
		if (pos == std::string::npos) {
			std::cout << "test no rn " << i << std::endl;
			if (i == 1)
				this->_end = 0;
            pos = str.length();
		}
		else {
			if (i == 1)
				this->_end = 1;
		}
   	    token = str.substr(0, pos);
        str_vector.push_back(token);
        str.erase(0, pos + arg.length());
    }
    return (str_vector);
}

std::string	User::_recast_buf_end(std::vector<std::string> last, std::string buf) {
	std::string	tmp;
	
	for (std::vector<std::string>::iterator it = last.begin(); it != last.end(); it++) {
		tmp += *it;
		if (it + 1 != last.end())
			tmp += " ";
	}
	tmp += buf;
	return (tmp);
}

void User::setcmdParser(char *client_buff){
	std::string 							buf(client_buff);
    std::vector<std::string>				raw_cmd;

	if (!this->_end) {
		buf = this->_recast_buf_end(this->_cmd.back(), buf);
		std::cout << std::endl << "--- buf assemble ------ " << std::endl << buf << std::endl;
		this->_cmd.erase(this->_cmd.end() - 1);
	}
    raw_cmd = _string_to_vector(buf, "\r\n", 1);
    for (std::vector<std::string>::iterator it = raw_cmd.begin(); it != raw_cmd.end(); it++) {
        this->_cmd.push_back(_string_to_vector(*it, " ", 2));
	}
}
