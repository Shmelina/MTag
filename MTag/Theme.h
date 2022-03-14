#pragma once
#include "Graphics.h"
#include <fstream>
#include <filesystem>
#include <map>
#include <string>
#include <sstream>

class ColorSetting
{
public:
	std::string ParamName;		// Parameter Name
	std::string ParamDescr;		// Parameter Description
	Color4f Value;				// Current Value
	Color4f Default;			// Default Value

	ColorSetting();
	ColorSetting(std::string ParName, std::string ParDescr, Color4f Val, Color4f DefVal);
	bool Set(string NewVal);
	bool SetDefault();
	string GetDefS();
	string GetValS();
};

class Theme
{
	std::string ThemeSettingFileName = "Settings\\Theme.txt";

public:
	ColorSetting MainWindowBckg = ColorSetting("MainWindowBckg", "Main Window Background color", Color4f(1.0, 1.0, 1.0, 1.0), Color4f(1.0, 1.0, 1.0, 1.0));
	ColorSetting MainText = ColorSetting("MainText", "Main Text color", Color4f(0.0, 0.0, 0.0, 1.0), Color4f(0.0, 0.0, 0.0, 1.0));
	ColorSetting DebugText = ColorSetting("DebugText", "Debug Text color", Color4f(1.0, 0.0, 0.0, 1.0), Color4f(1.0, 0.0, 0.0, 1.0));

	Theme();

	bool ReadThemeFile();
	bool ApplyTheme(std::map<std::string, std::string>);
	void SetDefaultTheme();
	void WriteDefaultThemeFile();

};

