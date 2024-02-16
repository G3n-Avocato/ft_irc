/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:36:58 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/16 23:29:03 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

class User {
	public:

		User();
		~User();

		void	setnickname(const char *nick);
		void	setusername(const char *usern);
		void	sethostname(const char *host);
		void	setservname(const char *name);

	private:
		
		User(const User&);
		User&	operator=(const User&);

		char	_nickname;
		char	*_username;
		char	*_hostname;
		char	*_servname;
		

		//list channel ?
};
