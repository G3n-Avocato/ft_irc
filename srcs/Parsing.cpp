/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:03:06 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/28 14:55:33 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/User.hpp"

std::vector<std::string> User::_string_to_vector(std::string str, std::string arg, int i) {
    std::vector<std::string>    str_vector;
	std::string                 token;
	size_t                      pos = 0;

    while (str.length() > 0) {
        pos = str.find(arg.c_str());
		if (pos == std::string::npos) {
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

//refound vector-> to string if cmd not end 
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
	
	std::cout << "buf client = " << buf << "." << std::endl;

	if (buf.size() == 1 && buf[0] == '\n') {
		this->_end = 0;
		return ;
	}
	
	if (!this->_end && !this->_cmd.empty()) {
		buf = this->_recast_buf_end(this->_cmd.back(), buf);
		this->_cmd.erase(this->_cmd.end() - 1);
	}

	if (buf.find("\r\n") != std::string::npos)
    	raw_cmd = this->_string_to_vector(buf, "\r\n", 1);
	else
		raw_cmd = this->_string_to_vector(buf, "\n", 1);
	
	for (std::vector<std::string>::iterator it = raw_cmd.begin(); it != raw_cmd.end(); it++)
        this->_cmd.push_back(this->_string_to_vector(*it, " ", 2));
}
