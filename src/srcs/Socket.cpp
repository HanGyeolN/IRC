#include "Socket.hpp"
#include "Reply.hpp"
#include "IrcServer.hpp"
#include <fcntl.h>

Socket::Socket() : _recv_bytes(0), _sent_bytes(0), _recv_cnt(0), _sent_cnt(0)
{
	memset(&_addr, 0, sizeof(_addr));
	time(&_start_time);
	time (&_last_action);
}

Socket::Socket(const char *port) : _recv_bytes(0), _sent_bytes(0), _recv_cnt(0), _sent_cnt(0)
{
	int	set = 1;

	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1)
		throw (Error("socket construct error"));
<<<<<<< HEAD:src/srcs/Socket.cpp
	setsockopt(_fd, SOL_SOCKET, MSG_NOSIGNAL, (void *)&set, sizeof(int));
=======
	setsockopt(_fd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
>>>>>>> master:srcs/Socket.cpp
	memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	_addr.sin_port = htons(ft::atoi(port));
	time(&_start_time);
	time(&_last_action);
}

Socket::Socket(unsigned short port) : _recv_bytes(0), _sent_bytes(0), _recv_cnt(0), _sent_cnt(0)
{
	int	set = 1;

	_fd = socket(AF_INET, SOCK_STREAM, 0);
<<<<<<< HEAD:src/srcs/Socket.cpp
	setsockopt(_fd, SOL_SOCKET, MSG_NOSIGNAL, (void *)&set, sizeof(int));
=======
	setsockopt(_fd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
>>>>>>> master:srcs/Socket.cpp
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
		throw(Error("fcntl returned -1"));
	memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	_addr.sin_port = port;
	time(&_start_time);
	time(&_last_action);
}

Socket::Socket(struct sockaddr_in serv_addr) : _recv_bytes(0), _sent_bytes(0), _recv_cnt(0), _sent_cnt(0)
{
	int	set = 1;

	_fd = socket(AF_INET, SOCK_STREAM, 0);
<<<<<<< HEAD:src/srcs/Socket.cpp
	setsockopt(_fd, SOL_SOCKET, MSG_NOSIGNAL, (void *)&set, sizeof(int));
=======
	setsockopt(_fd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
>>>>>>> master:srcs/Socket.cpp
	memset(&_addr, 0, sizeof(_addr));
	_addr = serv_addr;
	time(&_start_time);
	time(&_last_action);
}

Socket::Socket(Socket const &copy) : _fd(copy._fd), _addr(copy._addr), _recv_bytes(copy._recv_bytes), _sent_bytes(copy._sent_bytes)
{
}

Socket &Socket::operator=(Socket const &copy)
{
	if (_fd)
		close(_fd);
	_fd = copy._fd;
	_addr = copy._addr;
	time(&_last_action);
	return (*this);
}

Socket::~Socket()
{
	close(_fd);
}

void Socket::bind() const
{
	if (::bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw(Error("socket bind error"));
}

void Socket::listen() const
{
	if (::listen(_fd, 5) == -1)
		throw(Error("socket listen error"));
}

/*
** 1번 서버에 2번 서버가 연결 요청
** socket함수 호출
** sockaddr_in 구조체에 값 채워넣음
** 1번 서버와 2번 서버 connect로 연결
** 연결 되면 password 확인
** password 틀리면 연결 끊고 종료
*/

// first: host
// second: password
std::pair<struct sockaddr_in, std::string> Socket::parsing_host_info(const char *connect)
{
	std::string *split_ret;
	std::string string_host;
	std::string string_port_network;
	std::string string_password_network;
	struct sockaddr_in host;

	if (ft::split(connect, ':', split_ret) != 3)
		throw(Error("invalid host info"));
	string_host = split_ret[0];
	string_port_network = split_ret[1];
	string_password_network = split_ret[2];
	host.sin_family = AF_INET;
	host.sin_addr.s_addr = inet_addr(string_host.c_str());
	host.sin_port = htons(ft::atoi(string_port_network.c_str()));
	if (host.sin_addr.s_addr == -1)
		throw(Error("inet_addr() error"));
	delete[] split_ret;
	return (std::make_pair(host, string_password_network));
};

// 127.0.0.1:port:pass
Socket *Socket::connect(const char *connect_srv)
{
	Socket *new_sock;
	struct sockaddr_in serv_addr;
	std::pair<struct sockaddr_in, std::string> pair;

	memset(&serv_addr, 0, sizeof(serv_addr));
	pair = parsing_host_info(connect_srv);
	serv_addr = pair.first;

	// new_sock = new Socket(serv_addr.sin_port);
	new_sock = new Socket(serv_addr);
	new_sock->set_pass(pair.second);
	if (new_sock->_fd == -1)
		throw(Error("connect socket create error"));
	if (::connect(new_sock->_fd, (struct sockaddr *)&new_sock->_addr, sizeof(new_sock->_addr)) == -1)
	{
		if (errno != EINPROGRESS)
			throw (Error("socket connect error"));
	}
	fcntl(new_sock->_fd, F_SETFL, O_NONBLOCK);
	return (new_sock);
}

Socket *Socket::accept() const
{
	Socket *new_socket;
	struct sockaddr_in client_addr;
	int client_sock;
	socklen_t clnt_addr_size;
	int	set = 1;

	clnt_addr_size = sizeof(client_addr);
	client_sock = ::accept(_fd, (struct sockaddr *)&client_addr, &clnt_addr_size);
	if (client_sock < 0)
		throw(Error("socket accept error"));

	// copy
	new_socket = new Socket();
	new_socket->_fd = client_sock;
<<<<<<< HEAD:src/srcs/Socket.cpp
	setsockopt(_fd, SOL_SOCKET, MSG_NOSIGNAL, (void *)&set, sizeof(int));
=======
	setsockopt(_fd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
>>>>>>> master:srcs/Socket.cpp
	if (fcntl(new_socket->_fd, F_SETFL, O_NONBLOCK) == -1)
		throw(Error("fcntl returned -1"));
	memcpy(&new_socket->_addr, &client_addr, clnt_addr_size);
	return (new_socket);
}

void Socket::write(char const *msg)
{
	int ret = 0;
	if ((ret = ::send(_fd, msg, strlen(msg), 0)) > -1)
	{
		std::cout << "[SEND] " << msg << " [" << _fd << "] "
			  << "[" << show_type() << "]\n";
		_sent_bytes += strlen(msg);
		_sent_cnt++;		
	}
}

void Socket::write(Reply rpl)
{
	int	ret = 0;
	
	if ((ret = ::write(_fd, rpl.get_msg().c_str(), strlen(rpl.get_msg().c_str()))) > -1)
	{
		std::cout << "[SEND] " << rpl.get_msg().c_str() << " [" << _fd << "] "
			  << "[" << show_type() << "]\n";
		_sent_bytes += strlen(rpl.get_msg().c_str());
		_sent_cnt++;
	}
}

int			Socket::read(int fd, char *buffer, int *len)
{
	int		ret;

	ret = ft::read_until_crlf(fd, buffer, len);
	std::cout << "[RECV] " << buffer << " [" << fd << "] " << "[" << show_type() << "]\n";
	if (*len > 0)
	{
		_recv_bytes += static_cast<size_t>(*len);
		_recv_cnt++;
	}
	return (ret);
}

size_t		Socket::get_sent_bytes()
{
	return (_sent_bytes);
}
size_t		Socket::get_recv_bytes()
{
	return (_recv_bytes);
}

size_t		Socket::get_sent_cnt()
{
	return (_sent_cnt);
}
size_t		Socket::get_recv_cnt()
{
	return (_recv_cnt);
}


void Socket::show_info() const
{
	std::cout << "==== Socket info ====" << std::endl;
	std::cout << "fd     : " << _fd << std::endl;
	std::cout << "type   : " << show_type() << std::endl;
	std::cout << "port to: " << get_port() << std::endl;
	std::cout << "=====================" << std::endl;
}

int Socket::get_fd() const
{
	return (_fd);
}

unsigned short Socket::get_port() const
{
	return (ntohs(_addr.sin_port));
}

const char *Socket::get_hostname() const
{
	return (inet_ntoa(_addr.sin_addr));
}

std::string const &Socket::get_pass() const
{
	return (_pass);
}

void Socket::set_pass(std::string const &val) { _pass = val; }

void Socket::set_type(SOCKET_TYPE type)
{
	_type = type;
}

SOCKET_TYPE Socket::get_type() const
{
	return (_type);
}

const char *Socket::show_type() const
{
	if (_type == SERVER)
		return ("Server");
	else if (_type == CLIENT)
		return ("Client");
	else if (_type == LISTEN)
		return ("Listen");
	else if (_type == UNKNOWN)
		return ("Unknown");
	else
		return ("not defined type");
}

void				Socket::set_linkname(std::string const &linkname)
{
	_linkname = linkname;
}

std::string			Socket::get_linkname()
{
	return (_linkname);
}


time_t			Socket::get_start_time() { return (_start_time); }
time_t			Socket::get_last_action() { return (_last_action); }
void			Socket::set_last_action()
{
	time(&_last_action);
	_is_ping_check = false;
}

bool			Socket::is_ping_check() { return (_is_ping_check); }
void			Socket::set_ping_check() { _is_ping_check = true; }
