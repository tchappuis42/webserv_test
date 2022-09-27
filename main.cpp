/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:07:36 by ktrosset          #+#    #+#             */
/*   Updated: 2022/09/27 17:10:22 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_pars	parsing(int ac, char **av)
{
	t_pars pars;
	
	pars.ip = "127.0.0.1";
	if (ac == 1)
	{
		pars.port = 2000;
		pars.s_name = "tanguy";
		pars.body = 2000; 
	}
	else
	{
		std::string s;
		std::ifstream file(av[1]);
		if (!file)
		{
			std::cout << "Error: file not found\n";
			return (pars);
		}
		while(std::getline(file, s))
		{
			if (s.find("port") != -1)
			{
				s.replace(s.find("port"), 4, "");
				std::istringstream(s) >> pars.port;
			}
			if (s.find("body") != -1)
			{
				s.replace(s.find("body"), 4, "");
				std::istringstream(s) >> pars.body;
			}
			if (s.find("server_name") != -1)
			{
				s.replace(s.find("server_name"), 11, "");
				s.erase(0, 2);
				pars.s_name = s;
			}
		}
		file.close();
	}
	return (pars);
}

int main(int ac, char **av)
{
	if (ac > 2)
		return (0);
	t_pars pars;
	pars = parsing(ac, av);
	std::cout << pars.port << std::endl << pars.ip << std::endl << pars.body << std::endl << pars.s_name << std::endl;
	int socketServer = socket(AF_INET, SOCK_STREAM, 0);

	if ( socketServer < 0 ) {
		perror("Socket creation error!");
		exit (EXIT_FAILURE);
	}

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
