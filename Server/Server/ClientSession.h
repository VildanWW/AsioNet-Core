#pragma once
#include <boost/asio.hpp>
#include <memory>
#include "Settings.h"

struct SessionContext;

class ClientSession : public std::enable_shared_from_this<ClientSession> {
private:
	Net::tcp::socket clientSocket;

	std::unique_ptr<SessionContext> sessionContext;
public:
	ClientSession(Net::tcp::socket socket, uint64_t id);
};
