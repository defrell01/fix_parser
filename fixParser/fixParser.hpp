#pragma once
#include <cstdint>
#include <sstream>
#include <string>
#include <unordered_map>

class FixParser
{
public:
	bool ParseMessage(const std::string& message);
	std::string GetField(int tag) const;

private:
	std::unordered_map<int, std::string> fields_;
	bool validateChecksum_(const std::string& message, int expectedChecksum);
};
