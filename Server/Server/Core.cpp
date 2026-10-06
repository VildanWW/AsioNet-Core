#include <unordered_map>
#include <spdlog/spdlog.h>
#include "Core.h"

void Core::AddClient(uint64_t sessionId, std::shared_ptr<ClientSession> session) {
	std::lock_guard<std::mutex> lock(clientsMutex);
	clients[sessionId] = session;
	spdlog::info("[Core] Client {} register in core. Total clients: {}", sessionId, clients.size());
}

void Core::RemoveClient(uint64_t sessionId) {
	std::lock_guard<std::mutex> lock(clientsMutex);
	auto itClient = clients.find(sessionId);
	if (itClient != clients.end()) {
		clients.erase(itClient);
		spdlog::info("[Core] Client {} unregistered from core. Total clients: {}", sessionId, clients.size());
	}
	else {
		spdlog::info("[Core] Not find the client with ID: {}", sessionId);
	}
}
