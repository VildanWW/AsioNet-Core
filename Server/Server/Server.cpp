#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include "Server.h"
#include "Settings.h"

Server::Server() : acceptor(ioContext) {}

bool Server::StartServer(uint16_t inputPort) {

	if (inputPort < 1024) {
		spdlog::error("[Server] Port isn't valid!");
		return false;
	}
	else {
		Settings::port = inputPort;
	}

	Net::sys::error_code errorCode;

	acceptor.open(Net::tcp::v4(), errorCode);
	if (errorCode) {
		spdlog::error("[Server] Method open isn't valid!");
		return false;
	}

	acceptor.set_option(Net::asio::socket_base::reuse_address(true), errorCode);
	if (errorCode) {
		spdlog::error("[Server] Method set_option isn't valid!");
		return false;
	}

	acceptor.bind({ Net::tcp::v4(), Settings::port }, errorCode);
	if (errorCode == Net::error::address_in_use) {
		spdlog::error("[Server] Port is already busy");
		return false;
	}
	if (errorCode) {
		spdlog::error("[Server] Unknown error");
		return false;
	}

	acceptor.listen(Net::asio::socket_base::max_listen_connections, errorCode);
	if (errorCode) {
		spdlog::error("[Server] Error with the method listen");
		return false;
	}

	spdlog::info("[Server] Server is running on port {}", Settings::port);

	return true;
}
