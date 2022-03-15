#include "Theme.h"

ColorSetting::ColorSetting()
{
	ParamDescr = "";
	Value = Color4f(1.0, 1.0, 1.0, 1.0);
	Default = Color4f(1.0, 1.0, 1.0, 1.0);
}

ColorSetting::ColorSetting(std::string ParDescr, Color4f Val, Color4f DefVal)
{
	ParamDescr = ParDescr;
	Value = Val;
	Default = DefVal;
}

bool ColorSetting::Set(std::string NewVal)
{
	try {		
		unsigned short int Red, Green, Blue, Alpha;
		unsigned int ValueS;
		std::stringstream ValStream;
		ValStream << std::hex << NewVal;
		ValStream >> ValueS;
		Red = (ValueS & 0xff000000) >> 24;
		Green = (ValueS & 0x00ff0000) >> 16;
		Blue = (ValueS & 0x0000ff00) >> 8;
		Alpha = (ValueS & 0x000000ff);
		Value = Color4f(((float)Red) / 255.0f, ((float)Green) / 255.0f, ((float)Blue) / 255.0f, ((float)Alpha) / 255.0f);
		return true;
	}
	catch(exception e)
	{
		return false;
	}
}

bool ColorSetting::SetDefault()
{
	Value = Default;
	return true;
}

string ColorSetting::GetDefS()
{
	std::stringstream ValStream;
	ValStream << std::setfill('0') << std::hex << std::setw(2) << (int)(Default.r * 255.0) << std::setw(2) << (int)(Default.g * 255.0) << std::setw(2) << (int)(Default.b * 255.0) << std::setw(2) << (int)(Default.a * 255.0);
	return ValStream.str();
}

string ColorSetting::GetValS()
{
	std::stringstream ValStream;
	ValStream << std::setfill('0') << std::hex << std::setw(2) << (int)(Value.r * 255.0) << std::setw(2) << (int)(Value.g * 255.0) << std::setw(2) << (int)(Value.b * 255.0) << std::setw(2) << (int)(Value.a * 255.0);
	return ValStream.str();
}

Theme::Theme()
{
	ThemeMap["MainWindowBckg"] = ColorSetting("Main Window Background color", Color4f(1.0, 1.0, 1.0, 1.0), Color4f(1.0, 1.0, 1.0, 1.0));
	ThemeMap["MainText"] = ColorSetting("Main Text color", Color4f(0.0, 0.0, 0.0, 1.0), Color4f(0.0, 0.0, 0.0, 1.0));
	ThemeMap["DebugText"] = ColorSetting("Debug Text color", Color4f(1.0, 0.0, 0.0, 1.0), Color4f(1.0, 0.0, 0.0, 1.0));

	if (!ReadThemeFile())
	{
		SetDefaultTheme();
		WriteDefaultThemeFile();
	}
}

bool Theme::ReadThemeFile()
{
	std::map<std::string, string> NewThemeMap;
	if (std::filesystem::exists(ThemeSettingFileName))
	{
		std::ifstream ThemeFile(ThemeSettingFileName);
		if (ThemeFile.is_open())
		{
			std::string TmpN;
			std::string Junk;
			std::string TmpV;

			for (std::string Line; std::getline(ThemeFile, Line);)
			{
				std::stringstream LineStream(Line);
				LineStream >> TmpN >> Junk >> TmpV;
				NewThemeMap[TmpN] = TmpV;
				TmpN = "";
				Junk = "";
				TmpV = "";
			}

			ThemeFile.close();

			if (!ApplyTheme(NewThemeMap))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool Theme::ApplyTheme(std::map<std::string, std::string> NewThemeMap)
{
	if (!ThemeMap["MainWindowBckg"].Set(NewThemeMap["MainWindowBckg"]))
		return false;
	if (!ThemeMap["MainText"].Set(NewThemeMap["MainText"]))
		return false;
	if (!ThemeMap["DebugText"].Set(NewThemeMap["DebugText"]))
		return false;

	return true;
}

void Theme::SetDefaultTheme()
{
	for (auto& Set : ThemeMap)
	{
		Set.second.SetDefault();
	}
}

void Theme::WriteDefaultThemeFile()
{
	std::ofstream SettingsFile(ThemeSettingFileName);
	if (SettingsFile.is_open())
	{
		for (auto& Set : ThemeMap)
		{
			SettingsFile << Set.first << " = " << Set.second.GetDefS() << "\t\t#" << Set.second.ParamDescr << std::endl;
		}
	}
	else
	{
		throw std::exception(std::string("Unable to write default settings to '" + ThemeSettingFileName + "' file.").c_str());
	}
}