#pragma once
#include "../Graphics/Graphics.h"
#include <fstream>
#include <filesystem>
#include <map>
#include <string>
#include <sstream>

class ColorSetting
{
public:
	std::string ParamDescr;		// Parameter Description
	Color4f Value;				// Current Value
	Color4f Default;			// Default Value

	ColorSetting();
	ColorSetting(std::string ParDescr, Color4f Val, Color4f DefVal);
	bool Set(string NewVal);
	bool SetDefault();
	string GetDefS();
	string GetValS();
};

class Theme
{
private:

	std::string ThemeSettingFileName = "Settings\\Theme.txt";

	bool ApplyTheme(std::map<std::string, std::string>);

public:

	std::map<std::string, ColorSetting> ThemeMap;

	Theme();

	bool ReadThemeFile();
	void SetDefaultTheme();
	void WriteDefaultThemeFile();

};

