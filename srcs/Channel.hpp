/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:10 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/18 16:08:46 by lamasson         ###   ########.fr       */
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

		void	setName(std::string name);
		bool	getFlagInvite() const;
		bool	getFlagPass() const;
		bool	getFlagLimit() const;

	private:
		
		std::string					_name;
		std::vector<std::string>	_operator;
		std::vector<User*>			_users;
		std::string					_pass;
		int							_limit_user;

		bool						_invite;
		bool						_p;
		bool						_limit;

};
