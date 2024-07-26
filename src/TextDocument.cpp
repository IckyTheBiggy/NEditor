#include "TextDocument.h"

TextDocument::TextDocument(std::string filePath)
{
    this->filePath = filePath;
}

bool TextDocument::OpenTextDocument(std::vector<std::string> &textBuffer)
{
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Error opening .txt file: " << filePath << std::endl;
		return false;
	}

	std::string line;
	textBuffer.clear();

	while (std::getline(file, line))
	{
		textBuffer.push_back(line);
	}

	file.close();
	return true;
}

bool TextDocument::SaveTextDocument(std::vector<std::string> &textBuffer)
{
	std::ofstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Error saving .txt file: " << filePath << std::endl;
		return false;
	}

	for (const auto &line : textBuffer)
	{
		file << line << '\n';
	}

	file.close();
	return true;
}