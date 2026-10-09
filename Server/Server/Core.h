#pragma once
#include <unordered_map>
#include <memory>
#include <mutex>

namespace ServerAsio {
	namespace Network {
		class ClientSession;
	}
}

namespace ServerAsio {
	namespace Logic {
		class Core {
		private:
			std::unordered_map<uint64_t, std::shared_ptr<ServerAsio::Network::ClientSession>> clients;
			std::mutex clientsMutex;
		public:
			void AddClient(uint64_t sessionId, std::shared_ptr<ServerAsio::Network::ClientSession> session);

			void RemoveClient(uint64_t sessionId);
		};
	}
}

