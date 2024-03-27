/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_bot.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:59:44 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/23 16:43:51 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <vector>
#include <string>


class Bot {
	
	public:
		Bot();
		~Bot();

		void	_calcul_msg_to_string(std::string); //a mettre en private , ici en public pour pouvoir tester avec main, main a enlever aussi 

	private:
		std::vector<std::string>	_calcul;
		std::string					_res_calcul;
		
		bool		_parsing_nb(std::string);
		bool		_parsing_verif(int);
		bool		_check_precedence();
		std::string	_re_transformation(long int);
		std::string	_calculator_precedence(std::string);
		bool		_calculator_classic();
		bool		_parsing(std::string);
		bool		_algo(std::string);
		bool		_string_error();

};
