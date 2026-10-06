#pragma once
#include <boost/asio.hpp>

namespace Net {
	namespace ip = boost::asio::ip;
	namespace asio = boost::asio;
	namespace sys = boost::system;
	namespace error = boost::asio::error;

	using tcp = boost::asio::ip::tcp;
}

namespace Settings {
	inline uint16_t port;

	constexpr size_t sizePacket = 4096;
}