/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:07:36 by ktrosset          #+#    #+#             */
/*   Updated: 2022/09/27 14:20:49 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int ac, char **av)
{
	char buf[50000];
	int nbytes;
	int socketServer = socket(AF_INET, SOCK_STREAM, 0);

	if ( socketServer < 0 ) {
    perror("Socket creation error!");
    exit (EXIT_FAILURE);
	}

	struct sockaddr_in addrServer;
	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(8082);

	bind(socketServer, (const struct sockaddr *)&addrServer, sizeof (addrServer));
	listen(socketServer, 1);

	struct sockaddr_in addrClient;
	socklen_t csize = sizeof(addrClient);
	int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);

if ( connect( socketServer, (struct sockaddr *) &addrServer, sizeof( addrServer ) ) < 0 ) {
    perror("Connect process error!");
    exit (EXIT_FAILURE);
}
	while ( 1 ) 
	{
		nbytes = 0;
		ioctl( socketServer, FIONREAD, &nbytes );

		if ( !nbytes ) { break; }
		else {
			memset( buf, 0, sizeof( buf ) );
			nbytes = read( socketServer, buf, sizeof( buf ) -1 );
			printf("%s", buf);
			printf(">>>%d<<<\n", nbytes);  // for debug
   			 }
		usleep( 300000 );   // delay
	}
	close(socketServer);

}
