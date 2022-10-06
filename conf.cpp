#include "conf.hpp"

config::config() : ip("127.0.0.1"), port(0), body(0), root(NULL)
{
	return ;
}

config & config::operator=(config const & rhs)
{
	if (this != &rhs)
	{
		this->ip = rhs.ip;
		this->port = rhs.port;
		this->body = rhs.body;
		this->root = rhs.root;
	}
	return *this;
}

config::config(config const & src)
{
	*this = src;
	return ;
}

config::~config()
{
	return ;
}

void	config::parsing(char *conf)
{
	std::string s;
	std::ifstream file(conf);
	if (!file)
	{
		std::cout << "Error: file not found\n";
		return ; // throw error
	}
	std::getline(file, s);
	if (s.find("server"))
		return ; // throw error
	while(std::getline(file, s))
	{
		if (s.find("body") != -1)
		{
			s.replace(s.find("body"), 4, "");
			std::istringstream(s) >> this->body;
		}
		if (s.find("server_name") != -1)
		{
			s.replace(s.find("server_name"), 11, "");
			s.erase(0, 2);
			std::istringstream(s) >> this->port;
		}
		if (s.find("root"))
		{
			s.replace(s.find("root"), 4, "");
			s.erase(0, 4);
			this->root = s;
		}
	}
	file.close();
}
