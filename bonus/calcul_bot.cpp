/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_bot.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:55:09 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/29 17:37:08 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

bool	bot::_parsing_nb(std::string tmp) {
	for (size_t i = 0; i < tmp.size(); i++) {
		if (!isdigit(tmp[i]))
			return (this->_string_error());
	}
	long int	max = strtol(tmp.c_str(), NULL, 10);
	if (max > INT_MAX) {
		this->_res_calcul = "Bot doesn't handle MAX_INT.";
		return (false);
	}
	if (!this->_parsing_verif(1))
		return (false);
	if (this->_check_precedence()) {
		tmp = this->_calculator_precedence(tmp);
		if (tmp.empty())
			return (false);
	}
	this->_calcul.push_back(tmp);
	return (true);
}

bool	bot::_parsing_verif(int i) {
	int	j = -1;
	if (!this->_calcul.empty()) {
		std::string	test = this->_calcul.back();
		if (!isdigit(test[i]))
			j = 0;
		else
			j = 1;
		if (j == i)
			return (this->_string_error());
	}
	return (true);
}

bool	bot::_check_precedence() {
	if (!this->_calcul.empty()) {
		std::string check = this->_calcul.back();
		if (check[0] == '*' || check[0] == '/')
			return (true);
	}
	return (false);
}

std::string	bot::_re_transformation(long int res) {
	std::stringstream	ss;
	ss << res;
	std::string	str = ss.str();
	return (str);
}

std::string	bot::_calculator_precedence(std::string s2) {
	std::string	op = this->_calcul.back();
	this->_calcul.pop_back();
	if (this->_calcul.empty()) {
		this->_res_calcul = "Syntax error for calcul.";
		return ("");
	}
	std::string	s1 = this->_calcul.back();
	this->_calcul.pop_back();

	long int	a = strtol(s1.c_str(), NULL, 10);
	long int	b = strtol(s2.c_str(), NULL, 10);
	if (op[0] == '*')
		a = a * b;
	else if (op[0] == '/') {
		if (b == 0) {
			this->_res_calcul = "Division by zero prohibited.";
			return ("");
		}
		a = a / b;
	}
	s1 = this->_re_transformation(a);
	return (s1);
}

bool	bot::_calculator_classic() {
	std::vector<std::string>::iterator it = this->_calcul.begin();
	long int	a = strtol((*it).c_str(), NULL, 10);
	it = this->_calcul.erase(it);
	long int	b;
	std::string	op;
	
	while (it != this->_calcul.end()) {
		op = (*it);
		it++;
		if (it == this->_calcul.end())
			return (this->_string_error());
		b = strtol((*it).c_str(), NULL, 10);
		if (op[0] == '+')
			a = a + b;
		else if (op[0] == '-')
			a = a - b;
		else
			break ;
		it = this->_calcul.erase(this->_calcul.begin(), this->_calcul.begin() + 2);
	}
	if (this->_calcul.empty() && this->_res_calcul.empty()) {
		this->_res_calcul = this->_re_transformation(a);
		return (true);
	}
	return (this->_string_error());
}

bool	bot::_parsing(std::string tmp) {
	if (tmp.empty())
		return (this->_string_error());
	if (tmp[0] != '+' && tmp[0] != '-' && tmp[0] != '/' && tmp[0] != '*') {
		if (!this->_parsing_nb(tmp))
			return (false);
	}
	else if (tmp.size() == 1 && (tmp[0] == '+' || tmp[0] == '-' || tmp[0] == '*' || tmp[0] == '/')) {
		if (!this->_parsing_verif(0))
			return (false);
		this->_calcul.push_back(tmp);
	}
	else
		return (this->_string_error());
	return (true);
}

bool	bot::_algo(std::string line) {
	std::string	tmp;
	size_t		pos = 0;

	for (size_t i = 0; i < line.size(); ) {
		pos = line.find(" ", i);
		if (pos != std::string::npos) {
			tmp = line.substr(i, pos - i);
			if (!this->_parsing(tmp))
				return (false);
			i = pos + 1;
		}
		else {
			tmp = line.substr(i, line.size() - i);
			if (!this->_parsing(tmp))
				return (false);
			break ;
		}
	}
	if (!this->_calculator_classic())
		return (false);
	return (true);
}

bool	bot::_string_error() {
	this->_res_calcul = "Syntax error for calcul.";
	return (false);
}

void	bot::_calcul_msg_to_string(std::string line) {
	this->_calcul.clear();
	this->_res_calcul.clear();
	this->_algo(line);
	this->_calcul.clear();
}
