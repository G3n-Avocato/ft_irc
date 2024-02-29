/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:31:08 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/29 17:42:25 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <string>
#include <vector>

class User;

bool						syntax_mdp_channel(char c);
bool						syntax_name_channel(char c);
std::vector<std::string>	string_to_vector_(std::string, std::string);

bool						user_is_op(std::vector<User*> op, std::string name); 
std::string					list_user_to_string(std::vector<User*> users, std::vector<User*> op);
