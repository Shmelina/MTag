#pragma once
#include <fstream>
#include <filesystem>
#include <map>
#include <string>
#include <sstream>

class Setting
{
public:
	std::string ParamDescr;		// Parameter Description
	unsigned int Value;			// Current Value
	unsigned int Default;		// Default Value
	unsigned int Min;			// Minimal Value
	unsigned int Max;			// Maximal Value

	Setting();
	Setting(std::string ParDescr, unsigned int Val, unsigned int DefVal, unsigned int MinVal, unsigned int MaxVal);
	bool CheckNSet(unsigned int NewVal);
	void SetDefaultSetting();
};

class Settings
{

private:

	std::string SettingsFileName = "Settings\\Settings.txt";

	bool ApplySettings(std::map<std::string, unsigned int>);

public:

	std::map<std::string, Setting> SettingsMap;

	Settings();

	bool ReadSettingsFile();
	void SetDefaultSettings();
	void WriteDefaultSettingsFile();
};