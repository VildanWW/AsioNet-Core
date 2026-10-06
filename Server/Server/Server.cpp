#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <memory>
#include "Server.h"
#include "Settings.h"
#include "ClientSession.h"
#include "Core.h"

Server::Server(Net::asio::io_context& ioContext, Core& core) : ioContext(ioContext), acceptor(ioContext), core(core) {}

Net::asio::awaitable<void> Server::StartAccept() {
	for (;;) {
		try {
			Net::tcp::socket socket = co_await acceptor.async_accept(Net::asio::use_awaitable);

			uint64_t currentId = clientId.fetch_add(1);
			spdlog::info("[Server] Net connection! ID: {}", currentId);

			auto newSession = std::make_shared<ClientSession>(std::move(socket), currentId);

			core.AddClient(currentId, newSession);

			Net::asio::co_spawn(ioContext, HandleSessionLifeCycle(newSession), Net::asio::detached);
		}
		catch (const std::exception& ex) {
			spdlog::error("[Server] Accept error: {}. Continuing...", ex.what());
		}
	}
}

Net::asio::awaitable<void> Server::HandleSessionLifeCycle(std::shared_ptr<ClientSession> session) {
	try {
		co_await session->Start();
	}
	catch (const std::exception& ex) {
		spdlog::warn("[Server] Client {} disconnected with exception: {}", session->GetSessionId(), ex.what());
	}
	catch (...) {
		spdlog::warn("[Server] Client {} disconnected with unknown exception", session->GetSessionId());
	}

	core.RemoveClient(session->GetSessionId());
	spdlog::info("[Server] Client {} resource cleaned up successfully", session->GetSessionId());
}

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

	Net::asio::co_spawn(ioContext, StartAccept(), Net::asio::detached);

	spdlog::info("[Server] Server is running on port {}", Settings::port);

	return true;
}
