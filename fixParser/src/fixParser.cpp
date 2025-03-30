#include <fixParser/fixParser.hpp>

bool FixParser::ParseMessage(const std::string& message)
{
	fields_.clear();
	std::istringstream ss(message);
	std::string field;

	while(std::getline(ss, field, '\x01'))
	{
		std::size_t pos = field.find('=');
		if(pos == std::string::npos)
			continue;

		int tag = std::stoi(field.substr(0, pos));
		std::string value = field.substr(pos + 1);
		fields_[tag] = value;
	}

	if(fields_.find(10) != fields_.end())
	{
		int expectedCheckSum = std::stoi(fields_[10]);
		return validateChecksum_(message, expectedCheckSum);
	}
	return false;
}

std::string FixParser::GetField(int tag) const
{
	auto it = fields_.find(tag);
	return (it != fields_.end()) ? it->second : "";
}

bool FixParser::validateChecksum_(const std::string& message, int expectedChecksum)
{
	size_t checksumPos = message.rfind("10="); // Находим начало "10=XXX"
	if(checksumPos == std::string::npos)
		return false;

	int sum = 0;
	for(size_t i = 0; i < checksumPos; i++)
	{
		sum += static_cast<unsigned char>(message[i]); // Считаем сумму всех байтов
	}
	int computedChecksum = sum % 256; // Берём по модулю 256

	return computedChecksum == expectedChecksum;
}
