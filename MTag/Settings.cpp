#include "Settings.h"

Setting::Setting()
{
	ParamName = "";
	ParamDescr = "";
	Value = 0;
	Default = 0;
	Min = 0;
	Max = 0;
}

Setting::Setting(std::string ParName, std::string ParDescr, unsigned int Val, unsigned int DefVal, unsigned int MinVal, unsigned int MaxVal)
{
	ParamName = ParName;
	ParamDescr = ParDescr;
	Value = Val;
	Default = DefVal;
	Min = MinVal;
	Max = MaxVal;
}

bool Setting::CheckNSet(unsigned int NewVal)
{
	Value = NewVal;
	if (Value < Min || Value > Max)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Setting::SetDefaultSetting()
{
	Value = Default;
}

Settings::Settings()
{
	if (!ReadSettingsFile())
	{
		SetDefaultSettings();
		WriteDefaultSettingsFile();
	}
}

bool Settings::ReadSettingsFile()
{
	std::map<std::string, unsigned int> SettingsMap;
	if (std::filesystem::exists(SettingsFileName))
	{
		std::ifstream SettingsFile(SettingsFileName);
		if (SettingsFile.is_open())
		{
			std::string TmpN;
			std::string Junk;
			unsigned int TmpV;

			for(std::string Line; std::getline(SettingsFile, Line);)
			{
				std::stringstream LineStream(Line);
				LineStream >> TmpN >> Junk >> TmpV;
				SettingsMap[TmpN] = TmpV;
				TmpN = "";
				Junk = "";
				TmpV = 0;
			}

			SettingsFile.close();

			if (!ApplySettings(SettingsMap))
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

bool Settings::ApplySettings(std::map<std::string, unsigned int> SettingsMap)
{
	if (!WindowWidth.CheckNSet(SettingsMap[WindowWidth.ParamName]))
		return false;

	if (!WindowHeight.CheckNSet(SettingsMap[WindowHeight.ParamName]))
		return false;
	
	return true;
}

void Settings::SetDefaultSettings()
{
	WindowWidth.SetDefaultSetting();
	WindowHeight.SetDefaultSetting();
}

void Settings::WriteDefaultSettingsFile()
{
	std::ofstream SettingsFile(SettingsFileName);
	if (SettingsFile.is_open())
	{
		SettingsFile << WindowWidth.ParamName << " = " << WindowWidth.Default << "\t\t#" << WindowWidth.ParamDescr << std::endl;
		SettingsFile << WindowHeight.ParamName << " = " << WindowHeight.Default << "\t\t#" << WindowHeight.ParamDescr << std::endl;
	}
	else
	{
		throw std::exception(std::string("Unable to write default settings to '" + SettingsFileName + "' file.").c_str());
	}
}


