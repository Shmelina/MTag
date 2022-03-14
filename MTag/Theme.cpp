#include "Theme.h"

ColorSetting::ColorSetting()
{
	ParamName = "";
	ParamDescr = "";
	Value = Color4f(1.0, 1.0, 1.0, 1.0);
	Default = Color4f(1.0, 1.0, 1.0, 1.0);
}

ColorSetting::ColorSetting(std::string ParName, std::string ParDescr, Color4f Val, Color4f DefVal)
{
	ParamName = ParName;
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
		Value = Color4f(((float)Red) / 255.0, ((float)Green) / 255.0, ((float)Blue) / 255.0, ((float)Alpha) / 255.0);
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
	if (!ReadThemeFile())
	{
		SetDefaultTheme();
		WriteDefaultThemeFile();
	}
}

bool Theme::ReadThemeFile()
{
	std::map<std::string, string> ThemeMap;
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
				ThemeMap[TmpN] = TmpV;
				TmpN = "";
				Junk = "";
				TmpV = "";
			}

			ThemeFile.close();

			if (!ApplyTheme(ThemeMap))
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

bool Theme::ApplyTheme(std::map<std::string, std::string> ThemeMap)
{
	if (!MainWindowBckg.Set(ThemeMap[MainWindowBckg.ParamName]))
		return false;
	if (!MainText.Set(ThemeMap[MainText.ParamName]))
		return false;
	if (!DebugText.Set(ThemeMap[DebugText.ParamName]))
		return false;

	return true;
}

void Theme::SetDefaultTheme()
{
	MainWindowBckg.SetDefault();
	MainText.SetDefault();
	DebugText.SetDefault();
}

void Theme::WriteDefaultThemeFile()
{
	std::ofstream SettingsFile(ThemeSettingFileName);
	if (SettingsFile.is_open())
	{
		SettingsFile << MainWindowBckg.ParamName << " = " << MainWindowBckg.GetDefS() << "\t\t#" << MainWindowBckg.ParamDescr << std::endl;
		SettingsFile << MainText.ParamName << " = " << MainText.GetDefS() << "\t\t#" << MainText.ParamDescr << std::endl;
		SettingsFile << DebugText.ParamName << " = " << DebugText.GetDefS() << "\t\t#" << DebugText.ParamDescr << std::endl;
	}
	else
	{
		throw std::exception(std::string("Unable to write default settings to '" + ThemeSettingFileName + "' file.").c_str());
	}
}