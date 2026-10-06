#include <chrono>
#include "SessionContext.h"

SessionContext::SessionContext(uint64_t id) : 
	sessionId(id), 
	userId(""), 
	isAuthorized(false), 
	lastActivityTime(std::chrono::steady_clock::now()) {}
