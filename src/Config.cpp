#include "Config.h"

Config::Config()
{
	std::filesystem::path configDir =
	    std::filesystem::path(getenv("HOME")) / ".config" / "neditor";

	configPath = configDir / "config.toml";
	LoadConfig();
}

void Config::CreateDefaultConfig()
{
	toml::table defaultConfig;

	defaultConfig.insert("fps", 120);
	defaultConfig.insert("easing-speed", 0.25);

	std::filesystem::create_directories(configPath.parent_path());
	std::ofstream file(configPath);

	file << defaultConfig;
}

void Config::LoadConfig()
{
	if (!std::filesystem::exists(configPath))
	{
		CreateDefaultConfig();
	}

	try
	{
		configData = toml::parse_file(configPath.string());
	}

	catch (const toml::parse_error &err)
	{
		std::cerr << "Error parsing config file: " << err << std::endl;
		throw;
	}
}

int Config::GetInt(const std::string &key, int defaultValue) const
{
	return configData[key].value_or(defaultValue);
}

float Config::GetFloat(const std::string &key, float defaultValue) const
{
	return configData[key].value_or(defaultValue);
}