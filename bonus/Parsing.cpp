/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:46:42 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/29 15:46:45 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

// "127.0.0.1" "4444" "1234" "Jimmy" "MyBot" "#loby"

static int stoi(std::string &s) {
    int i;
    std::istringstream(s) >> i;
    return i;
}

bool bot::parsing_input(int size, char **input){

    if(size < 6){
        std::cout << size << std::endl;
        std::cout << "Error Input ( \"IP\" \"Port\" \"Password\" \"Nickname\" \"Username\" \"Channel\" )" << std::endl;
        return true;
    }
    std::string port(input[2]);
    if(stoi(port) > 65535){
        std::cout << "Error Port max is 65535 you port is: " << input[2] << std::endl;
        return true;
    }
    if(input[6][0] != '#'){
        std::cout << "Error Bad Channel Name example: #loby" << std::endl;
        return true;
    }
    set_server_info(input[1], stoi(port), input[3]);
    set_bot_info(input[4], input[4], input[5]);
    this->bot_chan = input[6];
    return false;
}