#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

class TextDocument
{
  public:
	void Load(std::filesystem::path filePath);
	void Save();

    std::vector<std::string> &GetTextBuffer();

  private:
    std::vector<std::string> textBuffer;
};
