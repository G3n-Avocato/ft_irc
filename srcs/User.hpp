/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:36:58 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/14 22:49:26 by lamasson         ###   ########.fr       */
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
		void	setpass_user(const char *pass);

	private:
		
		User(const User&);
		User&	operator=(const User&);

		char	_nickname[9];
		char	*_username;
		char	*_hostname;
		char	*_servname;
		char	*_pass_user;
		
		bool	_chanop;

		//list channel ?
};
