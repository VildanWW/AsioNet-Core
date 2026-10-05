#include "SessionContext.h"

SessionContext::SessionContext(uint64_t id) : sessionId(id), userId(""), isAuthorized(false) {}
