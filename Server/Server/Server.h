#pragma once
#include <boost/asio.hpp>
#include <atomic>
#include <memory>
#include "Settings.h"

class Core;
class ClientSession;

class Server {
private:
	Net::asio::io_context& ioContext;
	Net::tcp::acceptor acceptor;

	Core& core;
	
	std::atomic<uint64_t> clientId = 1;

	Net::asio::awaitable<void> StartAccept();
	Net::asio::awaitable<void> HandleSessionLifeCycle(std::shared_ptr<ClientSession> session);
public:
	Server(Net::asio::io_context& ioContext, Core& core);
	bool StartServer(uint16_t port);
};

