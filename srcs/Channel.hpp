/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:10 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/14 22:50:15 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>

class Channel {
	public:
		
		Channel();
		~Channel();

		void	setnamechan(const char* name);


	private:
		
		char						_name_chan[200];
		std::vector<std::string>	_operator;
		std::string					_pass_chan;
		int							_limit_user;

		bool						_invite;
		bool						_pass;
		bool						_limituse;

};
