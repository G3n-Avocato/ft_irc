/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:46:39 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/29 17:08:53 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

int main(int argv, char **argc){
    bot MyBot;

    if(MyBot.parsing_input(argv, argc))
        return (1);
    MyBot.bot_connect(argc[6]);

    std::string message = MyBot.receive_message(1024);
    while (true) {
        std::string message = MyBot.receive_message(1024);
        if(!message.empty()){
            std::cout << "Received " << message;
            MyBot.handle_message(message);
        }
    }
    return 0;
}