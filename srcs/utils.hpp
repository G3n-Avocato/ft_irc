/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:31:08 by lamasson          #+#    #+#             */
/*   Updated: 2024/03/01 16:55:08 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <string>
#include <vector>

class User;

bool						syntax_mdp_channel(char c);
bool						syntax_name_channel(char c);
std::vector<std::string>	string_to_vector_(std::string, std::string);

size_t						vector_search_user(std::vector<User*> list, std::string name);

bool						vector_check_user(std::vector<User*> list, std::string name); 
std::string					list_user_to_string(std::vector<User*> users, std::vector<User*> op);
