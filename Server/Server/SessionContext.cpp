#include <chrono>
#include "SessionContext.h"

namespace ServerAsio {
	namespace Network {
		SessionContext::SessionContext(uint64_t id) :
			sessionId(id),
			userId(""),
			isAuthorized(false),
			lastActivityTime(std::chrono::steady_clock::now()) {
		}
	}
}
