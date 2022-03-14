#include "Settings.h"

Setting::Setting()
{
	ParamDescr = "";
	Value = 0;
	Default = 0;
	Min = 0;
	Max = 0;
}

Setting::Setting(std::string ParDescr, unsigned int Val, unsigned int DefVal, unsigned int MinVal, unsigned int MaxVal)
{
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
	SettingsMap["WindowWidth"] = Setting("Program Window Width", 0, 1280, 600, 1920);
	SettingsMap["WindowHeight"] = Setting("Program Window Height", 0, 720, 400, 1080);

	if (!ReadSettingsFile())
	{
		SetDefaultSettings();
		WriteDefaultSettingsFile();
	}
}

bool Settings::ReadSettingsFile()
{
	std::map<std::string, unsigned int> NewSettingsMap;
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
				NewSettingsMap[TmpN] = TmpV;
				TmpN = "";
				Junk = "";
				TmpV = 0;
			}

			SettingsFile.close();

			if (!ApplySettings(NewSettingsMap))
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

bool Settings::ApplySettings(std::map<std::string, unsigned int> NewSettingsMap)
{
	if (!SettingsMap["WindowWidth"].CheckNSet(NewSettingsMap["WindowWidth"]))
		return false;

	if (!SettingsMap["WindowHeight"].CheckNSet(NewSettingsMap["WindowHeight"]))
		return false;
	
	return true;
}

void Settings::SetDefaultSettings()
{
	for (auto& Set : SettingsMap)
	{
		Set.second.SetDefaultSetting();
	}
}

void Settings::WriteDefaultSettingsFile()
{
	std::ofstream SettingsFile(SettingsFileName);
	if (SettingsFile.is_open())
	{
		for (auto& Set : SettingsMap)
		{
			SettingsFile << Set.first << " = " << Set.second.Default << "\t\t#" << Set.second.ParamDescr << std::endl;
		}
	}
	else
	{
		throw std::exception(std::string("Unable to write default settings to '" + SettingsFileName + "' file.").c_str());
	}
}


