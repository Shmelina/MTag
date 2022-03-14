#pragma once
#include <fstream>
#include <filesystem>
#include <map>
#include <string>
#include <sstream>

class Setting
{
public:
	std::string ParamName;		// Parameter Name
	std::string ParamDescr;		// Parameter Description
	unsigned int Value;			// Current Value
	unsigned int Default;		// Default Value
	unsigned int Min;			// Minimal Value
	unsigned int Max;			// Maximal Value

	Setting();
	Setting(std::string ParName, std::string ParDescr, unsigned int Val, unsigned int DefVal, unsigned int MinVal, unsigned int MaxVal);
	bool CheckNSet(unsigned int NewVal);
	void SetDefaultSetting();
};

class Settings
{
	std::string SettingsFileName = "Settings\\Settings.txt";

public:

	Setting WindowWidth = Setting("WindowWidth", "Program Window Width", 0, 1280, 600, 1920);		// Program window width;
	Setting WindowHeight = Setting("WindowHeight", "Program Window Height", 0, 720, 400, 1080);		// Program window heigth;

	Settings();

	bool ReadSettingsFile();
	bool ApplySettings(std::map<std::string, unsigned int>);
	void SetDefaultSettings();
	void WriteDefaultSettingsFile();
};