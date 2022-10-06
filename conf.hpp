#ifndef CONF_HPP
# define CONF_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

class config
{
	public:
			config();
			config & operator=(config const & rhs);
			config(config const & src);
			~config();
	
			void	parsing(char *conf);
	
	private:
			std::string	ip;
			int			port;
			int			body;
			std::string	root;	
};

#endif