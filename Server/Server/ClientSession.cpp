#include <boost/asio.hpp>
#include "ClientSession.h"
#include "SessionContext.h"

ClientSession::ClientSession(Net::tcp::socket socket, uint64_t id) : clientSocket(std::move(socket)) {}

