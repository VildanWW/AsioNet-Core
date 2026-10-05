#pragma once
#include <boost/asio.hpp>
#include <atomic>
#include "Settings.h"

class Server {
private:
	Net::asio::io_context ioContext;
	Net::tcp::acceptor acceptor;
	
	std::atomic<uint64_t> clientId = 1;
public:
	Server();
	bool StartServer(uint16_t port);
};

