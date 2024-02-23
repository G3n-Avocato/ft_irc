/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:49:43 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/02/23 15:00:17 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Error.hpp"

int	Command::cmd_PASS(std::vector<std::string> cmd, std::string pass) 
{
	if (cmd.size() < 2)
	{
		std::cout << "MORE PARAMS" << std::endl;//ERR_NEEDMOREPARAMS
		return (1);
	}
	if (cmd[1] == pass)
	{
		std::cout << "PASSWORD IS OK!" << std::endl;
		return (0);
	}
	return (1);
}
//ERR_ALREADYREGISTRED