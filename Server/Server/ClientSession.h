#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <queue>
#include "Settings.h"
#include "SessionContext.h"

class ClientSession : public std::enable_shared_from_this<ClientSession> {
private:
	Net::tcp::socket clientSocket;
	std::unique_ptr<SessionContext> sessionContext;
	
	std::vector<uint8_t> readBuffer;
	Net::asio::awaitable<void> ReadLoop();

	std::queue<std::vector<uint8_t>> writeQueue;
	std::mutex writeQueueMutex;
	bool writingNow = false;

	Net::asio::awaitable<void> WriteLoop();
public:
	ClientSession(Net::tcp::socket socket, uint64_t id);
	~ClientSession();

	Net::asio::awaitable<void> Start();

	void Send(std::vector<uint8_t> packet);

	uint64_t GetSessionId() const;
};
