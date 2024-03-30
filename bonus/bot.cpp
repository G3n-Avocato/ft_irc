/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arforgea <arforgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:46:27 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/29 22:27:30 by arforgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

bot::bot() {
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }
    int flags = fcntl(server_socket, F_GETFL, 0);
    fcntl(server_socket, F_SETFL, flags | O_NONBLOCK);
}

bot::~bot() {
    close(this->server_socket);
}

void    bot::_set_server_info(std::string ip, int port, std::string pass){
    this->server_ip = ip;
    this->server_port = port;
    this->server_pass = pass;
}

void    bot::_set_bot_info(std::string nick, std::string user, std::string name){
    this->bot_nick = nick;
    this->bot_user = user;
    this->bot_name = name;
}

void bot::_send_message(const std::string& message) {
    send(this->server_socket, message.c_str(), message.size(), 0);
}

void bot::_check_error(std::string flag){
    std::string message = receive_message(1024);

    if(message.empty()){
        std::cout << "Empty Error!" << std::endl; 
        return;
    }

    size_t pos = message.find(flag);
    std::cout << message << std::endl;

    if(pos != std::string::npos){
        std::cout << "Error: Your Nickname and already used on this server." << std::endl;
        throw std::logic_error("Bot close.\n");
    }
}

void bot::bot_connect(std::string to_channel) {
    this->bot_chan = to_channel;
    this->server_address.sin_family = AF_INET;
    this->server_address.sin_port = htons(this->server_port);
    inet_pton(AF_INET, this->server_ip.c_str(), &this->server_address.sin_addr);

    // Try non-blocking connexion
    if (connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        if (errno != EINPROGRESS) {
            std::cerr << "Failed to connect to server" << std::endl;
            return;
        }
    }
    else {
        this->_try_send_co();
        return;
    }

    // use select() for check connexion
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(server_socket, &writefds);

    struct timeval timeout;
    timeout.tv_sec = 10; // Time wait 10s max
    timeout.tv_usec = 0;

    int select_result = select(server_socket + 1, NULL, &writefds, NULL, &timeout);
    if (select_result == -1) {
        std::cerr << "Error in select()" << std::endl;
        return;
    }
    else if (select_result == 0) {
        std::cerr << "Timeout occurred while connecting" << std::endl;
        return;
    }

    if (FD_ISSET(server_socket, &writefds)) {
        int error = 0;
        socklen_t len = sizeof(error);
        getsockopt(server_socket, SOL_SOCKET, SO_ERROR, &error, &len);

        if (error != 0) {
            std::cerr << "Error occurred while connecting: " << strerror(error) << std::endl;
            return;
        }
        this->_try_send_co();
    }
}

void    bot::_try_send_co() {
    std::cout << "Connected successfully" << std::endl;
    this->_send_message("PASS " + this->server_pass + "\r\n");
    this->_send_message("NICK " + this->bot_nick + "\r\n");
    this->_check_error(": 433");
    this->_send_message("USER " + this->bot_user + " 0 * :realname" + "\r\n");
    this->_send_message("JOIN " + this->bot_chan + "\r\n");
}

size_t  bot::_find_second_occurrence(const std::string& str, char target) {
    size_t first_occurrence = str.find(target);
    if (first_occurrence != std::string::npos) {
        size_t second_occurrence = str.find(target, first_occurrence + 1);
        return second_occurrence;
    }
    return std::string::npos;
}

void bot::handle_message(const std::string message) {
    if(message.empty())
        return;
    std::string endStr = "\r\n";
     size_t second_occurrence_position = this->_find_second_occurrence(message, ':');
    if (second_occurrence_position != std::string::npos) {
        std::string after_second_occurrence = message.substr(second_occurrence_position + 1);
        if (after_second_occurrence.find("!calcul ") == 0) {
            size_t end_position = after_second_occurrence.find(endStr);
            if (end_position != std::string::npos) {
                std::string calculation = after_second_occurrence.substr(8, end_position);
                size_t end_position = calculation.find(endStr);
                calculation.replace(end_position, endStr.length(), "\0");
                this->_calcul_msg_to_string(calculation);
                this->_send_message("PRIVMSG " + this->bot_chan + " :" + this->_res_calcul + "\r\n");
            }
        }
    }
}

std::string bot::receive_message(const int buffer_size) {
    char buffer[buffer_size];
    int bytes_received = recv(server_socket, buffer, buffer_size, 0);
    if (bytes_received <= 0){
        if (bytes_received == 0){
            std::cout << "Disconnected from server" << std::endl;
            close(this->server_socket);
            throw std::logic_error("Bot close.\n");
        }
        else
            return "";
    }
    buffer[bytes_received] = '\0';
    return buffer;
}

int bot::get_server_socket() {
    return this->server_socket;
}

bool bot::parsing_input(int size, char **input) {
    if(size < 6) {
        std::cout << size << std::endl;
        std::cout << "Error Input ( \"IP\" \"Port\" \"Password\" \"Nickname\" \"Username\" \"Channel\" )" << std::endl;
        return true;
    }
    std::string str(input[2]);
    long int         port = strtol(input[2], NULL, 10);
    if(port < 1024 || port > 65535) {
        std::cout << "Error Port max is 65535 you port is: " << input[2] << std::endl;
        return true;
    }
    if(input[6][0] != '#') {
        std::cout << "Error Bad Channel Name example: #loby" << std::endl;
        return true;
    }
    this->_set_server_info(input[1], port, input[3]);
    this->_set_bot_info(input[4], input[4], input[5]);
    this->bot_chan = input[6];
    return false;
}
