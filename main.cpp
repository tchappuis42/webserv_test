/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:07:36 by ktrosset          #+#    #+#             */
/*   Updated: 2022/09/26 16:29:20 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_pars	parsing(int ac, char **av)
{
	t_pars pars;
	if (ac == 1)
	{
		pars.ip = "127.0.0.1";
		pars.port = 2000;
		pars.s_name = "tanguy";
		pars.body = 2000; 
	}
	return (pars);
}

int main(int ac, char **av)
{
	t_pars pars;
	pars = parsing(ac, av);
	std::cout << pars.port << std::endl << pars.ip << std::endl;
	int socketServer = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addrServer;

	addrServer.sin_addr.s_addr = inet_addr(pars.ip.c_str());
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(pars.port);

	bind(socketServer, (const struct sockaddr *)&addrServer, sizeof (addrServer));
	std::cout << "bind : " << socketServer << std::endl;

	listen(socketServer, 5);
	std::cout << "listen" << std::endl;

	struct sockaddr_in addrClient;
	socklen_t csize = sizeof(addrClient);
	int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
	std::cout << "accept" << std::endl;

	std::cout << "client : " << socketClient << std::endl;
}