#pragma once
#include <unordered_map>
#include <memory>

class ClientSession;

class Core {
private:
	std::unordered_map<uint64_t, std::shared_ptr<ClientSession>> clients;
public:

};

