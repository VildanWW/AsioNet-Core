#pragma once
#include <boost/asio.hpp>
#include <atomic>
#include <memory>
#include "Settings.h"

namespace ServerAsio {
	namespace Logic {
		class Core;
	}
}

namespace ServerAsio {
	namespace Network {
		class ClientSession;
	}
}

namespace ServerAsio {
	namespace Network {
		class Server {
		private:
			Net::asio::io_context& ioContext;
			Net::tcp::acceptor acceptor;

			ServerAsio::Logic::Core& core;

			std::atomic<uint64_t> clientId = 1;

			Net::asio::awaitable<void> StartAccept();
			Net::asio::awaitable<void> HandleSessionLifeCycle(std::shared_ptr<ClientSession> session);
		public:
			Server(Net::asio::io_context& ioContext, ServerAsio::Logic::Core& core);
			bool StartServer(uint16_t port);
		};
	}
}

