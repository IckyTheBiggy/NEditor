#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include "toml.hpp"

class Config
{
public:
    Config();
    int GetInt(const std::string& key, int defaultValue) const;
    float GetFloat(const std::string& key, float defaultValue) const;
private:
    void CreateDefaultConfig();
    void LoadConfig();

    std::filesystem::path configPath;
    toml::table configData;
};