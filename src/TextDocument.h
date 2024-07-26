#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

class TextDocument
{
  public:

    TextDocument(std::string filePath);

	bool OpenTextDocument(std::vector<std::string> &textBuffer);
	bool SaveTextDocument(std::vector<std::string> &textBuffer);

  private:
    std::string filePath;
};