#include <iostream>
#include <exception>
#include "Server.h"

int main() {
    try {
        Server server;
        int port;

        std::cout << "Write port:";
        std::cin >> port;

        server.StartServer(port);
    }
    catch (std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }
    return 0;
}
