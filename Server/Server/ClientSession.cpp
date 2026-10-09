#include <boost/asio.hpp>
#include <memory>
#include <spdlog/spdlog.h>
#include "ClientSession.h"
#include "SessionContext.h"

namespace ServerAsio {
	namespace Network {
		ClientSession::ClientSession(Net::tcp::socket socket, uint64_t id) :
			clientSocket(std::move(socket)),
			sessionContext(std::make_unique<SessionContext>(id))
		{
			spdlog::info("[ClientSession] Object created for ID: {}", id);
		}

		ClientSession::~ClientSession() {
			spdlog::info("[ClientSession] Object destroyed safely");
		}

		Net::asio::awaitable<void> ClientSession::Start() {
			co_await ReadLoop();
		}

		void ClientSession::Send(std::vector<uint8_t> packet) {
			std::lock_guard<std::mutex> lock(writeQueueMutex);

			writeQueue.push(std::move(packet));

			if (!writingNow) {
				writingNow = true;

				Net::asio::co_spawn(
					clientSocket.get_executor(),
					[](std::shared_ptr<ClientSession> self) -> Net::asio::awaitable<void> {
					co_await self->WriteLoop();
				}(shared_from_this()),
					Net::asio::detached
					);
			}
		}


		Net::asio::awaitable<void> ClientSession::WriteLoop() {
			try {
				for (;;) {
					std::vector<uint8_t> currentPacket;

					{
						std::lock_guard<std::mutex> lock(writeQueueMutex);
						if (writeQueue.empty()) {
							writingNow = false;
							co_return;
						}
						currentPacket = std::move(writeQueue.front());
						writeQueue.pop();
					}

					co_await Net::asio::async_write(clientSocket, Net::asio::buffer(currentPacket), Net::asio::use_awaitable);
				}
			}
			catch (const std::exception& ex) {
				spdlog::warn("[ClientSession {}] Write loop exception: {}", sessionContext->sessionId, ex.what());
			}
		}

		Net::asio::awaitable<void> ClientSession::ReadLoop() {
			try {
				readBuffer.resize(Settings::sizePacket);

				for (;;) {
					size_t bytesRead = co_await clientSocket.async_read_some(Net::asio::buffer(readBuffer), Net::asio::use_awaitable);

					if (bytesRead == 0) {
						co_return;
					}

					spdlog::info("[ClientSession {}] Received {} bytes", sessionContext->sessionId, bytesRead);
				}
			}
			catch (const Net::sys::system_error& ex) {
				if (ex.code() == boost::asio::error::eof || ex.code() == boost::asio::error::connection_reset) {
					spdlog::info("[ClientSession {}] Client disconnected normally", sessionContext->sessionId);
				}
				else {
					spdlog::error("[ClientSession {}] Read loop system error: {}", sessionContext->sessionId, ex.what());
				}
			}
			catch (const std::exception& ex) {
				spdlog::error("[ClientSession {}] Read loop unknown exception: {}", sessionContext->sessionId, ex.what());
			}
		}

		uint64_t ClientSession::GetSessionId() const {
			return sessionContext->sessionId;
		}
	}
}