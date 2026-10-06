#pragma once
#include <unordered_map>
#include <memory>
#include <mutex>

class ClientSession;

class Core {
private:
	std::unordered_map<uint64_t, std::shared_ptr<ClientSession>> clients;
	std::mutex clientsMutex;
public:
	void AddClient(uint64_t sessionId, std::shared_ptr<ClientSession> session);

	void RemoveClient(uint64_t sessionId);
};

