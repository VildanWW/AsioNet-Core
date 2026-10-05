#pragma once
#include <string>
#include <chrono>

struct SessionContext {
	uint64_t sessionId = -1;
	std::string userId;
	bool isAuthorized;

	std::chrono::steady_clock::time_point lastActivityTime;

	SessionContext(uint64_t id);
};