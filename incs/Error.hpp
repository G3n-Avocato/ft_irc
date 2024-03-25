/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorvisi <ecorvisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:28:39 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/08 00:27:41 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#define ERR_NOSUCHNICK(client, nick) (": 401 " + client + " " + nick + " :No such nick\r\n")
#define ERR_NOSUCHCHANNEL(client, canal) (": 403 " + client + " " + canal + " :No such channel\r\n")
#define ERR_CANNOTSENDTOCHAN(client, canal) (": 404 " + client + " " + canal + " :Cannot send to channel\r\n")
#define ERR_TOOMANYCHANNELS(client, canal) (": 405 " + client + " " + canal + " :You have joined too many channels\r\n")
#define ERR_TOOMANYTARGETS(nick) (": 407 " + nick + " :Duplicate recipients. No message delivered\r\n")

#define ERR_NORECIPIENT(client, cmd) (": 411 " + client + " :No recipient given " + cmd + "\r\n")
#define ERR_NOTEXTTOSEND(client) (": 412 " + client + " :No text to send\r\n")
#define ERR_NONICKNAMEGIVEN(client) (": 431 " + client + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(client, nick) (": 432 " + client + " " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(client, nick) (": 433 " + client + " " + nick + " :Nickname is already in use\r\n")
#define ERR_USERNOTINCHANNEL(client, target, canal) (": 441 " + client + " " + target + " " + canal + " :They aren't on that channel\r\n")
#define ERR_NOTONCHANNEL(client, canal) (": 442 " + client + " " + canal + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL(client, pseudo, canal) (": 443 " + client + " " + pseudo + " " + canal + " :is already on channel\r\n")
#define ERR_NOTREGISTERED(client) (": 451 " + client + " :You have not registered\r\n")

#define ERR_NEEDMOREPARAMS(client, cmd) (": 461 " + client + " " + cmd + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED(client) (": 462 " + client + " :You may not reregister\r\n")
#define ERR_KEYSET(client, canal) (": 467 " + client + " " + canal + " :Channel key already set\r\n")
#define ERR_CHANNELISFULL(client, canal) (": 471 " + client + " " + canal + " :Cannot join channel (+l)\r\n")
#define ERR_UNKNOWNMODE(client, str) (": 472 " + client + " " + str + " :is unknown mode char to me\r\n")
#define ERR_INVITEONLYCHAN(client, canal) (": 473 " + client + " " + canal + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(client, canal) (": 475 " + client + " " + canal + " :Cannot join channel (+k)\r\n")

#define ERR_CHANOPRIVSNEEDED(client, canal) (": 482 " + client + " " + canal + " :You're not channel operator\r\n")
#define ERR_UMODEUNKNOWNFLAG(client) (": 501 " + client + " :Unknown MODE flag\r\n")
#define ERR_USERSDONTMATCH(client) (": 502 " + client + " :Can't change mode for other users\r\n")

#define RPL_CHANNELMODEIS(client, canal, mode, para) (": 324 " + client + " " + canal + " " + mode + " " + para + "\r\n")
#define RPL_NOTOPIC(client, canal) (": 331 " + client + " " + canal + " :No topic is set\r\n")
#define RPL_TOPIC(client, canal, sujet) (": 332 " + client + " " + canal + " :" + sujet + "\r\n")
#define RPL_INVITING(client, pseudo, canal) (": 341 " + client + " " + pseudo + " " + canal + "\r\n")
#define RPL_NAMREPLY(client, canal, listuser) (": 353 " + client + " = " + canal + " : " + listuser + "\r\n")

#define RPL_WELCOME(client) (": 001 " + client + " :Welcome to Internet Relay Network " + client + "\r\n")
#define RPL_JOIN(client, canal) (":" + client + " JOIN " + canal + "\r\n")
#define RPL_PART(client, canal, msg) (":" + client + " PART " + canal + " :" + msg + "\r\n")
#define RPL_INVITE(client, pseudo, canal) (":" + client + " INVITE " + pseudo + " :" + canal + "\r\n")
#define RPL_KICK(client, pseudo, canal, msg) (":" + client + " KICK " + canal + " " + pseudo + " :" + msg + "\r\n")
#define RPL_QUIT(client, msg) (":" + client + " QUIT :Quit: " + msg + "\r\n")
#define RPL_PASSNEED() ("You need the Password before\r\n")
#define RPL_NICKNEED() ("You need the Nickname before\r\n")

#define USER_MSG(client, target, msg) (":" + client + " PRIVMSG " + target + " :" + msg + "\r\n")
#define CHAN_MSG(client, channel, msg) (":" + client + " PRIVMSG " + channel + " :" + msg + "\r\n")
