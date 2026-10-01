#pragma once
#include "Settings.h"
#include <boost/asio.hpp>
class Server {
private:
	Net::asio::io_context ioContext;
	Net::tcp::acceptor acceptor;
public:
	Server();
	bool StartServer(int port);
};

