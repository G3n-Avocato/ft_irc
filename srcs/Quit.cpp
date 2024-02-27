/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 00:30:25 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/02/27 00:43:57 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include "Error.hpp"

void	Command::_cmd_QUIT(std::vector<std::string>, User* client, Server* opt)
{

	int socket = client->getSocket();

	opt->deleteUser(socket);
	
	std::cout << "-----COMMAND QUIT SUCCESS FOR CLIENT " << socket << "-----" << std::endl; 
}
 