#include <iostream>
#include <exception>
#include <spdlog/spdlog.h>
#include "Server.h"

int main() {
    spdlog::set_pattern("[%X] [%^%l%$] %v");

    spdlog::info("[Main] Application started. Preparing configuration...");
    try {
        Server server;
        int port;

        std::cout << "Write port:";
        std::cin >> port;

        if (!server.StartServer(port)) {
            spdlog::error("[Main] Application terminate: the method StartServer returned false");
            return -1;
        }
    }
    catch (std::exception& ex) {
        spdlog::error("[Main] Critical error: {}", ex.what());
        return -1;
    }

    spdlog::info("[Main] Server sucesfully finished");

    return 0;
}
