#pragma once
#include <boost/asio.hpp>
#include "Settings.h"

class Server {
private:
	Net::asio::io_context ioContext;
	Net::tcp::acceptor acceptor;
public:
	Server();
	bool StartServer(int port);
};

