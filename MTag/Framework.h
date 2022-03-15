// header.h: включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта
//

#pragma once
#define _HAS_STD_BYTE 0
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
// Файлы заголовков среды выполнения C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <filesystem>
#include <string>

class Path {
public:
	const wchar_t* prog = L"C://ProgramData/MTag";
	const wchar_t* data = L"C://ProgramData/MTag/data";
	const wchar_t* saveddata = L"C://ProgramData/MTag/data/Track_List.dat";
	const wchar_t* picture = L"C://ProgramData/MTag/data/pictures";
	const wchar_t* music = L"C://ProgramData/MTag/music";
	Path() {};
};