/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arforgea <arforgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:46:39 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/30 16:38:53 by arforgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <signal.h>

void	signal_sigint(int signal)
{
	(void)signal;
	throw std::logic_error("\nBot Close.\n");
}

int main(int argv, char **argc){
    try {
        Bot MyBot;
        signal(SIGINT, signal_sigint);
        if(MyBot.parsing_input(argv, argc))
            return (1);
        MyBot.bot_connect(argc[6]);

        while (true) {
            std::string message = MyBot.receive_message(1024);
            if(!message.empty()){
                std::cout << "Received " << message;
                MyBot.handle_message(message);
            }
        }
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}
    return 0;
}