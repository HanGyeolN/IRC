#include "IrcServer.hpp"
		
std::string Reply::_user_name = "";
std::string Reply::_server_name = "";

int main(int argc, char **argv)
{
	try
	{
		IrcServer server(argc, argv);
		server.run(argc);
	}
	catch(Error &e)
	{
		std::cerr << e.what() << '\n';
	}
}
