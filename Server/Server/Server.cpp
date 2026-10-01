#include "Server.h"
#include "Settings.h"
#include <boost/asio.hpp>
#include <iostream>

Server::Server() : acceptor(ioContext) {}

bool Server::StartServer(int inputPort) {

	if (inputPort < 1024 || inputPort > 65535) {
		std::cout << "Port isn't valid!\n";
		return false;
	}
	else {
		Settings::port = inputPort;
	}

	Net::sys::error_code errorCode;

	acceptor.open(Net::tcp::v4(), errorCode);

	if (errorCode) return false;

	acceptor.set_option(Net::tcp::acceptor::reuse_address(true), errorCode);

	acceptor.bind({ Net::tcp::v4(), Settings::port }, errorCode);

	if (errorCode == Net::error::address_in_use) {
		std::cout << "Port is already busy\n";
		acceptor.close();
		return false;
	}

	acceptor.listen(Net::asio::socket_base::max_listen_connections, errorCode);

	std::cout << "Server is running on port" << Settings::port << '\n';
}
