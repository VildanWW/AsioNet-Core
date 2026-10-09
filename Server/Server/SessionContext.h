#pragma once
#include <string>
#include <chrono>

namespace ServerAsio {
	namespace Network {
		struct SessionContext {
			uint64_t sessionId = 0;
			std::string userId;
			bool isAuthorized;

			std::chrono::steady_clock::time_point lastActivityTime;

			SessionContext(uint64_t id);
		};
	}
}