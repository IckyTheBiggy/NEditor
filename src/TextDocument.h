#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

class TextDocument
{
  public:
	bool OpenTextDocument(const std::string &fileName, std::vector<std::string> &buffer);
	bool SaveTextDocument(const std::string &fileName, std::vector<std::string> &buffer);

  private:
};