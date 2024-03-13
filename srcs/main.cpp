/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:06:24 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/16 15:19:37 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <signal.h>

void	signal_sigint(int signal)
{
	(void)signal;
	throw std::logic_error("\nServer Closed !\n");
}

int	main(int argc, char **argv) {

	if (argc != 3)
		return (1);

	regex_t	regex;
	regcomp(&regex, "^[a-zA-Z+-:@-Za-{}~_^=%# ]{0,50}$", REG_EXTENDED);

	if (regexec(&regex, argv[2], 0, NULL, 0) == REG_NOMATCH)
	{
		regfree(&regex);
		std::cout << "Error: Password not allowed" << std::endl;
		return (1);
	}
	regfree(&regex);
	regex_t	regex2;
	regcomp(&regex2, "^(102[4-9]|10[3-9][0-9]|1[1-9][0-9][0-9]|[2-9][0-9][0-9][0-9]|[1-5][0-9][0-9][0-9][0-9]|6[0-4][0-9][0-9][0-9]|65[0-4][0-9][0-9]|655[0-2][0-9]|6553[0-5])$", REG_EXTENDED);
	if (regexec(&regex2, argv[1], 0, NULL, 0) == REG_NOMATCH)
	{
		regfree(&regex2);
		std::cout << "Error: Port not allowed" << std::endl;
		return (1);
	}
	regfree(&regex2);

	try {
		signal(SIGINT, signal_sigint);
		Server	start(argv[1], argv[2]);
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}
	return (0);
}