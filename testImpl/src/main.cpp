#include <fixParser/fixParser.hpp>
#include <iostream>

std::string generateFixMessage(const std::unordered_map<int, std::string>& fields)
{
	std::string message;
	for(const auto& [tag, value] : fields)
	{
		message += std::to_string(tag) + "=" + value + "\x01";
	}

	int sum = 0;
	for(char c : message)
		sum += static_cast<unsigned char>(c);
	int checksum = sum % 256;

	message += "10=" + std::to_string(checksum) + "\x01";
	return message;
}

int main()
{
	std::unordered_map<int, std::string> fixFields = {
		{8, "FIX.4.2"}, {9, "120"}, {35, "D"}, {49, "SENDER"}, {56, "TARGET"}, {34, "1"}};

	std::string fixMsg = generateFixMessage(fixFields);
	std::cout << "Generated FIX Message: " << fixMsg << std::endl;

	FixParser parser;
	if(parser.ParseMessage(fixMsg))
	{
		std::cout << "✅ FIX message parsed successfully!\n";
		std::cout << "MsgType: " << parser.GetField(35) << "\n";
	}
	else
	{
		std::cerr << "❌ Invalid FIX message!\n";
	}

	return 0;
}
