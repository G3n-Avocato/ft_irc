/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:36:58 by lamasson          #+#    #+#             */
/*   Updated: 2024/02/13 21:48:46 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

class User {
	public:

		User();
		~User();

		void	setnickname(char *nick);
		void	setusername(char *usern);
		void	setpassword(char *pass);

	private:

		char	*_nickname;
		char	*_username;
		char	*_password;
		bool	_chanop;

};
