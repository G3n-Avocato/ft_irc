/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:46:27 by ecorvisi          #+#    #+#             */
/*   Updated: 2024/03/29 19:11:39 by ecorvisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void    bot::set_server_info(std::string ip, int port, std::string pass){
    this->server_ip = ip;
    this->server_port = port;
    this->server_pass = pass;
}
void    bot::set_bot_info(std::string nick, std::string user, std::string name){
    this->bot_nick = nick;
    this->bot_user = user;
    this->bot_name = name;
}

void bot::send_message(const std::string& message) {
    send(this->server_socket, message.c_str(), message.size(), 0);
}


void bot::check_error(std::string flag){
    std::string message = receive_message(1024);

    std::cout << flag << std::endl;
    if(message.empty()){
        std::cout << "Empty Error!" << std::endl; 
        return;
    }

    size_t pos = message.find(flag);
    std::cout << message << std::endl;

    if(pos != std::string::npos){
        std::cout << "Error: Your Nickname and already used on this server." << std::endl;
        exit(1);
    }
}

void bot::bot_connect(std::string to_channel){
    this->bot_chan = to_channel;
    this->server_address.sin_family = AF_INET;
    this->server_address.sin_port = htons(this->server_port);
    // std::cout << "IP = " << this->server_ip << std::endl;
    inet_pton(AF_INET, this->server_ip.c_str(), &this->server_address.sin_addr);

    // Attempt connection
    int result = connect(this->server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (result == -1 && (errno != EINPROGRESS)) {
        std::cerr << "Failed to connect to server" << std::endl << errno << std::endl;
        close(this->server_socket);
        return;
    }
    else if (result == -1 && (errno == EINPROGRESS || errno == EWOULDBLOCK))
    {

        // Wait for connection to complete
        fd_set writefds;
        FD_ZERO(&writefds);
        FD_SET(this->server_socket, &writefds);
    
        struct timeval timeout;
        timeout.tv_sec = 10;  // Adjust the timeout as needed
        timeout.tv_usec = 0;
        
        result = select(this->server_socket + 1, NULL, &writefds, NULL, &timeout);
        if (result > 0 && FD_ISSET(this->server_socket, &writefds)) {
            std::cout << "Connected successfully" << std::endl;
            send_message("PASS " + this->server_pass + "\r\n");
            send_message("NICK " + this->bot_nick + "\r\n");
            send_message("USER " + this->bot_user + " 0 * :realname" + "\r\n");
            send_message("JOIN " + this->bot_chan + "\r\n");
        } else {
            std::cerr << "Failed to connect to server within timeout" << std::endl;
        }
    }
    else {
                        std::cout << "Connected successfully" << std::endl;
            send_message("PASS " + this->server_pass + "\r\n");
            send_message("NICK " + this->bot_nick + "\r\n");
            send_message("USER " + this->bot_user + " 0 * :realname" + "\r\n");
            send_message("JOIN " + this->bot_chan + "\r\n");
    }
        // Connection established

    // close(this->server_socket);
}

// void bot::bot_connect(std::string to_channel){
//     this->bot_chan = to_channel;
//     this->server_address.sin_family = AF_INET;
//     this->server_address.sin_port = htons(this->server_port);
//     std::cout << "IP = " << this->server_ip << std::endl;
//     inet_pton(AF_INET, this->server_ip, &this->server_address.sin_addr);

//     if (connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
//         if (errno == EINPROGRESS) {
//             std::cerr << "Failed to connect to server" << std::endl;
//             return;
//         }
//         std::cout << "debug : " << errno << std::endl;
//     }
//     send_message("PASS " + this->server_pass + "\r\n");
//     // check_error("000");
//     send_message("NICK " + this->bot_nick + "\r\n");
//     check_error(": 433");
//     send_message("USER " + this->bot_user + " 0 * :realname" + "\r\n");
//     // check_error("000");
//     send_message("JOIN " + this->bot_chan + "\r\n");
//     // check_error("000");
// }

size_t find_second_occurrence(const std::string& str, char target) {
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
     size_t second_occurrence_position = find_second_occurrence(message, ':');
    if (second_occurrence_position != std::string::npos) {
        std::string after_second_occurrence = message.substr(second_occurrence_position + 1);
        if (after_second_occurrence.find("!calcul ") == 0) {
            size_t end_position = after_second_occurrence.find(endStr);
            if (end_position != std::string::npos) {
                std::string calculation = after_second_occurrence.substr(8, end_position);
                size_t end_position = calculation.find(endStr);
                calculation.replace(end_position, endStr.length(), "\0");
                this->_calcul_msg_to_string(calculation);
                send_message("PRIVMSG " + this->bot_chan + " :" + this->_res_calcul + "\r\n");
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
            exit(1);
        }
        else
            return "";
    }
    buffer[bytes_received] = '\0';
    std::string msg = static_cast<std::string>(buffer);
    return msg;
}


int bot::get_server_socket(){
    return this->server_socket;
}

bot::bot()
{
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }
    int flags = fcntl(server_socket, F_GETFL, 0);
    fcntl(server_socket, F_SETFL, flags | O_NONBLOCK);
}

bot::~bot()
{
}