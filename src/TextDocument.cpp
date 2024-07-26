#include "TextDocument.h"

bool TextDocument::OpenTextDocument(const std::string &fileName, std::vector<std::string> &buffer)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error opening .txt file: " << fileName << std::endl;
		return false;
	}

	std::string line;
	buffer.clear();

	while (std::getline(file, line))
	{
		buffer.push_back(line);
	}

	file.close();
	return true;
}

bool TextDocument::SaveTextDocument(const std::string &fileName, std::vector<std::string> &buffer)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error saving .txt file: " << fileName << std::endl;
		return false;
	}

	for (const auto &line : buffer)
	{
		file << line << '\n';
	}

	file.close();
	return true;
}