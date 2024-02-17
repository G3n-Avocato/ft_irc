/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:10 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/17 16:13:52 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>

class User;

class Channel {
	public:
		
		Channel();
		~Channel();

		void	setnamechan(const char* name);

	private:
		
		std::string					_name_chan;
		std::vector<std::string>	_operator;
		std::vector<User*>			_users;
		std::string					_pass_chan;
		int							_limit_user;

		bool						_invite;
		bool						_pass;
		bool						_limituse;

};
