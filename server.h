#ifndef SERVER_H
# define SERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

typedef struct s_pars
{
	std::string	ip;
	int			port;
	int			body;
	std::string	s_name;
}	t_pars;

#endif